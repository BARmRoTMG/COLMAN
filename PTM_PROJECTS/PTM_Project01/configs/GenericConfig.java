package configs;

import java.nio.file.Files;
import java.nio.file.Paths;
import java.util.ArrayList;
import java.util.List;
import graph.Agent;
import java.lang.reflect.Constructor;

public class GenericConfig implements Config {
    private String confFile;
    private List<Agent> agents =new ArrayList<>();

    public void setConfFile(String confFile) {
        this.confFile = confFile;
    }

    @Override
    public void create() {
        try {
            List<String> lines = Files.readAllLines(Paths.get(confFile));

            for (int i = 0; i < lines.size(); i += 3) {
                String className = lines.get(i);
                String subsStr = lines.get(i+1);
                String pubsStr = lines.get(i+2);

                String[] subs = subsStr.split(",");
                String[] pubs = pubsStr.split(",");

                Class<?> clazz = Class.forName(className);
                Constructor<?> ctor = clazz.getConstructor(String[].class, String[].class);
                Agent agent = (Agent) ctor.newInstance((Object)subs, (Object)pubs);
                agents.add(new ParallelAgent(agent));
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    @Override
    public String getName() {
        return "Generic Config";
    }

    @Override
    public int getVersion() {
        return 1;
    }

    @Override
    public void close() {
        for (Agent agent : agents) {
            agent.close();
        }
    }
}
