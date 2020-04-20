//
// Created by KHML on 2020/02/16.
//

#include <iostream>
#include <string>
#include <utility>

#include "Node.hpp"

namespace AST
{
    Node::Node(std::string str) :str(std::move(str))
    {}

    Node::Node(std::string str, Node* left, Node* right) :str(std::move(str)), left(left), right(right)
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
}