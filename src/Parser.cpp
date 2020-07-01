//
// Created by KHML on 2020/01/10.
//

#include <iostream>
#include <memory>

#include "MacroLogger.hpp"
#include "Parser.hpp"

#define MakeBinaryOpNode(token, left, right) std::make_unique<BinaryOpNode>((token), (std::move(left)), (std::move(right)))

namespace AST
{

    Parser::Parser()
    = default;

    Parser::~Parser()
    = default;

    std::unique_ptr<AstNode> Parser::parse(std::vector<token::Token> tokenList)
    {
        tokenHead = 0;
        tokens.clear();
        tokens.swap(tokenList);
        return std::move(expression());
    }

    bool Parser::hasNext()
    {
        return tokenHead + 1 < tokens.size();
    }

    token::Token Parser::current()
    {
        return tokens[tokenHead];
    }

    bool Parser::isCurrent(token::kind::Kind kind)
    {
        return tokens[tokenHead].kind == kind;
    }

    token::Token Parser::consume()
    {
        return tokens[tokenHead++];
    }

    bool Parser::consume(token::kind::Kind expected)
    {
        bool isCurrentExpected = isCurrent(expected);
        if (isCurrentExpected)
            tokenHead++;
        return isCurrentExpected;
    }

    token::Token Parser::next()
    {
        return tokens[++tokenHead];
    }

    bool Parser::isNext(token::kind::Kind kind)
    {
        return tokens[tokenHead + 1].kind == kind;
    }

    token::Token Parser::prev()
    {
        return tokens[tokenHead - 1];
    }

    void Parser::expect(token::kind::Kind expectedToken)
    {
        if (consume(expectedToken))
            return;
        std::cerr << "expected '" << token::kind::fromTokenKind(expectedToken) << "' but given token-kind=" <<
                  token::kind::fromTokenKind(current().kind) << ", value=" << current().value << std::endl;
        exit(1);
    }

    std::unique_ptr<AstNode> Parser::expression()
    {
        LOG_DEBUG("expression");

        auto node = assignment();
        if (node != nullptr)
            return std::move(node);

        return std::move(equality());
    }

    std::unique_ptr<AstNode> Parser::assignment()
    {
        LOG_DEBUG("assignment");

        if (isCurrent(token::kind::IDENTIFIER) && hasNext() && isNext(token::kind::EQUAL))
        {
            std::unique_ptr<AstNode> variableNode = std::make_unique<VariableNode>(consume());
            return std::move(MakeBinaryOpNode(consume(), variableNode, equality()));
        }

        return nullptr;
    }

    std::unique_ptr<AstNode> Parser::equality()
    {
        LOG_DEBUG("equality");

        auto node = relation();

        while (hasNext())
        {
            if (isCurrent(token::kind::AND) || isCurrent(token::kind::OR))
            {
                node = MakeBinaryOpNode(consume(), node, relation());
            }
            else
                break;
        }
        return std::move(node);
    }

    std::unique_ptr<AstNode> Parser::relation()
    {
        LOG_DEBUG("relation");

        auto node = addition();
        while (hasNext())
        {
            switch (current().kind)
            {
                case token::kind::GRATER_THAN:
                case token::kind::LESSER_THAN:
                case token::kind::EQUIVALENCE:
                case token::kind::GRATER:
                case token::kind::LESSER:
                    node = MakeBinaryOpNode(consume(), node, addition());
                    break;
                default:
                    return std::move(node);
            }
        }
        return std::move(node);
    }

    std::unique_ptr<AstNode> Parser::addition()
    {
        LOG_DEBUG("addition");

        auto node = mul();

        while (hasNext())
        {
            if (isCurrent(token::kind::ADD) || isCurrent(token::kind::SUB))
            {
                node = MakeBinaryOpNode(consume(), node, mul());
            }
            else
                break;
        }
        return std::move(node);
    }

    std::unique_ptr<AstNode> Parser::mul()
    {
        LOG_DEBUG("mul");

        auto node = unary();
        while (hasNext())
        {
            if (isCurrent(token::kind::ASTERISK) || isCurrent(token::kind::SLASH) ||
                isCurrent(token::kind::PERCENT))
            {
                node = MakeBinaryOpNode(consume(), node, unary());
            }
            else
                break;
        }
        return std::move(node);
    }

    std::unique_ptr<AstNode> Parser::unary()
    {
        LOG_DEBUG("unary");

        static auto productToken = token::Token(token::kind::ASTERISK, "*", token::type::OPERATOR);

        if (consume(token::kind::SUB))
        {
            auto unitNode = std::make_unique<AstOpNode>(
                token::Token(token::kind::IDENTIFIER, "-1", token::type::INTEGER));
            auto left = priority();
            return std::move(MakeBinaryOpNode(productToken, left, unitNode));
        }

        consume(token::kind::ADD);

        return std::move(priority());
    }

    std::unique_ptr<AstNode> Parser::priority()
    {
        LOG_DEBUG("priority");

        if (current().kind == token::kind::IDENTIFIER)
            return std::move(chain());

        expect(token::kind::PARENTHESIS_LEFT);

        std::unique_ptr<AstNode> node = equality();

        expect(token::kind::PARENTHESISE_RIGHT);

        return std::move(node);
    }

    std::unique_ptr<AstNode> Parser::chain()
    {
        auto node = primary();

        while (hasNext())
        {
            if (isCurrent(token::kind::DOT))
            {
                node = std::move(MakeBinaryOpNode(consume(), node, primary()));
            }
            else
                break;
        }

        return std::move(node);
    }

    std::unique_ptr<AstNode> Parser::primary()
    {
        if (!isNext(token::kind::PARENTHESIS_LEFT))
            return std::move(std::make_unique<AstOpNode>(consume()));

        auto identifier = consume();
        auto arguments = tuple();
        return std::move(std::make_unique<CalleeNode>(identifier, arguments));
    }

    std::vector<std::unique_ptr<AstNode>> Parser::tuple(const token::kind::Kind delimiter, const token::kind::Kind left,
        const token::kind::Kind right)
    {
        std::vector<std::unique_ptr<AstNode>> arguments;

        expect(left);

        if (isCurrent(token::kind::PARENTHESISE_RIGHT))
            return std::move(arguments);

        while (hasNext())
        {
            auto arg = equality();
            arguments.emplace_back(std::move(arg));

            if (!consume(delimiter))
                break;
        }

        expect(right);

        return std::move(arguments);
    }

}