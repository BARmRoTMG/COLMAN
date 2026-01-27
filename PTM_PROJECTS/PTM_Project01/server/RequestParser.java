package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.util.HashMap;
import java.util.Map;

public class RequestParser {
    public static class RequestInfo {
        private String httpCommand;
        private String uri;
        private String[] uriSegments;
        private Map<String, String> parameters;
        private byte[] content;

        public RequestInfo(String httpCommand, String uri, String[] uriSegments, Map<String, String> parameters, byte[] content) {
            this.httpCommand = httpCommand;
            this.uri = uri;
            this.uriSegments = uriSegments;
            this.parameters = parameters;
            this.content = content;
        }

        public String getHttpCommand() { return httpCommand; }
        public String getUri() { return uri; }
        public String[] getUriSegments() { return uriSegments; }
        public Map<String, String> getParameters() { return parameters; }
        public byte[] getContent() { return content; }
    }

public static RequestInfo parseRequest(BufferedReader reader) throws IOException {
        String line = reader.readLine();
        if (line == null || line.isEmpty()) return null;

        String[] parts = line.split(" ");
        String command = parts[0];
        String fullUri = parts[1];

        String path = fullUri;
        Map<String, String> params = new HashMap<>();
        
        if (fullUri.contains("?")) {
            String[] uriParts = fullUri.split("\\?", 2);
            path = uriParts[0];
            String[] pairs = uriParts[1].split("&");
            for (String pair : pairs) {
                String[] keyValue = pair.split("=", 2);
                if (keyValue.length == 2) {
                    params.put(keyValue[0], keyValue[1]);
                }
            }
        }

        if (path.startsWith("/")) path = path.substring(1);
        String[] segments = path.isEmpty() ? new String[0] : path.split("/");

        while ((line = reader.readLine()) != null && !line.isEmpty()) {

        }

        while (reader.ready()) {
            line = reader.readLine();
            if (line == null || line.isEmpty()) break;

            if (line.contains("=")) {
                String[] keyValue = line.split("=", 2);
                params.put(keyValue[0], keyValue[1]);
            }
        }

        StringBuilder contentBuilder = new StringBuilder();
        while (reader.ready()) {
            line = reader.readLine();
            if (line == null || line.isEmpty()) break;
            
            contentBuilder.append(line).append("\n");
        }
        
        byte[] content = null;
        if (contentBuilder.length() > 0) {
            content = contentBuilder.toString().getBytes();
        }

        return new RequestInfo(command, fullUri, segments, params, content);
    }
}
