//
// Created by KHML on 2020/04/01.
//

#ifndef BLUEPRINT_TOKEN_HPP
#define BLUEPRINT_TOKEN_HPP

#include "TokenKind.hpp"
#include "TokenType.hpp"

namespace Lexer
{
    class Token
    {
    public:
        Token(tokenKind::Kind kind, const std::string& value);

        Token(tokenKind::Kind kind, std::string value, tokenType::Type type);

        Token(tokenKind::Kind kind, tokenType::Type type);

        Token(tokenKind::Kind kind, std::string value, std::string filename, uint16_t row);

        Token(tokenKind::Kind kind, std::string value, tokenType::Type type, std::string filename, uint16_t row);

        Token(tokenKind::Kind kind, tokenType::Type type, std::string filename, uint16_t row);

        Token(const Token& orig);

        virtual ~Token();

        const tokenKind::Kind kind;
        const tokenType::Type type;
        const std::string value;
        const std::string filename;
        const uint16_t row;

        void print();
    };
}


#endif //BLUEPRINT_TOKEN_HPP
