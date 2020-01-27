#include <iostream>
#include <string>
#include <vector>

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

        auto parser = Parser::Parser();
        auto node = parser.parse(line);
#ifdef DEBUG_NODE
        node->print();
#endif
        parser.print();
#ifdef DEBUG_GRAPH
        node->graph();
#endif
    }

    return 0;
}