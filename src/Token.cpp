//
// Created by KHML on 2020/01/08.
//

#include "iostream"
#include <sstream>

#include "MacroLogger.hpp"
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
        auto setIfNext = [&oss, &line, &idx, &ch, &kind, &putString]() -> void
        {
            putString(tokenKind::IDENTIFIER);

            if (++idx >= line.size())
            {
                // end of line
                oss << ch;
                putString(kind);
                return;
            }
            --idx;

            auto origKind = kind;
            ch = line.substr(idx, 2);
            kind = tokenKind::toTokenKind(ch);

            if (kind == tokenKind::IDENTIFIER)
            {
                // rollback
                ch = line.substr(idx, 1);
                kind = origKind;
                --idx;
            }

            oss << ch;
            putString(kind);
            ++idx;
        };

        LOG2(line);
        for (; idx < line.size(); idx++)
        {
            ch = line.substr(idx, 1);
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
                    putString(tokenKind::IDENTIFIER);
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
                    setIfNext();
                    break;
                default:
                    putString(tokenKind::IDENTIFIER);
                    oss << ch;
                    putString(kind);
                    break;
            }
            LOG2("idx: " << idx << ", kind: " << tokenKind::fromTokenKind(kind) << ", ch: " << ch);
        }
        putString(tokenKind::IDENTIFIER);
    }
}
