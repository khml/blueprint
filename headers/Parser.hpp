//
// Created by KHML on 2020/01/10.
//

#ifndef BLUEPRINT_PARSER_HPP
#define BLUEPRINT_PARSER_HPP

#include <vector>
#include <memory>

#include "Node.hpp"
#include "Tokenizer.hpp"

namespace AST
{
    class Parser
    {
    public:
        Parser();

        virtual ~Parser();

        std::unique_ptr<AstNode> parse(std::vector<Lexer::Token> tokenList);

    protected:
        std::vector<Lexer::Token> tokens;

        int tokenHead = 0;

        bool hasNext();

        Lexer::Token moveNext();

        Lexer::Token prev();

        Lexer::Token current();

        std::unique_ptr<AstNode> expression();

        std::unique_ptr<AstNode> assignment();

        std::unique_ptr<AstNode> equality();

        std::unique_ptr<AstNode> relation();

        std::unique_ptr<AstNode> addition();

        std::unique_ptr<AstNode> mul();

        std::unique_ptr<AstNode> primary();

        static std::unique_ptr<BinaryOpNode>
        makeBinaryOpNode(Lexer::Token& token, std::unique_ptr<AstNode>& left, std::unique_ptr<AstNode>& right);

#ifdef DEBUG_GRAPH
        int objId = 0;
#endif
    };
}

#endif //BLUEPRINT_PARSER_HPP
