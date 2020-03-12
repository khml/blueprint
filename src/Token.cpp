//
// Created by KHML on 2020/01/08.
//

#include "iostream"
#include <sstream>

#include "Token.hpp"

namespace Lexer
{
    void printTokens(std::vector<Token>& tokens)
    {
        for (auto token : tokens)
        {
            std::cerr << token.value << " | " << token.token() << std::endl;
        }
    }

    void tokenize(const std::string& line, std::vector<Token>& tokens)
    {
        std::ostringstream oss;
        tokenKind::Kind kind;

        tokens.emplace_back(Token(tokenKind::LINE_START, ""));

        auto putString = [&oss, &tokens](tokenKind::Kind kind) -> void
        {
            if (oss.str().empty())
                return;
            tokens.emplace_back(Token(kind, oss.str()));
            oss.str("");
        };

        std::string ch;
        int idx = 0;
        auto setIfNext = [&oss, &line, &idx, &ch, &kind, &putString]
            (tokenKind::Kind expect, tokenKind::Kind&& replace) -> void
        {
            putString(tokenKind::IDENTIFIER);
            oss << ch;

            if (++idx >= line.size())
            {
                --idx;
                putString(kind);
                return;
            }

            ch = line.substr(idx, 1);
            if (tokenKind::toTokenKind(ch) == expect)
            {
                oss << ch;
                putString(replace);
            }
            else
            {
                --idx;
                putString(kind);
            }
        };

        for (; idx < line.size(); idx++)
        {
            ch = line.substr(idx, 1);
            kind = tokenKind::toTokenKind(ch);
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
                    putString(tokenKind::IDENTIFIER);
                    oss << ch;
                    putString(tokenKind::WHITESPACE);
                    break;
                case tokenKind::ADD:
                    setIfNext(tokenKind::ADD, tokenKind::INCREMENTAL);
                    break;
                case tokenKind::SUB:
                    setIfNext(tokenKind::SUB, tokenKind::DECREMENTAL);
                    break;
                case tokenKind::ASTERISK:
                    setIfNext(tokenKind::SLASH, tokenKind::COMMENT_END);
                    break;
                case tokenKind::SLASH:
                    setIfNext(tokenKind::ASTERISK, tokenKind::COMMENT_START);
                    break;
                case tokenKind::EQUAL:
                    setIfNext(tokenKind::EQUAL, tokenKind::EQUIVALENCE);
                    break;
                case tokenKind::GRATER_THAN:
                    setIfNext(tokenKind::EQUAL, tokenKind::GRATER);
                    break;
                case tokenKind::LESSER_THAN:
                    setIfNext(tokenKind::EQUAL, tokenKind::LESSER);
                    break;
                case tokenKind::AMPERSAND:
                    setIfNext(tokenKind::AMPERSAND, tokenKind::AND);
                    break;
                case tokenKind::PIPE:
                    setIfNext(tokenKind::PIPE, tokenKind::OR);
                    break;
                default:
                    putString(tokenKind::IDENTIFIER);
                    oss << ch;
                    putString(kind);
                    break;
            }
        }
        putString(tokenKind::IDENTIFIER);
    }
}
