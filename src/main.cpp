#include <iostream>
#include <string>
#include <vector>

#include "Token.hpp"
#include "Parser.hpp"

using std::string;
using std::cerr;
using std::endl;
using std::cin;

int main()
{
    string line;

    while (true)
    {
        cerr << "=";
        getline(cin, line);

        if (line == "end")
            break;

        std::vector<Lexer::Token> tokens;
        Lexer::tokenize(line, tokens);
        Lexer::printTokens(tokens);

        auto parser = AST::Parser();
        auto node = parser.parse(tokens);
#ifdef DEBUG_NODE
        node->print();
#endif
#ifdef DEBUG_GRAPH
        node->graph();
#endif
    }

    return 0;
}