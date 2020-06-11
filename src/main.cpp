#include <iostream>
#include <string>

#include "FileReader.hpp"
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

        token::Tokenizer tokenizer;
        auto tokens = tokenizer.tokenize(line);
        token::printTokens(tokens);

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

    io::FileReader file(filename);
    token::Tokenizer tokenizer;
    auto parser = AST::Parser();

    for(auto& line : file.lines())
    {
        STD_ERR_LOG("line: " << line);
        auto tokens = tokenizer.tokenize(line);
        token::printTokens(tokens);
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