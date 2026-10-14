#pragma once

#include <string>

enum class TokenKind {
    End,
    String,
    LeftParen,
    RightParen,
    Chygar,
};

struct Token {
    TokenKind kind;
    std::string value;
};

