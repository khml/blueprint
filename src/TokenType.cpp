//
// Created by KHML on 2020/01/29.
//

#include <iostream>
#include <regex>

#include "TokenType.hpp"

using std::string;
using std::regex;
using std::regex_match;

namespace tokenType
{
    string fromTokenType(Type val)
    {
        switch (val)
        {
            case INTEGER:
                return "INTEGER";
            case FLOAT:
                return "FLOAT";
            case DOUBLE:
                return "DOUBLE";
            case STRING:
                return "STRING";
            case UNTOKENIZE:
                return "UNTOKENIZE";
            case IDENTIFIER:
            default:
                return "IDENTIFIER";
        }
    }

    bool isDigit(string& str)
    {
        static regex re("[0-9]+");
        return regex_match(str, re);
    }

    bool isFloat(string& str)
    {
        static regex re(R"(^(\d*[\\.]\d*)f$)");
        return regex_match(str, re);
    }

    bool isDouble(string& str)
    {
        static regex re(R"(^(\d*[\.]\d*)$)");
        return regex_match(str, re);
    }

    bool isIdentifier(string& str)
    {
        static regex re("[_a-zA-Z][_a-zA-Z0-9]?");
        return regex_match(str, re);
    }

    Type toType(std::string& str)
    {
        if (isIdentifier(str))
            return IDENTIFIER;
        else if (isDigit(str))
            return INTEGER;
        else if (isFloat(str))
            return FLOAT;
        else if (isDouble(str))
            return DOUBLE;
        else
            return UNTOKENIZE;
    }
}