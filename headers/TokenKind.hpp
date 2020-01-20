// This File is Auto Generated.
#ifndef BLUEPRINT_TOKEN_KIND_HPP
#define BLUEPRINT_TOKEN_KIND_HPP

#include <string>

namespace Token
{
    enum TokenKind
    {
        ADD, /* + */
        SUB, /* - */
        ASTERISK, /* * */
        SLASH, /* / */
        AT, /* @ */
        EQUAL, /* = */
        PARENTHESISE_RIGHT, /* ) */
        PARENTHESIS_LEFT, /* ( */
        BRACKET_RIGHT, /* ] */
        BRACKET_LEFT, /* [ */
        BRACE_RIGHT, /* } */
        BRACE_LEFT, /* { */
        DOT, /* . */
        COMMA, /* , */
        COLON, /* : */
        SEMICOLON, /* ; */
        INTERROGATION, /* ? */
        GRATER, /* > */
        LESS, /* < */
        APOSTROPHE, /* \' */
        QUOTATION, /* " */
        AMPERSAND, /* & */
        PERCENT, /* % */
        DOLLAR, /* $ */
        SHARP, /* # */
        PIPE, /* | */
        UNDER_BAR, /* _ */
        BACKSLASH, /* \\ */
        WHITESPACE, /*   */
        IDENTIFIER, /*  */
        LINE_START,
        LINE_END,
    };

    TokenKind toTokenKind(char val);
    
    std::string fromTokenKind(TokenKind val);
}

#endif //BLUEPRINT_TOKEN_KIND_HPP
