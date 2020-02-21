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


class Header:
    HEADER_TEMPLATE = """\
// This File is Auto Generated.
#ifndef BLUEPRINT_TOKEN_KIND_HPP
#define BLUEPRINT_TOKEN_KIND_HPP

#include <string>

namespace TokenKind
{{
{content}\
    TokenKind toTokenKind(char val);
    
    std::string fromTokenKind(TokenKind val);
}}

#endif //BLUEPRINT_TOKEN_KIND_HPP
"""

    ENUM_TEMPLATE = """\
    enum TokenKind
    {{\
{impl}
    }};
"""

    ITEM_FORMAT = "\n        {kind}, /* {value} */"

    def __init__(self):
        header_content = self.HEADER_TEMPLATE.format(content=self._enum)
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

#include <string>

#include "TokenKind.hpp"

namespace TokenKind
{{
{content}\
}}
"""

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

    def __init__(self):
        impl_content = self._to_enum + self._to_str
        impl_content = self.IMPL_TEMPLATE.format(content=impl_content)
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
        to_enum_impl = ""
        for kind_name, kind_value in TokenKind.items():
            to_enum_case = "default" if kind_name == "IDENTIFIER" else "case '{}'".format(kind_value)
            to_enum_impl += self.CASE_FORMAT.format(case=to_enum_case, value=kind_name)
        return self.SWITCH_FORMAT.format(return_type="TokenKind", arg_type="char", name="toTokenKind",
                                         impl=to_enum_impl)


def main():
    Header()
    Impl()


if __name__ == '__main__':
    main()
