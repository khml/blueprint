//
// Created by KHML on 2020/01/10.
//

#include <iostream>

#include "MacroLogger.hpp"
#include "Parser.hpp"

namespace AST
{

    Parser::Parser()
    = default;

    Parser::~Parser()
    = default;

    std::unique_ptr<Node> Parser::parse(std::vector<Lexer::Token> tokenList)
    {
        tokens.clear();
        tokens.swap(tokenList);
        auto node = std::unique_ptr<Node>(expression());

        return node;
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

    Node* Parser::expression()
    {
        LOG_DEBUG("expression");

        auto node = assignment();
        if (node != nullptr)
            return node;

        return equality();
    }

    Node* Parser::assignment()
    {
        LOG_DEBUG("assignment");

        if (moveNext().kind == tokenKind::IDENTIFIER && hasNext())
        {
            auto varName = current().value;
            if (moveNext().kind == tokenKind::EQUAL)
            {
                auto node = new Node(varName);
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
                node = new Node(current().value, node, equality());
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

    Node* Parser::equality()
    {
        LOG_DEBUG("equality");

        Node* node = relation();

        while (hasNext())
        {
            if (current().kind == tokenKind::AND || current().kind == tokenKind::OR)
            {
                node = new Node(current().value, node, relation());
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
            }
            else
                break;
        }
        return node;
    }

    Node* Parser::relation()
    {
        LOG_DEBUG("relation");

        Node* node = addition();

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
                    node = new Node(current().value, node, addition());
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

    Node* Parser::addition()
    {
        LOG_DEBUG("addition");

        Node* node = mul();

        while (hasNext())
        {
            if (current().kind == tokenKind::ADD || current().kind == tokenKind::SUB)
            {
                node = new Node(current().value, node, mul());
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
            }
            else
                break;
        }
        return node;
    }

    Node* Parser::mul()
    {
        LOG_DEBUG("mul");

        Node* node = primary();
        while (hasNext())
        {
            if (current().kind == tokenKind::ASTERISK || current().kind == tokenKind::SLASH
                || current().kind == tokenKind::PERCENT)
            {
                node = new Node(current().value, node, primary());
#ifdef DEBUG_GRAPH
                node->objId = objId++;
#endif
            }
            else
                break;
        }
        return node;
    }

    Node* Parser::primary()
    {
        LOG_DEBUG("primary");

        moveNext();

        Node* node;
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
            node = new Node(current().value);
        else
        {
            std::cerr << "expected IDENTIFIER token, but given token-kind=" <<
                      tokenKind::fromTokenKind(current().kind) << ", value=" << current().value << std::endl;
            exit(1);
        }

        moveNext();

#ifdef DEBUG_GRAPH
        node->objId = objId++;
#endif
        return node;
    }
}