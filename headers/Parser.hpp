//
// Created by KHML on 2020/01/10.
//

#ifndef BLUEPRINT_PARSER_HPP
#define BLUEPRINT_PARSER_HPP

#include <string>
#include <vector>
#include <memory>

#ifdef DEBUG_GRAPH
#include <sstream>
#endif

#include "Token.hpp"

namespace AST
{
    class Node
    {
    public:
        Node(std::string str);

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

    class Parser
    {
    public:
        Parser();

        ~Parser();

        std::unique_ptr<Node> parse(std::vector<Lexer::Token> tokenList);


    protected:
        std::vector<Lexer::Token> tokens;

        int tokenHead = 0;

        bool hasNext();

        Lexer::Token moveNext();

        Lexer::Token prev();

        Lexer::Token current();

        Node* expression();

        Node* assignment();

        Node* equality();

        Node* relation();

        Node* addition();

        Node* mul();

        Node* primary();

#ifdef DEBUG_GRAPH
    private:
        int objId = 0;
#endif
    };
}

#endif //BLUEPRINT_PARSER_HPP
