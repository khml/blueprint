# -*- coding:utf-8 -*-

from collections import OrderedDict

HEADER_FILE_NAME = "../headers/TokenKind.hpp"
IMPL_FILE_NAME = "../src/TokenKind.cpp"

TokenKindName = [
    "ADD",
    "SUB",
    "ASTERISK",
    "SLASH",
    "AT",
    "EQUAL",
    "PARENTHESISE_RIGHT",
    "PARENTHESIS_LEFT",
    "BRACKET_RIGHT",
    "BRACKET_LEFT",
    "BRACE_RIGHT",
    "BRACE_LEFT",
    "DOT",
    "COMMA",
    "COLON",
    "SEMICOLON",
    "INTERROGATION",
    "GRATER",
    "LESS",
    "APOSTROPHE",
    "QUOTATION",
    "AMPERSAND",
    "PERCENT",
    "DOLLAR",
    "SHARP",
    "PIPE",
    "UNDER_BAR",
    "BACKSLASH",
    "WHITESPACE",
    "IDENTIFIER",
]

TokenKindValue = [
    "+",
    "-",
    "*",
    "/",
    "@",
    "=",
    ")",
    "(",
    "]",
    "[",
    "}",
    "{",
    ".",
    ",",
    ":",
    ";",
    "?",
    ">",
    "<",
    "\\'",
    "\"",
    "&",
    "%",
    "$",
    "#",
    "|",
    "_",
    "\\\\",
    " ",
    "",
]

TokenKind = OrderedDict()
for name, value in zip(TokenKindName, TokenKindValue):
    TokenKind[name] = value

HEADER_TEMPLATE = """\
// This File is Auto Generated.
#ifndef BLUEPRINT_TOKEN_KIND_HPP
#define BLUEPRINT_TOKEN_KIND_HPP

#include <string>

namespace Token
{{
{content}\
    TokenKind toTokenKind(char val);
    
    std::string fromTokenKind(TokenKind val);
}}

#endif //BLUEPRINT_TOKEN_KIND_HPP
"""

IMPL_TEMPLATE = """\
// This File is Auto Generated.

#include <string>

#include "TokenKind.hpp"

namespace Token
{{
{content}\
}}
"""

ENUM_TEMPLATE = """\
    enum TokenKind
    {{\
{impl}
        LINE_START,
        LINE_END,
    }};

"""

KIND_FORMAT = "\n        {kind}, /* {value} */"

SWITCH_FORMAT = """\
    {return_type} {name}({arg_type} val)
    {{
        switch (val)
        {{
{impl}
        }}
    }};

"""

CASE_FORMAT = """\
            {case}:
                return {value};
"""


def main():
    enum_impl = ""
    to_enum_impl = ""
    to_str_impl = ""
    for kind_name, kind_value in TokenKind.items():
        enum_impl += KIND_FORMAT.format(kind=kind_name, value=kind_value)
        to_enum_case = "default" if kind_name == "IDENTIFIER" else "case '{}'".format(kind_value)
        to_enum_impl += CASE_FORMAT.format(case=to_enum_case, value=kind_name)
        to_str_case = "default" if kind_name == "IDENTIFIER" else "case {}".format(kind_name)
        to_str_impl += CASE_FORMAT.format(case=to_str_case, value='"{}"'.format(kind_name))
    enum_impl = ENUM_TEMPLATE.format(impl=enum_impl)
    to_enum_impl = SWITCH_FORMAT.format(return_type="TokenKind", arg_type="char", name="toTokenKind", impl=to_enum_impl)
    to_str_impl = SWITCH_FORMAT.format(return_type="std::string", arg_type="TokenKind", name="fromTokenKind",
                                       impl=to_str_impl)

    header_content = enum_impl
    impl_content = to_enum_impl + to_str_impl

    header_content = HEADER_TEMPLATE.format(content=header_content)
    impl_content = IMPL_TEMPLATE.format(content=impl_content)

    with open(HEADER_FILE_NAME, "w") as f:
        f.write(header_content)

    with open(IMPL_FILE_NAME, "w") as f:
        f.write(impl_content)


if __name__ == '__main__':
    main()
