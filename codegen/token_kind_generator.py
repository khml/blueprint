# -*- coding:utf-8 -*-

from collections import OrderedDict

HEADER_FILE_NAME = "../headers/TokenKind.hpp"
IMPL_FILE_NAME = "../src/TokenKind.cpp"
NAME_SPACE = "tokenKind"

TokenKind = OrderedDict([
    ('ADD', '+'),
    ('SUB', '-'),
    ('ASTERISK', '*'),
    ('SLASH', '/'),
    ('AT', '@'),
    ('EQUAL', '='),
    ('PARENTHESISE_RIGHT', ')'),
    ('PARENTHESIS_LEFT', '('),
    ('BRACKET_RIGHT', ']'),
    ('BRACKET_LEFT', '['),
    ('BRACE_RIGHT', '}'),
    ('BRACE_LEFT', '{'),
    ('DOT', '.'),
    ('COMMA', ','),
    ('COLON', ':'),
    ('SEMICOLON', ';'),
    ('INTERROGATION', '?'),
    ('GRATER', '>'),
    ('LESS', '<'),
    ('APOSTROPHE', "\\'"),
    ('QUOTATION', '\\"'),
    ('AMPERSAND', '&'),
    ('PERCENT', '%'),
    ('DOLLAR', '$'),
    ('SHARP', '#'),
    ('PIPE', '|'),
    ('UNDER_BAR', '_'),
    ('BACKSLASH', '\\\\'),
    ('WHITESPACE', ' '),
    ('NEW_LINE', '\\n'),
    ('IDENTIFIER', '')
])


class Header:
    HEADER_TEMPLATE = """\
// This File is Auto Generated.
#ifndef BLUEPRINT_TOKEN_KIND_HPP
#define BLUEPRINT_TOKEN_KIND_HPP

#include <string>

namespace {namespace}
{{
{content}\
    TokenKind toTokenKind(std::string& val);
    
    std::string fromTokenKind(TokenKind val);
}}

#endif //BLUEPRINT_TOKEN_KIND_HPP
"""

    ENUM_TEMPLATE = """\
    enum TokenKind
    {{\
{impl}
        LINE_START,
    }};
"""

    ITEM_FORMAT = "\n        {kind}, /* {value} */"

    def __init__(self):
        header_content = self.HEADER_TEMPLATE.format(namespace=NAME_SPACE, content=self._enum)
        with open(HEADER_FILE_NAME, "w") as f:
            f.write(header_content)

    @property
    def _enum(self):
        enum_impl = ""
        for kind_name, kind_value in TokenKind.items():
            enum_impl += self.ITEM_FORMAT.format(kind=kind_name, value=kind_value)
        return self.ENUM_TEMPLATE.format(impl=enum_impl)


class Impl:
    IMPL_TEMPLATE = """\
// This File is Auto Generated.

#include <map>

#include "TokenKind.hpp"

namespace {namespace}
{{
{content}\
}}
"""

    SWITCH_FORMAT = """\
    {return_type} {name}({arg_type} val)
    {{
        switch (val)
        {{
            case LINE_START:
                return "LINE_START";
{impl}
        }}
    }};

"""

    CASE_FORMAT = """\
            {case}:
                return {value};
"""

    MAP_FORMAT = """\
    static std::map<std::string, TokenKind> toTokenKindMap()
    {{
        return std::map<std::string, TokenKind> {{
{impl}\
        }};
    }}

"""

    def __init__(self):
        impl_content = self._map + self._to_enum + self._to_str
        impl_content = self.IMPL_TEMPLATE.format(namespace=NAME_SPACE, content=impl_content)
        with open(IMPL_FILE_NAME, "w") as f:
            f.write(impl_content)

    @property
    def _to_str(self):
        to_str_impl = ""
        for kind_name, kind_value in TokenKind.items():
            to_str_case = "default" if kind_name == "IDENTIFIER" else "case {}".format(kind_name)
            to_str_impl += self.CASE_FORMAT.format(case=to_str_case, value='"{}"'.format(kind_name))
        return self.SWITCH_FORMAT.format(return_type="std::string", arg_type="TokenKind", name="fromTokenKind",
                                         impl=to_str_impl)

    @property
    def _to_enum(self):
        return """\
    TokenKind toTokenKind(std::string& val)
    {
        static std::map<std::string, TokenKind> dictionary = toTokenKindMap();

        auto iter = dictionary.find(val);
        if ( iter != end(dictionary) ) {
            return iter->second;
        } else {
            return IDENTIFIER;
        }
    };

"""

    @property
    def _map(self):
        map_impl = ""
        item_format = "            {{\"{string}\", {kind}}},\n"
        for kind_name, kind_value in TokenKind.items():
            map_impl += item_format.format(string=kind_value, kind=kind_name) if kind_name != "IDENTIFIER" else ""
        return self.MAP_FORMAT.format(impl=map_impl)


def main():
    Header()
    Impl()


if __name__ == '__main__':
    main()