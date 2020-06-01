//
// Created by KHML on 2020/03/28.
//

#include <iostream>
#include <fstream>
#include <stdexcept>

#include "FileReader.hpp"

namespace io
{

    FileReader::FileReader(const std::string& filename) :filename(filename)
    {
        std::ifstream file(filename);

        if (file.fail())
            throw std::runtime_error("Failed to open file : " + filename);

        bool continuation = false;
        std::string line;
        while (getline(file, line))
        {
            bool is_last_backslash = line.back() == '\\';
            line = is_last_backslash ? line.substr(0, line.size() - 1) : line;

            if (continuation)
                _lines[_lines.size() - 1] = _lines.back() + line;
            else
                _lines.emplace_back(line);

            continuation = is_last_backslash;
        }

        if (continuation)
            throw std::runtime_error("Last character is a backslash, expect next line");

    }

    FileReader::~FileReader()
    = default;

    std::vector<std::string> FileReader::lines()
    {
        return _lines;
    }
}
