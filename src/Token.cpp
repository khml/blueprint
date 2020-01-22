//
// Created by KHML on 2020/01/08.
//

#include <sstream>

#include "Token.hpp"

namespace Token
{
    void tokenize(const std::string& line, std::vector<Token>& tokens)
    {
        std::ostringstream oss;
        TokenKind kind;

        tokens.emplace_back(Token(LINE_START, ""));

        auto putString = [&oss, &tokens](TokenKind kind) -> void
        {
            if (oss.str().empty())
                return;
            tokens.emplace_back(Token(kind, oss.str()));
            oss.str("");
        };

        for (auto&& ch:line)
        {
            kind = toTokenKind(ch);
            switch (kind)
            {
                case IDENTIFIER:
                    oss << ch;
                    break;
                case WHITESPACE:
                    putString(IDENTIFIER);
                    break;
                default:
                    putString(IDENTIFIER);
                    oss << ch;
                    putString(kind);
                    break;
            }
        }
        putString(IDENTIFIER);
    }
}
