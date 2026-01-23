#include <iostream>
#include "JsonParser.h"

void verifySampleJson(const JsonNode& root)
{
    if (root.Name() != "root")
        cout << "error root name (-3)" << endl;

    if (false == root.GetAttributes().Has("name"))
        cout << "error attribute name (-3)" << endl;
    else if (root.GetAttributes().Get("name") != "traffic_sim")
        cout << "error attribute name (-3)" << endl;

    if (root.GetChildren().size() != 4)
        cout << "error children count (-44)" << endl;
    else
    {
        auto trafficLightChilds = root.FindChilds("traffic_light");
        if (trafficLightChilds.size() != 2)
            cout << "error children count (-12)" << endl;
        else
        {
            auto light = trafficLightChilds[0];
            if (false == light->GetAttributes().Has("direction"))
                cout << "error attribute direction (-3)" << endl;
            else if (light->GetAttributes().Get("direction") != "North")
                cout << "error attribute direction (-3)" << endl;

            if (false == light->GetAttributes().Has("timer"))
                cout << "error attribute timer (-3)" << endl;
            else if (light->GetAttributes().Get("timer") != "1.25")
                cout << "error attribute timer (-3)" << endl;

            light = trafficLightChilds[1];
            if (false == light->GetAttributes().Has("direction"))
                cout << "error attribute direction (-3)" << endl;
            else if (light->GetAttributes().Get("direction") != "East")
                cout << "error attribute direction (-3)" << endl;

            if (false == light->GetAttributes().Has("timer"))
                cout << "error attribute timer (-3)" << endl;
            else if (light->GetAttributes().Get("timer") != "0.75")
                cout << "error attribute timer (-3)" << endl;
        }

        auto carChilds = root.FindChilds("car");
        if (carChilds.size() != 2)
            cout << "error children count (-18)" << endl;
        else
        {
            auto car = carChilds[0];
            if (false == car->GetAttributes().Has("lane"))
                cout << "error attribute lane (-3)" << endl;
            else if (car->GetAttributes().Get("lane") != "Left")
                cout << "error attribute lane (-3)" << endl;

            if (false == car->GetAttributes().Has("position"))
                cout << "error attribute position (-3)" << endl;
            else if (car->GetAttributes().Get("position") != "30.0")
                cout << "error attribute position (-3)" << endl;

            if (false == car->GetAttributes().Has("speed"))
                cout << "error attribute speed (-3)" << endl;
            else if (car->GetAttributes().Get("speed") != "12.5")
                cout << "error attribute speed (-3)" << endl;

            car = carChilds[1];
            if (false == car->GetAttributes().Has("lane"))
                cout << "error attribute lane (-3)" << endl;
            else if (car->GetAttributes().Get("lane") != "Right")
                cout << "error attribute lane (-3)" << endl;

            if (false == car->GetAttributes().Has("position"))
                cout << "error attribute position (-3)" << endl;
            else if (car->GetAttributes().Get("position") != "45.0")
                cout << "error attribute position (-3)" << endl;

            if (false == car->GetAttributes().Has("speed"))
                cout << "error attribute speed (-3)" << endl;
            else if (car->GetAttributes().Get("speed") != "10.0")
                cout << "error attribute speed (-3)" << endl;
        }
    }
}

int main()
{
    JsonParser p1;
    ifstream in1("input1.txt");
    JsonNode root1 = p1.Parse(in1);
    in1.close();

    verifySampleJson(root1);

    JsonParser p2;
    ofstream out1("output1.txt");
    p2.Save(root1, out1);
    out1.close();

    JsonParser p3;
    ifstream in2("output1.txt");
    JsonNode root2 = p3.Parse(in2);
    in2.close();

    verifySampleJson(root2);

    cout << "done" << endl;
}