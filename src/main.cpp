#include <iostream>
#include <fstream>
#include <string>

#include "Tokenizer.hpp"
#include "Parser.hpp"
#include "MacroLogger.hpp"

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

void read_file_and_print(const string& filename)
{
    STD_ERR_LOG("filename:" << filename);
    std::ifstream file(filename);
    if (file.fail())
    {
        STD_ERR_LOG("Failed to open file : " << filename);
        return;
    }

    string line;
    Lexer::Tokenizer tokenizer;
    auto parser = AST::Parser();
    while (getline(file, line))
    {
        STD_ERR_LOG("line: " << line);
        auto tokens = tokenizer.tokenize(line);
        Lexer::printTokens(tokens);
        auto node = parser.parse(tokens);
#ifdef DEBUG_NODE
        node->print();
#endif
#ifdef DEBUG_GRAPH
        node->graph();
#endif
        STD_ERR_LOG("");
    }
}

int main(int argc, char* argv[])
{
    if (argc == 0)
        read_print_loop();
    else
    {
        string filename = argv[1];
        read_file_and_print(filename);
    }

    return 0;
}