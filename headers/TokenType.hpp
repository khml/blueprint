//
// Created by KHML on 2020/01/29.
//

#ifndef BLUEPRINT_TOKENTYPE_HPP
#define BLUEPRINT_TOKENTYPE_HPP

#include <string>

namespace tokenType
{
    enum Type
    {
    INTEGER,
    FLOAT,
    DOUBLE,
    STRING,
    IDENTIFIER,
    OPERATOR,
    };

    bool isDigit(std::string& str);

    bool isFloat(std::string& str);

    bool isDouble(std::string& str);

    bool isIdentifier(std::string& str);

    Type toType(std::string& str);

    std::string fromTokenType(Type val);
}
#endif //BLUEPRINT_TOKENTYPE_HPP
