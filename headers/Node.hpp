//
// Created by KHML on 2020/02/16.
//

#ifndef BLUEPRINT_NODE_HPP
#define BLUEPRINT_NODE_HPP

#include <string>

#ifdef DEBUG_GRAPH
#include <sstream>
#endif

#include "Tokenizer.hpp"

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

    class AstNode
    {
    public:
        explicit AstNode(const Lexer::Token& token);

        virtual ~AstNode();

        const Lexer::Token token;

#ifdef DEBUG_NODE

        virtual void print();

#endif

#ifdef DEBUG_GRAPH
        int objId = 0;

        virtual void graph();

        virtual void graph(std::ostringstream& dotFile);

#endif
    };

    class PrimaryNode : public AstNode
    {
    public:
        explicit PrimaryNode(const Lexer::Token& token);

        ~PrimaryNode() override;
    };

    class VariableNode : public AstNode
    {
    public:
        explicit VariableNode(const Lexer::Token& token);

        ~VariableNode() override;
    };

    class BinaryOpNode : public AstNode
    {
    public:
        explicit BinaryOpNode(const Lexer::Token& token);

        BinaryOpNode(const Lexer::Token& token, std::unique_ptr<AstNode> left, std::unique_ptr<AstNode> right);

        ~BinaryOpNode() override;

#ifdef DEBUG_NODE

        void print() override;

#endif

        std::unique_ptr<AstNode> left;
        std::unique_ptr<AstNode> right;

    protected:

#ifdef DEBUG_GRAPH

        void graph(std::ostringstream& dotFile) override;

#endif
    };
}

#endif //BLUEPRINT_NODE_HPP
