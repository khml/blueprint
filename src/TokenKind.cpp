// This File is Auto Generated.

#include <string>

#include "TokenKind.hpp"

namespace Token
{
    TokenKind toTokenKind(char val)
    {
        switch (val)
        {
            case '+':
                return ADD;
            case '-':
                return SUB;
            case '*':
                return ASTERISK;
            case '/':
                return SLASH;
            case '@':
                return AT;
            case '=':
                return EQUAL;
            case ')':
                return PARENTHESISE_RIGHT;
            case '(':
                return PARENTHESIS_LEFT;
            case ']':
                return BRACKET_RIGHT;
            case '[':
                return BRACKET_LEFT;
            case '}':
                return BRACE_RIGHT;
            case '{':
                return BRACE_LEFT;
            case '.':
                return DOT;
            case ',':
                return COMMA;
            case ':':
                return COLON;
            case ';':
                return SEMICOLON;
            case '?':
                return INTERROGATION;
            case '>':
                return GRATER;
            case '<':
                return LESS;
            case '\'':
                return APOSTROPHE;
            case '"':
                return QUOTATION;
            case '&':
                return AMPERSAND;
            case '%':
                return PERCENT;
            case '$':
                return DOLLAR;
            case '#':
                return SHARP;
            case '|':
                return PIPE;
            case '_':
                return UNDER_BAR;
            case '\\':
                return BACKSLASH;
            case ' ':
                return WHITESPACE;
            default:
                return IDENTIFIER;

        }
    };

    std::string fromTokenKind(TokenKind val)
    {
        switch (val)
        {
            case ADD:
                return "ADD";
            case SUB:
                return "SUB";
            case ASTERISK:
                return "ASTERISK";
            case SLASH:
                return "SLASH";
            case AT:
                return "AT";
            case EQUAL:
                return "EQUAL";
            case PARENTHESISE_RIGHT:
                return "PARENTHESISE_RIGHT";
            case PARENTHESIS_LEFT:
                return "PARENTHESIS_LEFT";
            case BRACKET_RIGHT:
                return "BRACKET_RIGHT";
            case BRACKET_LEFT:
                return "BRACKET_LEFT";
            case BRACE_RIGHT:
                return "BRACE_RIGHT";
            case BRACE_LEFT:
                return "BRACE_LEFT";
            case DOT:
                return "DOT";
            case COMMA:
                return "COMMA";
            case COLON:
                return "COLON";
            case SEMICOLON:
                return "SEMICOLON";
            case INTERROGATION:
                return "INTERROGATION";
            case GRATER:
                return "GRATER";
            case LESS:
                return "LESS";
            case APOSTROPHE:
                return "APOSTROPHE";
            case QUOTATION:
                return "QUOTATION";
            case AMPERSAND:
                return "AMPERSAND";
            case PERCENT:
                return "PERCENT";
            case DOLLAR:
                return "DOLLAR";
            case SHARP:
                return "SHARP";
            case PIPE:
                return "PIPE";
            case UNDER_BAR:
                return "UNDER_BAR";
            case BACKSLASH:
                return "BACKSLASH";
            case WHITESPACE:
                return "WHITESPACE";
            default:
                return "IDENTIFIER";

        }
    };

}
