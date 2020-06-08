//
// Created by KHML on 2019-11-24.
//

#ifndef BLUEPRINT_TOKENIZER_HPP
#define BLUEPRINT_TOKENIZER_HPP

#include <string>
#include <vector>

#include "Token.hpp"

namespace Lexer
{
    void printTokens(const std::vector<Token>& tokens);

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
}

#endif //BLUEPRINT_TOKENIZER_HPP
