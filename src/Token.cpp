//
// Created by KHML on 2020/01/08.
//

#include <iostream>

#include "MacroLogger.hpp"
#include "Token.hpp"

namespace Lexer
{
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

    std::vector<Token> Tokenizer::tokenize(std::string& line)
    {
        lineData = line;
        tokens.clear();
        oss.str("");
        indicator = 0;

        LOG2(line);
        for (; indicator < line.size(); indicator++)
        {
            ch = line.substr(indicator, 1);
            kind = tokenKind::toTokenKind(ch);
            LOG2("idx: " << idx << ", kind: " << tokenKind::fromTokenKind(kind) << ", ch: " << ch);
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
                default:
                    pushToken(tokenKind::IDENTIFIER);
                    oss << ch;
                    pushToken(kind);
                    break;
            }
            LOG2("idx: " << idx << ", kind: " << tokenKind::fromTokenKind(kind) << ", ch: " << ch);
        }
        pushToken(tokenKind::IDENTIFIER);
        return tokens;
    }

    void printTokens(std::vector<Token>& tokens)
    {
        for (auto token : tokens)
        {
            std::cerr << token.value << " | " << token.token() << std::endl;
        }
    }
}
