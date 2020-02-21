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
        TokenKind::TokenKind kind;

        tokens.emplace_back(Token(TokenKind::LINE_START, ""));

        auto putString = [&oss, &tokens](TokenKind::TokenKind kind) -> void
        {
            if (oss.str().empty())
                return;
            tokens.emplace_back(Token(kind, oss.str()));
            oss.str("");
        };

        for (auto&& ch:line)
        {
            kind = TokenKind::toTokenKind(ch);
            switch (kind)
            {
            case TokenKind::IDENTIFIER:
                oss << ch;
                break;
            case TokenKind::WHITESPACE:
                putString(TokenKind::IDENTIFIER);
                break;
            default:
                putString(TokenKind::IDENTIFIER);
                oss << ch;
                putString(kind);
                break;
            }
        }
        putString(TokenKind::IDENTIFIER);
    }
}
