//
// Created by KHML on 2019-11-24.
//

#ifndef BLUEPRINT_TOKEN_HPP
#define BLUEPRINT_TOKEN_HPP

#include <string>
#include <sstream>
#include <vector>

#include "TokenKind.hpp"

namespace Lexer
{
    class Token
    {
    public:
        Token(tokenKind::Kind kind, std::string&& value) :kind(kind), value(value)
        {};

        virtual ~Token()
        {};
        const tokenKind::Kind kind;
        const std::string value;

        std::string token()
        { return fromTokenKind(kind); };
    };

    class Tokenizer
    {
    public:
        Tokenizer();

        virtual ~Tokenizer();

        std::vector<Token> tokenize(std::string& line);

    protected:
        std::string lineData;
        std::vector<Token> tokens;
        std::ostringstream oss;
        tokenKind::Kind kind;
        std::string ch;
        int indicator = 0;

        void pushToken(tokenKind::Kind tokenKind);

        void pushTwoCharToken();

        void pushString();
    };

    void printTokens(std::vector<Token>& tokens);
}

#endif //BLUEPRINT_TOKEN_HPP
