//
// Created by KHML on 2020/04/07.
//

#include <algorithm>
#include <utility>

#include "FileReader.hpp"
#include "Tokenizer.hpp"
#include "FileTokenizer.hpp"

namespace token
{
    FileTokenizer::FileTokenizer(const std::string& filename) :filename(filename), lines(io::readFile(filename))
    {}

    FileTokenizer::~FileTokenizer()
    = default;

    std::vector<Token> FileTokenizer::tokenize()
    {
        row = 0;
        std::vector<Token> allTokens;

        for (auto& line : lines)
        {
            std::vector<Token> tokens = Tokenizer::tokenize(line);
            allTokens.reserve(allTokens.size() + tokens.size());
            std::move(tokens.begin(), tokens.end(), std::back_inserter(allTokens));
            switch (allTokens.back().kind)
            {
                case token::kind::IDENTIFIER:
                case token::kind::INCREMENTAL:
                case token::kind::DECREMENTAL:
                    allTokens.emplace_back(token::Token(token::kind::SEMICOLON, ";"));
                    break;
                default:
                    break;
            }
            row++;
        }
        return std::move(allTokens);
    }

    Token FileTokenizer::makeToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type)
    {
        return Token(kindVal, value, type, filename, row);
    }

    Token FileTokenizer::makeToken(token::kind::Kind kindVal, const std::string& value)
    {
        return Token(kindVal, value, filename, row);
    }
}