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

        std::unique_ptr<AstOpNode> parse(std::vector<Lexer::Token> tokenList);

    protected:
        std::vector<Lexer::Token> tokens;

        int tokenHead = 0;

        bool hasNext();

        Lexer::Token current();

        bool isCurrent(tokenKind::Kind kind);

        Lexer::Token next();

        bool isNext(tokenKind::Kind kind);

        Lexer::Token prev();

        Lexer::Token consume();

        bool consume(tokenKind::Kind expected);

        std::unique_ptr<AstOpNode> expression();

        std::unique_ptr<AstOpNode> assignment();

        std::unique_ptr<AstOpNode> equality();

        std::unique_ptr<AstOpNode> relation();

        std::unique_ptr<AstOpNode> addition();

        std::unique_ptr<AstOpNode> mul();

        std::unique_ptr<AstOpNode> unary();

        std::unique_ptr<AstOpNode> priority();

        std::unique_ptr<AstOpNode> chain();

        std::unique_ptr<AstOpNode> primary();

        std::unique_ptr<AstOpNode> args();
    };
}

#endif //BLUEPRINT_PARSER_HPP
