//
// Created by KHML on 2020/01/29.
//

#include <regex>

#include "TokenType.hpp"
#include "TokenKind.hpp"

using std::string;
using std::regex;
using std::regex_match;
using tokenKind::toTokenKind;

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
            case RESERVED:
                return "RESERVED";
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
        {
            auto kind = toTokenKind(str);
            if (kind == tokenKind::IDENTIFIER)
                return UNTOKENIZE;
            else
                return RESERVED;
        }
    }
}