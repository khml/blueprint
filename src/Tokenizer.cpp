//
// Created by KHML on 2020/01/08.
//

#include <iostream>
#include <utility>

#include "MacroLogger.hpp"
#include "Tokenizer.hpp"

namespace Lexer
{
    bool isNumber(const std::string& str)
    {
        try
        {
            stoi(str);
            return true;
        }
        catch (const std::invalid_argument& _)
        {
            return false;
        }
    }

    Token::Token(tokenKind::Kind kind, const std::string& value) :kind(kind), value(value),
        type(tokenType::toType(value))
    {}

    Token::Token(tokenKind::Kind kind, std::string value, tokenType::Type type) :kind(kind), value(std::move(value)),
        type(type)
    {}

    Token::~Token()
    = default;

    void Token::print()
    {
        std::cerr << value << " | " << tokenKind::fromTokenKind(kind)
                  << " | " << tokenType::fromTokenType(type) << std::endl;
    }

    Tokenizer::Tokenizer()
    = default;

    Tokenizer::~Tokenizer()
    = default;

    void Tokenizer::pushToken(tokenKind::Kind kindVal, const std::string& value, bool isString)
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

    void Tokenizer::readMultiCharOperator(tokenKind::Kind kind, const std::string& ch, const int size)
    {
        if (indicator + size - 1 >= lineData.size())
        {
            // end of line
            pushToken(kind, ch);
            return;
        }

        auto multiCharOp = lineData.substr(indicator, size);
        auto kindVal = tokenKind::toTokenKind(multiCharOp);

        if (kindVal == tokenKind::IDENTIFIER)
        {
            // rollback
            multiCharOp = ch;
            kindVal = kind;
        }
        else
            indicator++;

        pushToken(kindVal, multiCharOp);
    }

    void Tokenizer::readString(const std::string& mark)
    {
        int start = indicator++;
        for (; indicator < lineData.size(); indicator++)
        {
            if (lineData.substr(indicator, 1) == mark)
            {
                auto str = lineData.substr(start + 1, (indicator - start - 1));
                pushToken(tokenKind::IDENTIFIER, str, true);
                return;
            }
        }
        std::cerr << "expected : " << mark << " but not given." << std::endl;
        exit(1);
    }

    void Tokenizer::readIdentifier()
    {
        int start = indicator++;
        tokenKind::Kind kind;

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

    void Tokenizer::readNumber()
    {
        int start = indicator;
        bool isDotAppeared = false;
        std::string ch;
        for (; indicator < lineData.size(); indicator++)
        {
            ch = lineData.substr(indicator, 1);
            if (ch == ".")
            {
                // allow dot only once
                if (isDotAppeared)
                    break;
                isDotAppeared = true;
            }
            else if (isNumber(ch))
                continue;
            else if (ch == "f")
            {
                indicator++;
                break;
            }
            else
                break;
        }
        ch = lineData.substr(start, indicator - start);
        pushToken(tokenKind::IDENTIFIER, ch);
        --indicator;
    }

    std::vector<Token> Tokenizer::tokenize(const std::string& line)
    {
        lineData = line;
        tokens.clear();

        std::string ch;
        tokenKind::Kind kind;

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
                    if (isNumber(ch))
                        readNumber();
                    else
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
                    readMultiCharOperator(kind, ch, 2);
                    break;
                case tokenKind::APOSTROPHE:
                case tokenKind::QUOTATION:
                    readString(ch);
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
