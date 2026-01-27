import java.io.BufferedReader;
import java.io.ByteArrayInputStream;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintWriter;
import java.net.Socket;
import java.util.Arrays;
import java.util.HashMap;
import java.util.Map;
import java.util.Random;

import server.MyHTTPServer; // הוספנו
import server.RequestParser; // תיקנו את ה-Import
import server.RequestParser.RequestInfo; // תיקנו את ה-Import
import servlets.Servlet; // הוספנו

public class MainTrain { 

    private static void testParseRequest() {
        // Test data
        String request = "GET /api/resource?id=123&name=test HTTP/1.1\n" +
                            "Host: example.com\n" +
                            "Content-Length: 5\n"+
                            "\n" +
                            "filename=\"hello_world.txt\"\n"+
                            "\n" +
                            "hello world!\n"+
                            "\n" ;

        BufferedReader input=new BufferedReader(new InputStreamReader(new ByteArrayInputStream(request.getBytes())));
        try {
            RequestParser.RequestInfo requestInfo = RequestParser.parseRequest(input);

            // Test HTTP command
            if (!requestInfo.getHttpCommand().equals("GET")) {
                System.out.println("HTTP command test failed (-5)");
            }

            // Test URI
            if (!requestInfo.getUri().equals("/api/resource?id=123&name=test")) {
                System.out.println("URI test failed (-5)");
            }

            // Test URI segments
            String[] expectedUriSegments = {"api", "resource"};
            if (!Arrays.equals(requestInfo.getUriSegments(), expectedUriSegments)) {
                System.out.println("URI segments test failed (-5)");
                for(String s : requestInfo.getUriSegments()){
                    System.out.println(s);
                }
            } 
            // Test parameters
            Map<String, String> expectedParams = new HashMap<>();
            expectedParams.put("id", "123");
            expectedParams.put("name", "test");
            expectedParams.put("filename","\"hello_world.txt\"");
            
            if (!requestInfo.getParameters().equals(expectedParams)) {
                System.out.println("Parameters test failed (-5)");
                System.out.println("Expected: " + expectedParams);
                System.out.println("Got: " + requestInfo.getParameters());
            }

            // Test content
            byte[] expectedContent = "hello world!\n".getBytes();
            if (!Arrays.equals(requestInfo.getContent(), expectedContent)) {
                System.out.println("Content test failed (-5)");
                System.out.println("Expected: " + new String(expectedContent));
                String got = requestInfo.getContent() != null ? new String(requestInfo.getContent()) : "null";
                System.out.println("Got: " + got);
            } 
            input.close();
        } catch (IOException e) {
            System.out.println("Exception occurred during parsing: " + e.getMessage() + " (-5)");
            e.printStackTrace();
        }        
    }


    public static void testServer() throws Exception {
        int port = 8080 + new Random().nextInt(1000); // פורט אקראי למניעת התנגשויות
        MyHTTPServer server = new MyHTTPServer(port, 3);

        // הוספת סרבלט פשוט לבדיקה
        server.addServlet("GET", "/test", new Servlet() {
            @Override
            public void handle(RequestInfo ri, OutputStream toClient) throws IOException {
                String response = "HTTP/1.1 200 OK\r\n\r\nSuccess";
                toClient.write(response.getBytes());
            }
            @Override
            public void close() throws IOException {}
        });

        server.start();
        Thread.sleep(100); // נותנים לשרת רגע לעלות

        try {
            Socket client = new Socket("localhost", port);
            PrintWriter out = new PrintWriter(client.getOutputStream(), true);
            BufferedReader in = new BufferedReader(new InputStreamReader(client.getInputStream()));

            // שליחת בקשה
            out.println("GET /test HTTP/1.1");
            out.println("Host: localhost");
            out.println("");
            out.flush();

            // קריאת תשובה
            String line = in.readLine(); // HTTP/1.1 200 OK
            if(line == null || !line.contains("200 OK")) {
                 System.out.println("Server did not respond with 200 OK (-20)");
            }
            
            // דילוג על Headers
            while((line = in.readLine()) != null && !line.isEmpty()) {}

            // קריאת התוכן
            String content = in.readLine();
            if(content == null || !content.equals("Success")) {
                 System.out.println("Server response content incorrect (-20)");
            }

            in.close();
            out.close();
            client.close();
        } catch(Exception e) {
            System.out.println("Server connection failed (-20)");
            e.printStackTrace();
        } finally {
            server.close();
            Thread.sleep(200);
        }
    }
    
    public static void main(String[] args) {
        testParseRequest(); // 40 points
        try{
            testServer(); // 60
        }catch(Exception e){
            System.out.println("your server throwed an exception (-60)");
            e.printStackTrace();
        }
        System.out.println("done");
    }
}