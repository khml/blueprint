//
// Created by KHML on 2020/04/01.
//

#include <iostream>
#include <utility>

#include "Token.hpp"

#define MOVE(value) value(std::move((value)))

namespace Lexer
{
    Token::Token(tokenKind::Kind kind, const std::string& value) :kind(kind), value(value),
        type(tokenType::toType(value)), filename(""), row(0)
    {}

    Token::Token(tokenKind::Kind kind, std::string value, tokenType::Type type) :kind(kind), value(std::move(value)),
        type(type), filename(""), row(0)
    {}

    Token::Token(const tokenKind::Kind kind, const tokenType::Type type) :kind(kind), type(type),
        value(tokenKind::fromTokenKind(kind)), filename(""), row(0)
    {}

    Token::Token(const Lexer::Token& orig) :kind(orig.kind), type(orig.type), value(orig.value),
        filename(orig.filename), row(orig.row)
    {}

    Token::Token(tokenKind::Kind kind, std::string value, std::string filename, uint16_t row) :MOVE(kind), MOVE(value),
        type(tokenType::toType(value)), MOVE(filename), row(row)
    {}

    Token::Token(tokenKind::Kind kind, std::string value, tokenType::Type type, std::string filename, uint16_t row)
        :MOVE(kind), MOVE(value), MOVE(type), MOVE(filename), row(row)
    {}

    Token::Token(tokenKind::Kind kind, tokenType::Type type, std::string filename, uint16_t row)
        :MOVE(kind), value(tokenKind::fromTokenKind(kind)), MOVE(type), MOVE(filename), row(row)
    {}

    Token::~Token()
    = default;

    void Token::print()
    {
        std::cerr << value << " | " << tokenKind::fromTokenKind(kind)
                  << " | " << tokenType::fromTokenType(type) << std::endl;
    }
}