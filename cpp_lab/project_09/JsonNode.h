#pragma once
#include <vector>
#include "JsonAtts.h"

class JsonNode
{
public:
    //c'tor that sets the name for the node
    JsonNode( const string& name = "" ) : m_name(name)
    {
    }

    //returns the name
    const string& Name() const { return m_name; }

    //sets the attribute with the key-value pair
    void SetAttribute( const string& key, const string& value )
    {
        m_atts.Set(key, value);
    }

    //gets all attributes
    const JsonAttributes& GetAttributes() const { return m_atts; }

    //adds the child to the childs list
    void AddChild( const JsonNode& child )
    {
        m_children.push_back(child);
    }

    //gets all children
    const vector<JsonNode>& GetChildren() const
    {
        return m_children;
    }

    //finds and returns a pointer to the child with that name
    const JsonNode* FindChild( const string& name ) const
    {
        for (const auto& child : m_children)
        {
            if (child.Name() == name)
                return &child;
        }
        return nullptr;
    }

    //finds and returns a vector with pointers to all the childs with that name
    const vector<const JsonNode*> FindChilds( const string& name ) const
    {
        vector<const JsonNode*> foundChildren;

        for (const auto& child : m_children)
        {
            if (child.Name() == name)
                foundChildren.push_back(&child);
        }

        return foundChildren;
    }

private:
    string m_name;
    JsonAttributes m_atts;
    vector<JsonNode> m_children;
};