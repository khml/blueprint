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
    class AstOpNode
    {
    public:
        explicit AstOpNode(const Lexer::Token& token);

        virtual ~AstOpNode();

        const Lexer::Token token;

#ifdef DEBUG_NODE

        virtual void print();

#endif

#ifdef DEBUG_GRAPH
        const int objId;

        virtual void graph();

        virtual void graph(std::ostringstream& dotFile);

#endif

    private:

#ifdef DEBUG_GRAPH
        static int objIdCounter;
#endif

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

        BinaryOpNode(const Lexer::Token& token, std::unique_ptr<AstOpNode> left, std::unique_ptr<AstOpNode> right);

        ~BinaryOpNode() override;

#ifdef DEBUG_NODE

        void print() override;

#endif

        std::unique_ptr<AstOpNode> left;
        std::unique_ptr<AstOpNode> right;

    protected:

#ifdef DEBUG_GRAPH

        void graph(std::ostringstream& dotFile) override;

#endif
    };
}

#endif //BLUEPRINT_NODE_HPP
