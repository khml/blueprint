#include <iostream>
#include <string>

#include "Tokenizer.hpp"
#include "Parser.hpp"

using std::string;
using std::cerr;
using std::endl;
using std::cin;

void read_print_loop()
{
    string line;

    while (true)
    {
        cerr << "> ";
        getline(cin, line);

        if (line == "end")
            break;

        Lexer::Tokenizer tokenizer;
        auto tokens = tokenizer.tokenize(line);
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
}

int main()
{
    read_print_loop();
    return 0;
}