#pragma once

#include <string>

enum class TokenKind {
    Invalid,
    End,
    String,
    LeftParen,
    RightParen,
    Chygar,
}

struct Token {
    TokenKind kind;
    std::string value;
}

