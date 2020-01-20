//
// Created by KHML on 2019-11-24.
//

#ifndef BLUEPRINT_TOKEN_HPP
#define BLUEPRINT_TOKEN_HPP

#include <string>
#include <vector>

#include "TokenKind.hpp"

namespace Token
{
    class Token
    {
    public:
        Token(TokenKind kind, std::string&& value) : kind(kind), value(value)
        {};

        virtual ~Token()
        {};
        const TokenKind kind;
        const std::string value;

        std::string token()
        { return fromTokenKind(kind); };
    };

    void tokenize(const std::string& line, std::vector<Token>& tokens);
}

#endif //BLUEPRINT_TOKEN_HPP
