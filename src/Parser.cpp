//
// Created by KHML on 2020/01/10.
//

#include <iostream>

#ifdef DEBUG2
#define LOG2(value) std::cerr << value << std::endl
#else
#define LOG2(value)
#endif

#include "Parser.hpp"

namespace parser
{
    Node::Node(std::string str) :str(str)
    {}

    Node::Node(std::string str, Node* left, Node* right) :str(str), left(left), right(right)
    {}

    Node::~Node()
    {
        delete left;
        delete right;
    }

#ifdef DEBUG_NODE
    void Node::print()
    {
        std::cerr << "node: " << str;
        if (left != nullptr)
            std::cerr << ", left: " << left->str;
        if (right != nullptr)
            std::cerr << ", right: " << right->str;
        std::cerr << std::endl;

        if (left != nullptr)
            left->print();
        if (right != nullptr)
            right->print();

    }
#endif

#ifdef DEBUG_GRAPH
    void Node::graph()
    {
        std::ostringstream dotFile;
        dotFile
            << "digraph AST {" << std::endl
            << "  graph [" << std::endl
            << "    dpi = 300;" << std::endl
            << "    ratio = 0.5;" << std::endl
            << "  ]" << std::endl;
        graph(dotFile);
        dotFile << "}" << std::endl;

        std::cerr << dotFile.str() << std::endl;
    }

    void Node::graph(std::ostringstream& dotFile)
    {
        dotFile << "  " << objId << " [ label = \"" << str << "\" ]" << std::endl;
        if (left != nullptr)
            dotFile << "  " << objId << "->" << left->objId << std::endl;
        if (right != nullptr)
            dotFile << "  " << objId << "->" << right->objId << std::endl;
        if (left != nullptr)
            left->graph(dotFile);
        if (right != nullptr)
            right->graph(dotFile);
    }
#endif

    Parser::Parser()
    {}

    Parser::~Parser()
    {}

    void Parser::print()
    {
        for (auto token : tokens)
        {
            std::cerr << token.value << " | " << token.token() << std::endl;
        }
    }

    std::unique_ptr<Node> Parser::parse(std::string& line)
    {
        tokens.clear();
        token::tokenize(line, tokens);
        auto node = std::unique_ptr<Node>(expression());

        return node;
    }

    bool Parser::hasNext()
    {
        return tokenHead + 1 < tokens.size();
    }

    token::Token Parser::current()
    {
        return tokens[tokenHead];
    }

    token::Token Parser::moveNext()
    {
        return tokens[++tokenHead];
    }

    token::Token Parser::prev()
    {
        return tokens[tokenHead - 1];
    }

    Node* Parser::expression()
    {
        LOG2("expression");
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
        LOG2("mul");

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
        LOG2("primary");

        moveNext();

        Node* node;
        if (current().kind == tokenKind::PARENTHESIS_LEFT)
        {
            node = expression();
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