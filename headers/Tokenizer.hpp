//
// Created by KHML on 2019-11-24.
//

#ifndef BLUEPRINT_TOKENIZER_HPP
#define BLUEPRINT_TOKENIZER_HPP

#include <string>
#include <vector>

#include "Token.hpp"

namespace token
{
    void printTokens(const std::vector<Token>& tokens);

    class Tokenizer
    {
    public:
        Tokenizer();

        virtual ~Tokenizer();

        std::vector<Token> tokenize(const std::string& line);

    protected:
        virtual Token makeToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type);

        virtual Token makeToken(token::kind::Kind kindVal, const std::string& value);

    private:
        std::string line;
        std::vector<Token> tokens;
        int indicator = 0;

        void pushToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type);

        void pushToken(token::kind::Kind kindVal, const std::string& value);

        void readMultiCharOperator(token::kind::Kind kind, const std::string& ch, int size);

        void readString(const std::string& mark);

        void readNumber();

        void readIdentifier();
    };

    class FileTokenizer : protected Tokenizer
    {
    public:
        explicit FileTokenizer(const std::string& filename);

        ~FileTokenizer() override;

        std::vector<Token> tokenize();

    protected:
        uint16_t row{};

        Token makeToken(token::kind::Kind kindVal, const std::string& value, token::type::Type type) override;

        Token makeToken(token::kind::Kind kindVal, const std::string& value) override;

        const std::string filename;

        std::vector<std::string> lines;
    };
}

#endif //BLUEPRINT_TOKENIZER_HPP
