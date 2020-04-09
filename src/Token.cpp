//
// Created by KHML on 2020/01/08.
//

#include <iostream>

#include "MacroLogger.hpp"
#include "Token.hpp"

namespace Lexer
{
    Token::Token(tokenKind::Kind kind, std::string& value) :kind(kind), value(value), type(tokenType::toType(value))
    {}

    Token::Token(tokenKind::Kind kind, std::string&& value) :kind(kind), value(value), type(tokenType::toType(value))
    {}

    Token::Token(tokenKind::Kind kind, std::string& value, tokenType::Type type) :kind(kind), value(value), type(type)
    {}

    Token::Token(tokenKind::Kind kind, std::string&& value, tokenType::Type type) :kind(kind), value(value), type(type)
    {}

    Token::~Token()
    = default;

    void Token::print()
    {
        std::cerr << value << " | " << tokenKind::fromTokenKind(kind)
                  << " | " << tokenType::fromTokenType(type) << std::endl;
    }

    Tokenizer::Tokenizer() :kind(tokenKind::IDENTIFIER)
    {}

    Tokenizer::~Tokenizer()
    = default;

    void Tokenizer::pushToken(tokenKind::Kind kindVal, std::string& value, bool isString)
    {
        if (isString)
            tokens.emplace_back(Token(kindVal, value, tokenType::STRING));
        else
        {
            if (kindVal == tokenKind::IDENTIFIER)
                kindVal = tokenKind::toTokenKind(value); // check keyword or not

            tokens.emplace_back(Token(kindVal, value));
        }
    }

    void Tokenizer::readMultiCharOperator(const int size)
    {
        if (indicator + size - 1 >= lineData.size())
        {
            // end of line
            pushToken(kind, ch);
            return;
        }

        auto origKind = kind;
        ch = lineData.substr(indicator, size);
        kind = tokenKind::toTokenKind(ch);

        if (kind == tokenKind::IDENTIFIER)
        {
            // rollback
            ch = lineData.substr(indicator, 1);
            kind = origKind;
        }
        else
            indicator++;

        pushToken(kind, ch);
    }

    void Tokenizer::readString()
    {
        int start = indicator++;
        for (; indicator < lineData.size(); indicator++)
        {
            if (lineData.substr(indicator, 1) == ch)
            {
                auto str = lineData.substr(start + 1, (indicator - start - 1));
                pushToken(tokenKind::IDENTIFIER, str, true);
                return;
            }
        }
        std::cerr << "expected : " << ch << " but not given." << std::endl;
        exit(1);
    }

    void Tokenizer::readIdentifier()
    {
        int start = indicator++;
        for (; indicator < lineData.size(); indicator++)
        {
            kind = tokenKind::toTokenKind(lineData.substr(indicator, 1));
            if (kind != tokenKind::IDENTIFIER)
            {
                --indicator;
                break;
            }
        }

        auto identifier = lineData.substr(start, (indicator - start + 1));
        pushToken(tokenKind::IDENTIFIER, identifier);
    }

    std::vector<Token> Tokenizer::tokenize(const std::string& line)
    {
        lineData = line;
        tokens.clear();
        oss.str("");

        LOG_DEBUG(line);
        for (indicator = 0; indicator < lineData.size(); indicator++)
        {
            ch = lineData.substr(indicator, 1);
            kind = tokenKind::toTokenKind(ch);
            LOG_DEBUG("idx: " << indicator << ", kind: " << tokenKind::fromTokenKind(kind) << ", ch: " << ch);
            switch (kind)
            {
                /*
                 * if token is identifier, stored the one char.
                 * if token is whitespace, tokenize stored strings.
                 * else, tokenize stored strings, and put the token.
                 */
                case tokenKind::IDENTIFIER:
                    readIdentifier();
                    break;
                case tokenKind::WHITESPACE:
                    break;
                case tokenKind::ADD:
                case tokenKind::SUB:
                case tokenKind::ASTERISK:
                case tokenKind::SLASH:
                case tokenKind::EQUAL:
                case tokenKind::GRATER_THAN:
                case tokenKind::LESSER_THAN:
                case tokenKind::AMPERSAND:
                case tokenKind::PIPE:
                    readMultiCharOperator(2);
                    break;
                case tokenKind::APOSTROPHE:
                case tokenKind::QUOTATION:
                    readString();
                    break;
                default:
                    pushToken(kind, ch);
                    break;
            }
            LOG_DEBUG("idx: " << indicator << ", kind: " << tokenKind::fromTokenKind(kind) << ", ch: " << ch);
        }
        return tokens;
    }

    void printTokens(std::vector<Token>& tokens)
    {
        for (auto token : tokens)
            token.print();
    }
}
