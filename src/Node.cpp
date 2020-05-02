//
// Created by KHML on 2020/02/16.
//

#include <iostream>
#include <string>
#include <utility>

#include "Node.hpp"

namespace AST
{
    AstNode::AstNode(const Lexer::Token& token) :token(token)
    {}

    AstNode::~AstNode()
    = default;

#ifdef DEBUG_NODE
    void AstNode::print()
    {
        std::cerr << "node: " << token.value << std::endl;
    }
#endif

#ifdef DEBUG_GRAPH
    void AstNode::graph()
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

    void AstNode::graph(std::ostringstream& dotFile)
    {
        dotFile << "  " << objId << " [ label = \"" << token.value << "\" ]" << std::endl;
    }
#endif

    PrimaryNode::PrimaryNode(const Lexer::Token& token) :AstNode(token)
    {}

    PrimaryNode::~PrimaryNode()
    = default;

    VariableNode::VariableNode(const Lexer::Token& token) :AstNode(token)
    {}

    VariableNode::~VariableNode()
    = default;

    BinaryOpNode::BinaryOpNode(const Lexer::Token& token) :AstNode(token), left(nullptr), right(nullptr)
    {}

    BinaryOpNode::BinaryOpNode(const Lexer::Token& token, std::unique_ptr<AstNode> left, std::unique_ptr<AstNode> right)
        :AstNode(token), left(std::move(left)), right(std::move(right))
    {}

    BinaryOpNode::~BinaryOpNode()
    = default;

#ifdef DEBUG_NODE
    void BinaryOpNode::print()
    {
        std::cerr << "[BinaryOpNode] op: " << token.value;
        if (left)
            std::cerr << ", left: " << left->token.value;
        if (right)
            std::cerr << ", right: " << right->token.value;
        std::cerr << std::endl;

        if (left)
            left->print();
        if (right)
            right->print();
    }
#endif

#ifdef DEBUG_GRAPH
    void BinaryOpNode::graph(std::ostringstream& dotFile)
    {
        AstNode::graph(dotFile);
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
}