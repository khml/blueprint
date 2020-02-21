//
// Created by KHML on 2020/01/08.
//

#include <sstream>

#include "Token.hpp"

namespace token
{
    void tokenize(const std::string& line, std::vector<Token>& tokens)
    {
        std::ostringstream oss;
        tokenKind::TokenKind kind;

        tokens.emplace_back(Token(tokenKind::LINE_START, ""));

        auto putString = [&oss, &tokens](tokenKind::TokenKind kind) -> void
        {
            if (oss.str().empty())
                return;
            tokens.emplace_back(Token(kind, oss.str()));
            oss.str("");
        };

        for (int i = 0; i < line.size(); i++)
        {
            auto ch = line.substr(i, 1);
            kind = tokenKind::toTokenKind(ch);
            switch (kind)
            {
                case tokenKind::IDENTIFIER:
                    oss << ch;
                    break;
                case tokenKind::WHITESPACE:
                    putString(tokenKind::IDENTIFIER);
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
