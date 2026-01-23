#include "JsonParser.h"
#include <sstream>

// Helper function to trim whitespace from both ends of a string
string Trim(const string& str)
{
    size_t first = str.find_first_not_of(" \t\n\r");
    if (first == string::npos)
        return "";
    size_t last = str.find_last_not_of(" \t\n\r");
    return str.substr(first, last - first + 1);
}

// Helper function to parse a single node recursively
JsonNode ParseNode(ifstream& in, string& nodeName)
{
    JsonNode node(nodeName);
    string line;

    while (getline(in, line))
    {
        line = Trim(line);

        // Skip empty lines
        if (line.empty())
            continue;

        // Check if we're at the end of this node
        if (line == "}")
            break;

        // Check if this is a child node (contains opening brace)
        size_t bracePos = line.find('{');
        if (bracePos != string::npos)
        {
            // Extract child node name
            string childName = Trim(line.substr(0, bracePos));
            JsonNode child = ParseNode(in, childName);
            node.AddChild(child);
        }
        else
        {
            // This is a key:value pair
            size_t colonPos = line.find(':');
            if (colonPos != string::npos)
            {
                string key = Trim(line.substr(0, colonPos));
                string value = Trim(line.substr(colonPos + 1));
                node.SetAttribute(key, value);
            }
        }
    }

    return node;
}

JsonNode JsonParser::Parse( ifstream& in )
{
    string line;

    // Find the root node
    while (getline(in, line))
    {
        line = Trim(line);

        if (line.empty())
            continue;

        // Look for the first node definition (name followed by {)
        size_t bracePos = line.find('{');
        if (bracePos != string::npos)
        {
            string rootName = Trim(line.substr(0, bracePos));
            return ParseNode(in, rootName);
        }
    }

    // Return empty node if nothing found
    return JsonNode();
}

void JsonParser::Save( const JsonNode& node, ofstream& out, int indent )
{
    // Write indentation
    string indentStr(indent, ' ');

    // Write node name and opening brace
    out << indentStr << node.Name() << " {" << endl;

    // Write attributes
    const auto& atts = node.GetAttributes().Values();
    for (const auto& pair : atts)
    {
        out << indentStr << "  " << pair.first << ":" << pair.second << endl;
    }

    // Write children recursively
    const auto& children = node.GetChildren();
    for (const auto& child : children)
    {
        Save(child, out, indent + 2);
    }

    // Write closing brace
    out << indentStr << "}" << endl;
}