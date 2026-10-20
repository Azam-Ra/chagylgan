# Working in Chagylgan

## Learning and explanation preferences

The user is learning through this project and wants thorough answers across sessions. Explain how things work under the hood, not just the immediate fix. When relevant, cover underlying language rules, the reason for diagnostics, object lifetimes and memory behavior, and design tradeoffs. Use concrete examples tied to the project, explain unfamiliar terminology, and distinguish conceptual explanations from suggested code changes. Do not default to terse answers unless the user requests brevity.

## Scope and implementation status

Chagylgan is an early C++ implementation of Suu, a compiled language with Kyrgyz keywords. The repository currently contains a lexer prototype, not a working compiler. There is no parser, AST, code generator, or runtime yet. The language examples in `docs/suu/README.md` describe more functionality than the implementation supports; do not treat them as executable acceptance tests.

## Build and validation

No established build, run, test, lint, or formatting commands are documented. The current `CMakeLists.txt` contains only `project(chagylgan)`: it defines no executable or test targets and selects no C++ standard. Successful CMake configuration would not validate the source.

A direct syntax check from the repository root was exercised during documentation discovery:

```sh
clang++ -fsyntax-only src/main.cpp
```

This checks the sole translation unit and its included headers without creating build artifacts. It currently fails because of existing source errors:

- `src/Token.hpp` lacks terminating semicolons after the enum and struct.
- `src/Lexer.hpp` uses `token` instead of `Token`, refers to `text` instead of `text_`, and contains an unfinished conditional and `isCyrillic` body.
- `src/main.cpp` attempts to cast a whole `Token` to `int`, rather than its kind.

Establish the current baseline before attributing these failures to a new change. There is no automated test runner or assertion-based test suite. `test/lang/01.suu` is a sample input only; no code loads or checks it. No CI configuration was found.

## Component relationships

- `src/Token.hpp` defines the shared token representation: `TokenKind` and a `Token` carrying a kind and string value. The kinds currently cover invalid input, end of input, strings, parentheses, and `Chygar`.
- `src/Lexer.hpp` includes `Token.hpp` and holds the source string and cursor. Lexer methods are defined inside the class in the header; there is no separate lexer translation unit. `nextToken()` is the boundary consumed by the demo, but its implementation is unfinished.
- `src/main.cpp` constructs a lexer for the hard-coded string `чыгар("Салам!")`, repeatedly requests tokens, attempts to print their numeric kind and value, and stops at `TokenKind::End`. This is a token-dump demo, not execution of Suu's print statement. Its command-line arguments are unused, so passing a `.suu` filename does not read that file.
- `docs/suu/README.md` contains the alphabet, reserved words, and proposed language examples. Consult it when changing lexical rules; the root `README.md` contains only the project title.
- `test/lang/01.suu` contains `чыгар("Салам, дүйнө!")`, a different string from the hard-coded demo.

Changes to the token contract need to account for both the lexer and the demo. The demo's loop depends on the lexer eventually returning `TokenKind::End`.

## Language and encoding pitfalls

The language document restricts keyword spelling to the 36 lowercase Kyrgyz letters it lists, including `ң`, `ө`, and `ү`. Some listed keywords contain spaces, such as `же эгер` and `ар бир`; do not assume every documented keyword is one whitespace-delimited word.

The source and examples contain UTF-8 Cyrillic text, while the lexer stores `std::string` and its unfinished character helper takes `char`. Byte iteration is not Unicode character iteration: a single `char` cannot represent a UTF-8 Kyrgyz letter. Preserve the original spelling and account for that distinction when implementing character classification or cursor movement.

The language examples also mix visually similar Latin and Cyrillic characters (for example, `a` in the first loop condition and `caн` in the second example). They are design notes, not a complete or internally validated grammar. Avoid silently deriving identifier or keyword rules from those lookalikes.

## Local conventions and working-tree care

The small existing C++ sample uses four-space indentation, same-line opening braces, `#pragma once` headers, PascalCase type and enum names, camelCase methods, and trailing underscores on private fields. It uses standard-library types directly and defines types in the global namespace. There is no formatter configuration or dependency manifest establishing further conventions.

At documentation discovery, `src/Lexer.hpp` and `src/main.cpp` already had local modifications, and `CMakeLists.txt` was untracked. Check `git status` before editing and preserve unrelated work; these incomplete files may be actively edited. Do not repair the compiler simply to make a documentation-only task pass validation.
