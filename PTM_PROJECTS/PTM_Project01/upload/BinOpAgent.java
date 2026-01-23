package test;

import java.util.function.BinaryOperator;

// import graph.Agent;
// import graph.Message;
// import graph.TopicManagerSingleton;

public class BinOpAgent implements Agent {
    private String name;
    private String input1, input2, output;
    private BinaryOperator<Double> op;
    private double x = 0.0;
    private double y = 0.0;

    public BinOpAgent(String name, String input1, String input2, String output, BinaryOperator<Double> op) {
        this.name = name;
        this.input1 = input1;
        this.input2 = input2;
        this.output = output;
        this.op = op;

        TopicManagerSingleton.get().getTopic(input1).subscribe(this);
        TopicManagerSingleton.get().getTopic(input2).subscribe(this);
        TopicManagerSingleton.get().getTopic(output).addPublisher(this);
    }

    @Override
    public String getName() {
        return name;
    }

    @Override
    public void reset() {
        x = 0.0;
        y= 0.0;
    }

    @Override
    public void close() {
    }

    @Override
    public void callback(String topic, Message msg) {
        if (Double.isNaN(msg.asDouble))
            return;

        if (topic.equals(input1)){
            x = msg.asDouble;
        } else if (topic.equals(input2)) {
            y = msg.asDouble;
        }

        double result = op.apply(x, y);
        TopicManagerSingleton.get().getTopic(output).publish(new Message(result));
    }
}
