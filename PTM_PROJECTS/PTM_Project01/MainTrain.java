import java.util.List;
import configs.BinOpAgent;
import configs.Graph;
import configs.Node;
import graph.Message;
import graph.Topic;
import graph.TopicManagerSingleton;
import graph.TopicManagerSingleton.TopicManager;

public class MainTrain {

    // בדיקת מעגלים פשוטה ברמת ה-Node
    public static void testNodeCycles() {
        Node a = new Node("A");
        Node b = new Node("B");
        Node c = new Node("C");
        Node d = new Node("D");

        // A -> B -> C -> D
        a.addEdge(b);
        b.addEdge(c);
        c.addEdge(d);

        if (a.hasCycles())
            System.out.println("Error: detected cycle in a simple list (-10)");

        // יצירת מעגל: D -> A
        d.addEdge(a);

        if (!a.hasCycles())
            System.out.println("Error: failed to detect cycle A->B->C->D->A (-10)");
    }

    // בדיקת הסוכן הבינארי והגרף המלא
    public static void testBinOpAndGraph() {
        TopicManager tm = TopicManagerSingleton.get();
        tm.clear(); // מתחילים נקי

        // בניית הגרף החישובי: (x+y) * (x-y)
        // הקלטים: A, B
        // ביניים: Plus, Minus
        // תוצאה: Final

        new BinOpAgent("plusAgent", "A", "B", "Plus", (x, y) -> x + y);
        new BinOpAgent("minusAgent", "A", "B", "Minus", (x, y) -> x - y);
        new BinOpAgent("mulAgent", "Plus", "Minus", "Final", (x, y) -> x * y);

        // שליחת נתונים
        Topic topicA = tm.getTopic("A");
        Topic topicB = tm.getTopic("B");

        topicA.publish(new Message(10.0));
        topicB.publish(new Message(5.0));
        
        // חישוב צפוי:
        // Plus = 10 + 5 = 15
        // Minus = 10 - 5 = 5
        // Final = 15 * 5 = 75

        // בדיקה שהתוצאה הגיעה
        // (במערכת אמיתית זה א-סינכרוני, פה זה מיידי)
        
        // עכשיו נבנה את הגרף ונבדוק אם הוא נוצר נכון
        Graph g = new Graph();
        g.createFromTopics();

        if (g.hasCycles())
             System.out.println("Error: Graph shouldn't have cycles (-10)");
        
        // בדיקת שמות הצמתים בגרף
        // צריכים להיות צמתים ל: TA, TB, TPlus, TMinus, TFinal (Topics)
        // וצמתים לסוכנים: AplusAgent, AminusAgent, AmulAgent
        boolean foundAgent = false;
        for(Node n : g) {
            if(n.getName().equals("AplusAgent")) foundAgent = true;
        }
        if(!foundAgent) 
            System.out.println("Error: Graph creation missed the agent node (-10)");

        System.out.println("Graph size: " + g.size()); // רק לידע כללי
    }

    public static void main(String[] args) {
        testNodeCycles();
        testBinOpAndGraph();
        System.out.println("done");
    }
}