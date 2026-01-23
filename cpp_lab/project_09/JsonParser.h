#pragma once
#include <fstream>
#include "JsonNode.h"

class JsonParser
{
public:
    //gets an input stream and created the full JsonNode from it
    JsonNode Parse( ifstream& in );

    //get a JsonNode and an output stream and writes the file accordingly
    //indent = how many spaces to put in the line for indentation
    //attention! this function should be recursive...
    void Save( const JsonNode& node, ofstream& out, int indent = 0 );
};