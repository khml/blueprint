//
// Created by KHML on 2020/01/10.
//

#include <iostream>
#include <memory>

#include "MacroLogger.hpp"
#include "Parser.hpp"

namespace AST
{

    Parser::Parser()
    = default;

    Parser::~Parser()
    = default;

    std::unique_ptr<AstNode> Parser::parse(std::vector<Lexer::Token> tokenList)
    {
        tokens.clear();
        tokens.swap(tokenList);
        return expression();
    }

    bool Parser::hasNext()
    {
        return tokenHead + 1 < tokens.size();
    }

    Lexer::Token Parser::current()
    {
        return tokens[tokenHead];
    }

    bool Parser::isCurrent(tokenKind::Kind kind)
    {
        return tokens[tokenHead].kind == kind;
    }

    Lexer::Token Parser::consume()
    {
        return tokens[tokenHead++];
    }

    bool Parser::consume(tokenKind::Kind expected)
    {
        bool isCurrentExpected = isCurrent(expected);
        if (isCurrentExpected)
            tokenHead++;
        return isCurrentExpected;
    }

    Lexer::Token Parser::next()
    {
        return tokens[++tokenHead];
    }

    bool Parser::isNext(tokenKind::Kind kind)
    {
        return tokens[tokenHead + 1].kind == kind;
    }

    Lexer::Token Parser::prev()
    {
        return tokens[tokenHead - 1];
    }

    std::unique_ptr<AstNode> Parser::expression()
    {
        LOG_DEBUG("expression");

        auto node = assignment();
        if (node != nullptr)
            return node;

        return equality();
    }

    std::unique_ptr<AstNode> Parser::assignment()
    {
        LOG_DEBUG("assignment");

        if (isCurrent(tokenKind::IDENTIFIER) && hasNext() && isNext(tokenKind::EQUAL))
        {
            std::unique_ptr<AstNode> variableNode = std::make_unique<VariableNode>(consume());
#ifdef DEBUG_GRAPH
            variableNode->objId = objId++;
#endif
            auto equalToken = consume();
            auto right = equality();
            auto node = makeBinaryOpNode(equalToken, variableNode, right);
#ifdef DEBUG_GRAPH
            node->objId = objId++;
#endif
            return node;
        }

        return nullptr;
    }

    std::unique_ptr<AstNode> Parser::equality()
    {
        LOG_DEBUG("equality");

        auto node = relation();

        while (hasNext())
        {
            if (isCurrent(tokenKind::AND) || isCurrent(tokenKind::OR))
            {
                auto logicalOpToken = consume();
                auto right = relation();
                node = makeBinaryOpNode(logicalOpToken, node, right);
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
            }
            else
                break;
        }
        return node;
    }

    std::unique_ptr<AstNode> Parser::relation()
    {
        LOG_DEBUG("relation");

        static auto makeNode = [this](Lexer::Token&& logicalOpToken, std::unique_ptr<AstNode>& left,
            std::unique_ptr<AstNode>&& right) -> std::unique_ptr<AstNode>
        {
            return makeBinaryOpNode(logicalOpToken, left, right);
        };

        auto node = addition();
        while (hasNext())
        {
            switch (current().kind)
            {
                case tokenKind::GRATER_THAN:
                case tokenKind::LESSER_THAN:
                case tokenKind::EQUIVALENCE:
                case tokenKind::GRATER:
                case tokenKind::LESSER:
                    node = makeNode(consume(), node, addition());
#ifdef DEBUG_GRAPH
                    node->objId = objId++;
#endif
                    break;
                default:
                    return node;
            }
        }
        return node;
    }

    std::unique_ptr<AstNode> Parser::addition()
    {
        LOG_DEBUG("addition");

        auto node = mul();

        while (hasNext())
        {
            if (isCurrent(tokenKind::ADD) || isCurrent(tokenKind::SUB))
            {
                auto additionToken = consume();
                auto right = mul();
                node = makeBinaryOpNode(additionToken, node, right);
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
            }
            else
                break;
        }
        return node;
    }

    std::unique_ptr<AstNode> Parser::mul()
    {
        LOG_DEBUG("mul");

        auto node = unary();
        while (hasNext())
        {
            if (isCurrent(tokenKind::ASTERISK) || isCurrent(tokenKind::SLASH) ||
                isCurrent(tokenKind::PERCENT))
            {
                auto mulToken = consume();
                auto right = unary();
                node = makeBinaryOpNode(mulToken, node, right);
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
            }
            else
                break;
        }
        return node;
    }

    std::unique_ptr<AstNode> Parser::unary()
    {
        LOG_DEBUG("unary");

        static auto productToken = Lexer::Token(tokenKind::ASTERISK, "*", tokenType::OPERATOR);

        if (consume(tokenKind::SUB))
        {
            auto unitNode = std::make_unique<AstNode>(Lexer::Token(tokenKind::IDENTIFIER, "-1", tokenType::INTEGER));
#ifdef DEBUG_GRAPH
            unitNode->objId = objId++;
#endif
            auto left = primary();
            return makeBinaryOpNode(productToken, unitNode, left);
        }

        consume(tokenKind::ADD);

        return primary();
    }

    std::unique_ptr<AstNode> Parser::primary()
    {
        LOG_DEBUG("primary");

        std::unique_ptr<AstNode> node;

        if (consume(tokenKind::PARENTHESIS_LEFT))
        {
            node = equality();
            if (!consume(tokenKind::PARENTHESISE_RIGHT))
            {
                std::cerr << "expected ')' but given token-kind=" <<
                          tokenKind::fromTokenKind(current().kind) << ", value=" << current().value << std::endl;
                exit(1);
            }
        }
        else if (isCurrent(tokenKind::IDENTIFIER))
            node = std::make_unique<PrimaryNode>(current());
        else
        {
            std::cerr << "expected IDENTIFIER token, but given token-kind=" <<
                      tokenKind::fromTokenKind(current().kind) << ", value=" << current().value << std::endl;
            exit(1);
        }

        if (hasNext())
            next();

#ifdef DEBUG_GRAPH
        node->objId = objId++;
#endif
        return node;
    }

    std::unique_ptr<BinaryOpNode>
    Parser::makeBinaryOpNode(Lexer::Token& token, std::unique_ptr<AstNode>& left, std::unique_ptr<AstNode>& right)
    {
        auto node = std::make_unique<BinaryOpNode>(token);
        node->left = std::move(left);
        node->right = std::move(right);
#ifdef DEBUG_GRAPH
        node->objId = objId++;
#endif
        return node;
    }
}