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

        std::unique_ptr<AstNode> parse(std::vector<token::Token> tokenList);

    protected:
        std::vector<token::Token> tokens;

        int tokenHead = 0;

        bool hasNext();

        token::Token current();

        bool isCurrent(token::kind::Kind kind);

        token::Token next();

        bool isNext(token::kind::Kind kind);

        token::Token prev();

        token::Token consume();

        bool consume(token::kind::Kind expected);

        void expect(token::kind::Kind expectedToken);

        std::unique_ptr<AstNode> expression();

        std::unique_ptr<AstNode> assignment();

        std::unique_ptr<AstNode> equality();

        std::unique_ptr<AstNode> relation();

        std::unique_ptr<AstNode> addition();

        std::unique_ptr<AstNode> mul();

        std::unique_ptr<AstNode> unary();

        std::unique_ptr<AstNode> priority();

        std::unique_ptr<AstNode> chain();

        std::unique_ptr<AstNode> primary();

        std::vector<std::unique_ptr<AstNode>>
        tuple(token::kind::Kind delimiter = token::kind::COMMA, token::kind::Kind left = token::kind::PARENTHESIS_LEFT,
            token::kind::Kind right = token::kind::PARENTHESISE_RIGHT);
    };
}

#endif //BLUEPRINT_PARSER_HPP
