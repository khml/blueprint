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

    void singleCharTokenize(const std::string& line, std::vector<Token>& tokens)
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
                    oss << ch;
                    putString(tokenKind::WHITESPACE);
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

    void multiCharTokenize(std::vector<Token>& tokens)
    {
        std::vector<Token> results;
        auto current = tokens.begin();

        auto addIfNext = [&tokens, &results, &current](tokenKind::Kind&& expect, Token&& token) -> void
        {
            if (++current != tokens.end() && current->kind == expect)
            {
                results.emplace_back(token);
                return;
            }
            results.emplace_back(*--current);
        };

        while (current != tokens.end())
        {
            switch (current->kind)
            {
                case tokenKind::ADD:
                    addIfNext(tokenKind::ADD, Token(tokenKind::INCREMENTAL, "++"));
                    break;
                case tokenKind::SUB:
                    addIfNext(tokenKind::SUB, Token(tokenKind::DECREMENTAL, "--"));
                    break;
                case tokenKind::ASTERISK:
                    addIfNext(tokenKind::SLASH, Token(tokenKind::COMMENT_END, "*/"));
                    break;
                case tokenKind::SLASH:
                    addIfNext(tokenKind::ASTERISK, Token(tokenKind::COMMENT_START, "/*"));
                    break;
                case tokenKind::EQUAL:
                    addIfNext(tokenKind::EQUAL, Token(tokenKind::EQUIVALENCE, "=="));
                    break;
                case tokenKind::GRATER_THAN:
                    addIfNext(tokenKind::EQUAL, Token(tokenKind::GRATER, ">="));
                    break;
                case tokenKind::LESSER_THAN:
                    addIfNext(tokenKind::EQUAL, Token(tokenKind::LESSER, "<="));
                    break;
                case tokenKind::AMPERSAND:
                    addIfNext(tokenKind::AMPERSAND, Token(tokenKind::AND, "&&"));
                    break;
                case tokenKind::PIPE:
                    addIfNext(tokenKind::PIPE, Token(tokenKind::OR, "||"));
                    break;
                case tokenKind::WHITESPACE:
                    // get rid of whitespace
                    break;
                default:
                    results.emplace_back(*current);
                    break;
            }
            current++;
        }
        tokens.swap(results);
    }

    void tokenize(const std::string& line, std::vector<Token>& tokens)
    {
        singleCharTokenize(line, tokens);
        multiCharTokenize(tokens);
    }
}
