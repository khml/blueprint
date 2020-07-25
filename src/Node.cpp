//
// Created by KHML on 2020/02/16.
//

#include <iostream>
#include <string>
#include <utility>

#include "Node.hpp"

namespace AST
{
#ifdef DEBUG_GRAPH
    AstNode::AstNode() :objId(objIdCounter++)
    {}
#else
    AstNode::AstNode()
    {}
#endif

    AstNode::~AstNode()
    = default;

#ifdef DEBUG_GRAPH
    int AstNode::objIdCounter = 0;

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
#endif

    ValueNode::ValueNode(const token::Token& token) :token(token)
    {}

    ValueNode::~ValueNode()
    = default;

    std::string ValueNode::str()
    {
        return token.value;
    }

#ifdef DEBUG_NODE
    void ValueNode::print()
    {
        std::cerr << "node: " << token.value << std::endl;
    }
#endif

#ifdef DEBUG_GRAPH
    void ValueNode::graph(std::ostringstream& dotFile)
    {
        dotFile << "  " << objId << " [ label = \"" << token.value << "\" ]" << std::endl;
    }
#endif

    VariableNode::VariableNode(const token::Token& token) :ValueNode(token)
    {}

    VariableNode::~VariableNode()
    = default;

    IntNode::IntNode(const token::Token& token) :ValueNode(token)
    {}

    IntNode::~IntNode()
    = default;

    FloatNode::FloatNode(const token::Token& token) :ValueNode(token)
    {}

    FloatNode::~FloatNode()
    = default;

    DoubleNode::DoubleNode(const token::Token& token) :ValueNode(token)
    {}

    DoubleNode::~DoubleNode()
    = default;

    StringNode::StringNode(const token::Token& token) :ValueNode(token)
    {}

    StringNode::~StringNode()
    = default;

    BinaryOpNode::BinaryOpNode(const token::Token& token, std::unique_ptr<AstNode> left,
        std::unique_ptr<AstNode> right)
        :token(token), left(std::move(left)), right(std::move(right))
    {}

    BinaryOpNode::~BinaryOpNode()
    = default;

    std::string BinaryOpNode::str()
    {
        return left->str() + token.value + right->str();
    }

#ifdef DEBUG_NODE
    void BinaryOpNode::print()
    {
        std::cerr << "[BinaryOpNode] op: " << token.value;
        if (left)
            std::cerr << ", left: " << left->str();
        if (right)
            std::cerr << ", right: " << right->str();
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
        dotFile << "  " << objId << " [ label = \"" << token.value << "\" ]" << std::endl;
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

    CalleeNode::CalleeNode(const token::Token& token, std::vector<std::unique_ptr<AstNode>>& args) :token(token),
        args(std::move(args))
    {}

    CalleeNode::~CalleeNode()
    = default;

    std::string CalleeNode::str()
    {
        return token.value + args_str();
    }

    std::string CalleeNode::args_str()
    {
        std::ostringstream oss;
        auto length = args.size();
        oss << "(";
        for (const auto& item: args)
        {
            oss << item->str();
            if (--length > 0)
                oss << ", ";
        }
        oss << ")";
        return oss.str();
    }

#ifdef DEBUG_NODE
    void CalleeNode::print()
    {
        std::cerr << "[Callee]: " + str();
        std::cerr << std::endl;
        for (auto& item : args)
            item->print();
    }
#endif

#ifdef DEBUG_GRAPH
    void CalleeNode::graph(std::ostringstream& dotFile)
    {
        dotFile << "  " << objId << " [ label = \"" << str() << "\" ]" << std::endl;
        for (auto& item : args)
            item->graph(dotFile);
        for (auto& item : args)
            dotFile << "  " << objId << "->" << item->objId << " [ label = \"" << "arg" << "\" ]" << std::endl;;
    }
#endif

    StatementsNode::StatementsNode(std::vector<std::unique_ptr<AstNode>>& args) :statements(std::move(args))
    {}

    StatementsNode::~StatementsNode()
    = default;

    std::string StatementsNode::str()
    {
        return "Statement(s)";
    }

#ifdef DEBUG_NODE
    void StatementsNode::print()
    {
        std::cerr << "[Statement(s)], ";
        std::cerr << std::endl;
        for (auto& item : statements)
            item->print();
    }
#endif

#ifdef DEBUG_GRAPH
    void StatementsNode::graph(std::ostringstream& dotFile)
    {
        dotFile << "  " << objId << " [ label = \"" << str() << "\" ]" << std::endl;
        for (auto& item : statements)
            item->graph(dotFile);

        uint16_t count(0);
        for (auto& item : statements)
            dotFile << "  " << objId << "->" << item->objId << " [ label = \"" << "Content(" << count++ << ")\" ]"
                    << std::endl;;
    }
#endif

}