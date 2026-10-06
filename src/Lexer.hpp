#pragma once

#include <string>

#include "Token.hpp"

class Lexer {
public:
    explicit Lexer(std::string text) : text_(std::move(text)) {}

    token nextToken() {
        std::string subtext = "";

        for (auto t : text) {
            if (pos_ >= text_.size())
                return {TokenKind::End, ""};
        }
    }

private:
    int pos_ = 0;
    std::string text_;
};
