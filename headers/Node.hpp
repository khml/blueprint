//
// Created by KHML on 2020/02/16.
//

#ifndef BLUEPRINT_NODE_HPP
#define BLUEPRINT_NODE_HPP

#include <string>

#ifdef DEBUG_GRAPH
#include <sstream>
#endif

namespace AST
{
    class Node
    {
    public:
        explicit Node(std::string str);

        Node(std::string str, Node* left, Node* right);

        ~Node();

#ifdef DEBUG_NODE

        void print();

#endif
        std::string str;
        Node* left = nullptr;
        Node* right = nullptr;

#ifdef DEBUG_GRAPH
        int objId = 0;

        void graph();

    private:
        void graph(std::ostringstream& dotFile);

#endif
    };
}

#endif //BLUEPRINT_NODE_HPP
