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
    class AstNode
    {
    public:
        AstNode();

        virtual ~AstNode();

        virtual std::string value() = 0;

#ifdef DEBUG_NODE

        virtual void print() = 0;

#endif

#ifdef DEBUG_GRAPH
        const int objId;

        virtual void graph() = 0;

        virtual void graph(std::ostringstream& dotFile) = 0;

#endif

    private:

#ifdef DEBUG_GRAPH
        static int objIdCounter;
#endif
    };

    class AstOpNode : public AstNode
    {
    public:
        explicit AstOpNode(const Lexer::Token& token);

        ~AstOpNode() override;

        std::string value() override;

#ifdef DEBUG_NODE

        void print() override;

#endif

#ifdef DEBUG_GRAPH

        void graph() override;

        void graph(std::ostringstream& dotFile) override;

#endif

    protected:
        const Lexer::Token token;
    };

    class PrimaryNode : public AstOpNode
    {
    public:
        explicit PrimaryNode(const Lexer::Token& token);

        ~PrimaryNode() override;
    };

    class VariableNode : public AstOpNode
    {
    public:
        explicit VariableNode(const Lexer::Token& token);

        ~VariableNode() override;
    };

    class BinaryOpNode : public AstOpNode
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
