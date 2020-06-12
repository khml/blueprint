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

        virtual std::string str() = 0;

#ifdef DEBUG_NODE

        virtual void print() = 0;

#endif

#ifdef DEBUG_GRAPH
        const int objId;

        virtual void graph();

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
        explicit AstOpNode(const token::Token& token);

        ~AstOpNode() override;

        std::string str() override;

#ifdef DEBUG_NODE

        void print() override;

#endif

#ifdef DEBUG_GRAPH

        void graph(std::ostringstream& dotFile) override;

#endif

    protected:
        const token::Token token;
    };

    class VariableNode : public AstOpNode
    {
    public:
        explicit VariableNode(const token::Token& token);

        ~VariableNode() override;
    };

    class BinaryOpNode : public AstOpNode
    {
    public:
        explicit BinaryOpNode(const token::Token& token);

        BinaryOpNode(const token::Token& token, std::unique_ptr<AstNode> left, std::unique_ptr<AstNode> right);

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

    class CalleeNode : public AstNode
    {
    public:
        CalleeNode(const token::Token& token, std::vector<std::unique_ptr<AstNode>>& args);

        ~CalleeNode() override;

        std::string str() override;

#ifdef DEBUG_NODE

        void print() override;

#endif

#ifdef DEBUG_GRAPH

        void graph(std::ostringstream& dotFile) override;

#endif

    protected:
        const token::Token token;
        const std::vector<std::unique_ptr<AstNode>> args;

        std::string args_str();
    };

}

#endif //BLUEPRINT_NODE_HPP
