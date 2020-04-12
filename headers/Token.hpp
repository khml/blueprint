//
// Created by KHML on 2019-11-24.
//

#ifndef BLUEPRINT_TOKEN_HPP
#define BLUEPRINT_TOKEN_HPP

#include <string>
#include <sstream>
#include <vector>

#include "TokenKind.hpp"
#include "TokenType.hpp"

namespace Lexer
{
    class Token
    {
    public:
        Token(tokenKind::Kind kind, const std::string& value);

        Token(tokenKind::Kind kind, std::string value, tokenType::Type type);

        virtual ~Token();

        const tokenKind::Kind kind;
        const tokenType::Type type;
        const std::string value;

        void print();
    };

    class Tokenizer
    {
    public:
        Tokenizer();

        virtual ~Tokenizer();

        std::vector<Token> tokenize(const std::string& line);

    protected:
        std::string lineData;
        std::vector<Token> tokens;
        int indicator = 0;

        void pushToken(tokenKind::Kind kindVal, const std::string& value, bool isString = false);

        void readMultiCharOperator(tokenKind::Kind kind, const std::string& ch, int size);

        void readString(const std::string& mark);

        void readNumber();

        void readIdentifier();
    };

    void printTokens(std::vector<Token>& tokens);
}

#endif //BLUEPRINT_TOKEN_HPP
