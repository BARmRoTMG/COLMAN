package test;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Map;

// import graph.Agent;
// import graph.Topic;
// import graph.TopicManagerSingleton;

public class Graph extends ArrayList<Node>{
    
    public boolean hasCycles() {
        for (Node node : this) {
            if (node.hasCycles())
                return true;
        }
        return false;
    }

    public void createFromTopics(){
        TopicManagerSingleton.TopicManager tm = TopicManagerSingleton.get();
        Map<String, Node> nodeMap = new HashMap<>();

        for (Topic topic : tm.getTopics()) {
            String topicNodeName = "T" + topic.name;
            Node topicNode = nodeMap.computeIfAbsent(topicNodeName, name -> new Node(name));

            for (Agent agent : topic.getSubs()) {
                String agentNodeName = "A" + agent.getName();
                Node agentNode = nodeMap.computeIfAbsent(agentNodeName, name -> new Node(name));
                topicNode.addEdge(agentNode);
            }

            for (Agent agent : topic.getPubs()) {
                String agentNodeName = "A" + agent.getName();
                Node agentNode = nodeMap.computeIfAbsent(agentNodeName, name -> new Node(name));
                agentNode.addEdge(topicNode);
            }
        }

        this.clear();
        this.addAll(nodeMap.values());
    }    
}
