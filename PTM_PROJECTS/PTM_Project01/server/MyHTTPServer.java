package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Map;
import java.util.concurrent.ConcurrentHashMap;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import servlets.Servlet;

public class MyHTTPServer implements HTTPServer {
    private int port;
    private ServerSocket serverSocket;
    private boolean stop = false;
    private ExecutorService threadPool;

    private Map<String, Servlet> getMap = new ConcurrentHashMap<>();
    private Map<String, Servlet> postMap = new ConcurrentHashMap<>();
    private Map<String, Servlet> deleteMap = new ConcurrentHashMap<>();

    public MyHTTPServer(int port, int nThreads) {
        this.port = port;
        this.threadPool = Executors.newFixedThreadPool(nThreads);
    }

    @Override
    public void addServlet(String httpCommand, String uri, Servlet s) {
        if (httpCommand.equals("GET")) {
            getMap.put(uri, s);
        } else if (httpCommand.equals("POST")) {
            postMap.put(uri, s);
        } else if (httpCommand.equals("DELETE")) {
            deleteMap.put(uri, s);
        }
    }

    @Override
    public void removeServlet(String httpCommand, String uri) {
        if (httpCommand.equals("GET")) {
            getMap.remove(uri);
        } else if (httpCommand.equals("POST")) {
            postMap.remove(uri);
        } else if (httpCommand.equals("DELETE")) {
            deleteMap.remove(uri);
        }
    }

    @Override
    public void start() {
        new Thread(this).start();
    }

    @Override
    public void run() {
        try {
            serverSocket = new ServerSocket(port);
            serverSocket.setSoTimeout(1000);

            while (!stop) {
                try {
                    Socket client = serverSocket.accept();
                    threadPool.execute(() -> {
                        try {
                            RequestParser.RequestInfo ri = RequestParser.parseRequest(
                                    new java.io.BufferedReader(new java.io.InputStreamReader(client.getInputStream())));

                            if (ri != null) {
                                Servlet bestMatch = findBestServlet(ri.getHttpCommand(), ri.getUri());

                                if (bestMatch != null) {
                                    bestMatch.handle(ri, client.getOutputStream());
                                }
                            }

                            client.close();
                        } catch (Exception e) {
                            e.printStackTrace();
                        }
                    });
                } catch (java.net.SocketTimeoutException e) {

                }
            }
            serverSocket.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public void close() {
        stop = true;
        threadPool.shutdown();
    }

    private Servlet findBestServlet(String command, String uri) {
        Map<String, Servlet> map = null;

        if (command.equals("GET"))
            map = getMap;
        else if (command.equals("POST"))
            map = postMap;
        else if (command.equals("DELETE"))
            map = deleteMap;

        if (map == null) return null;

        Servlet best = null;
        int maxLen = -1;

        for (Map.Entry<String, Servlet> entry : map.entrySet()) {
            String registeredUri = entry.getKey();

            if (uri.startsWith(registeredUri)) {
                if (registeredUri.length() > maxLen) {
                    maxLen = registeredUri.length();
                    best = entry.getValue();
                }
            }
        }
        return best;
    }
}
