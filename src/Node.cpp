//
// Created by KHML on 2020/02/16.
//

#include <iostream>
#include <string>
#include <utility>

#include "Node.hpp"

namespace AST
{
    AstNode::AstNode() :objId(objIdCounter++)
    {}

    AstNode::~AstNode()
    = default;

#ifdef DEBUG_GRAPH
    int AstNode::objIdCounter = 0;
#endif

    AstOpNode::AstOpNode(const Lexer::Token& token) :token(token)
    {}

    AstOpNode::~AstOpNode()
    = default;

    std::string AstOpNode::value()
    {
        return token.value;
    }

#ifdef DEBUG_NODE
    void AstOpNode::print()
    {
        std::cerr << "node: " << token.value << std::endl;
    }
#endif

#ifdef DEBUG_GRAPH
    void AstOpNode::graph()
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

    void AstOpNode::graph(std::ostringstream& dotFile)
    {
        dotFile << "  " << objId << " [ label = \"" << token.value << "\" ]" << std::endl;
    }
#endif

    PrimaryNode::PrimaryNode(const Lexer::Token& token) :AstOpNode(token)
    {}

    PrimaryNode::~PrimaryNode()
    = default;

    VariableNode::VariableNode(const Lexer::Token& token) :AstOpNode(token)
    {}

    VariableNode::~VariableNode()
    = default;

    BinaryOpNode::BinaryOpNode(const Lexer::Token& token) :AstOpNode(token), left(nullptr), right(nullptr)
    {}

    BinaryOpNode::BinaryOpNode(const Lexer::Token& token, std::unique_ptr<AstNode> left,
        std::unique_ptr<AstNode> right)
        :AstOpNode(token), left(std::move(left)), right(std::move(right))
    {}

    BinaryOpNode::~BinaryOpNode()
    = default;

#ifdef DEBUG_NODE
    void BinaryOpNode::print()
    {
        std::cerr << "[BinaryOpNode] op: " << token.value;
        if (left)
            std::cerr << ", left: " << left->value();
        if (right)
            std::cerr << ", right: " << right->value();
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
        AstOpNode::graph(dotFile);
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