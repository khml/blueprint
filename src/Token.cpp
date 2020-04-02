//
// Created by KHML on 2020/01/08.
//

#include <iostream>

#include "MacroLogger.hpp"
#include "Token.hpp"

namespace Lexer
{
    Token::Token(tokenKind::Kind kind, std::string&& value) :kind(kind), value(value), type(tokenType::toType(value))
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

    void Tokenizer::pushToken(tokenKind::Kind tokenKind)
    {
        if (oss.str().empty())
            return;
        tokens.emplace_back(Token(tokenKind, oss.str()));
        oss.str("");
    }

    void Tokenizer::pushToken(tokenKind::Kind tokenKind, tokenType::Type type)
    {
        if (oss.str().empty())
            return;
        tokens.emplace_back(Token(tokenKind, oss.str(), type));
        oss.str("");
    }

    void Tokenizer::pushTwoCharToken()
    {
        pushToken(tokenKind::IDENTIFIER);

        if (++indicator >= lineData.size())
        {
            // end of line
            oss << ch;
            pushToken(kind);
            return;
        }
        --indicator;

        auto origKind = kind;
        ch = lineData.substr(indicator, 2);
        kind = tokenKind::toTokenKind(ch);

        if (kind == tokenKind::IDENTIFIER)
        {
            // rollback
            ch = lineData.substr(indicator, 1);
            kind = origKind;
            --indicator;
        }

        oss << ch;
        pushToken(kind);
        ++indicator;
    }

    void Tokenizer::pushString()
    {
        int start = indicator++;
        for (; indicator < lineData.size(); indicator++)
        {
            if (lineData.substr(indicator, 1) == ch)
            {
                oss << lineData.substr(start + 1, (indicator - start - 1));
                pushToken(tokenKind::IDENTIFIER, tokenType::STRING);
                return;
            }
        }
        std::cerr << "expected : " << ch << " but not given." << std::endl;
        exit(1);
    }

    std::vector<Token> Tokenizer::tokenize(std::string& line)
    {
        lineData = line;
        tokens.clear();
        oss.str("");
        indicator = 0;

        LOG_DEBUG(line);
        for (; indicator < lineData.size(); indicator++)
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
                    oss << ch;
                    break;
                case tokenKind::WHITESPACE:
                    pushToken(tokenKind::IDENTIFIER);
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
                    pushTwoCharToken();
                    break;
                case tokenKind::APOSTROPHE:
                case tokenKind::QUOTATION:
                    pushString();
                    break;
                default:
                    pushToken(tokenKind::IDENTIFIER);
                    oss << ch;
                    pushToken(kind);
                    break;
            }
            LOG_DEBUG("idx: " << indicator << ", kind: " << tokenKind::fromTokenKind(kind) << ", ch: " << ch);
        }
        pushToken(tokenKind::IDENTIFIER);
        return tokens;
    }

    void printTokens(std::vector<Token>& tokens)
    {
        for (auto token : tokens)
            token.print();
    }
}
