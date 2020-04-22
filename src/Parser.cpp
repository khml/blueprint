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

    Lexer::Token Parser::moveNext()
    {
        return tokens[++tokenHead];
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

        if (moveNext().kind == tokenKind::IDENTIFIER && hasNext())
        {
            auto variableToken = current();
            if (moveNext().kind == tokenKind::EQUAL)
            {
                auto equalToken = current();

                std::unique_ptr<AstNode> variableNode = std::make_unique<VariableNode>(variableToken);
#ifdef DEBUG_GRAPH
                variableNode->objId = objId++;
#endif

                auto right = equality();
                auto node = makeBinaryOpNode(equalToken, variableNode, right);
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
                return node;
            }
            prev();
        }

        prev();
        return nullptr;
    }

    std::unique_ptr<AstNode> Parser::equality()
    {
        LOG_DEBUG("equality");

        auto node = relation();

        while (hasNext())
        {
            if (current().kind == tokenKind::AND || current().kind == tokenKind::OR)
            {
                auto currentToken = current();
                auto right = relation();
                node = makeBinaryOpNode(currentToken, node, right);
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

        auto node = addition();
        std::unique_ptr<AstNode> right;

        auto currentToken = current();
        bool breakFlg = false;
        while (hasNext())
        {
            switch (current().kind)
            {
                case tokenKind::GRATER_THAN:
                case tokenKind::LESSER_THAN:
                case tokenKind::EQUIVALENCE:
                case tokenKind::GRATER:
                case tokenKind::LESSER:
                    right = addition();
                    node = makeBinaryOpNode(currentToken, node, right);
#ifdef DEBUG_GRAPH
                    node->objId = objId++;
#endif
                    break;
                default:
                    breakFlg = true;
                    break;
            }
            if (breakFlg)
                break;
        }
        return node;
    }

    std::unique_ptr<AstNode> Parser::addition()
    {
        LOG_DEBUG("addition");

        auto node = mul();

        while (hasNext())
        {
            if (current().kind == tokenKind::ADD || current().kind == tokenKind::SUB)
            {
                auto currentToken = current();
                auto right = mul();
                node = makeBinaryOpNode(currentToken, node, right);
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

        auto node = primary();
        while (hasNext())
        {
            if (current().kind == tokenKind::ASTERISK || current().kind == tokenKind::SLASH
                || current().kind == tokenKind::PERCENT)
            {
                auto currentToken = current();
                auto right = primary();
                node = makeBinaryOpNode(currentToken, node, right);
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
            }
            else
                break;
        }
        return node;
    }

    std::unique_ptr<AstNode> Parser::primary()
    {
        LOG_DEBUG("primary");

        moveNext();

        std::unique_ptr<AstNode> node;

        if (current().kind == tokenKind::PARENTHESIS_LEFT)
        {
            node = equality();
            if (hasNext() && current().kind != tokenKind::PARENTHESISE_RIGHT)
            {
                std::cerr << "expected ')' but given token-kind=" <<
                          tokenKind::fromTokenKind(current().kind) << ", value=" << current().value << std::endl;
                exit(1);
            }
        }
        else if (current().kind == tokenKind::IDENTIFIER)
            node = std::make_unique<PrimaryNode>(current());
        else
        {
            std::cerr << "expected IDENTIFIER token, but given token-kind=" <<
                      tokenKind::fromTokenKind(current().kind) << ", value=" << current().value << std::endl;
            exit(1);
        }

        if (hasNext())
            moveNext();

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
        return node;
    }
}