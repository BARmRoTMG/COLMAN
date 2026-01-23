package test;

import java.util.ArrayList;
import java.util.List;

public class Topic {
    public final String name;
    private final List<Agent> subs;
    private final List<Agent> pubs;

    Topic(String name) {
        this.name = name;
        this.subs = new ArrayList<>();
        this.pubs = new ArrayList<>();
    }

    public void subscribe(Agent a) {
        subs.add(a);
    }

    public void unsubscribe(Agent a){
        subs.remove(a);
    }

    public void publish(Message msg) {
        for (Agent agent : subs){
            agent.callback(name, msg);
        }
    }

    public void addPublisher(Agent a) {
        pubs.add(a);
    }

    public void removePublisher(Agent a){
        pubs.remove(a);
    }
}
