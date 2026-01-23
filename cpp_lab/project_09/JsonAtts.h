#pragma once
#include <string>
#include <map>
using namespace std;

class JsonAttributes
{
public:
    //will add the pair key-value to the map
    void Set( const string& key, const string& value )
    {
        m_values[key] = value;
    }

    //will check if this key exists in the map
    bool Has( const string& key ) const
    {
        return m_values.find(key) != m_values.end();
    }

    //will get the value for this key
    const string& Get( const string& key ) const
    {
        return m_values.at(key);
    }

    //will get the map
    const map<string, string>& Values() const
    {
        return m_values;
    }

private:
    map<string, string> m_values;
};