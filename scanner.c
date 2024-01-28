#include <string.h>

#include "common.h"
#include "scanner.h"

typedef struct Scanner
{
    const char *start;
    const char *current;
    int line;
} Scanner;

Scanner scanner;

void initScanner(const char *source)
{
    scanner.start = source;
    scanner.current = source;
    scanner.line = 1;
}

static bool isAtEnd()
{
    return *scanner.current == '\0';
}

static Token makeToken(TokenType type)
{
    Token token;
    token.type = type;
    token.start = scanner.start;
    token.length = (int)(scanner.current - scanner.start);
    token.line = scanner.line;
    return token;
}

// message must outlive the error token. This is normally the case for static strings.
static Token errorToken(const char *message)
{
    Token token;
    token.type = TOKEN_ERROR;
    token.start = message;
    token.length = strlen(message);
    token.line = scanner.line;
    return token;
}

Token scanToken()
{
    scanner.start = scanner.current;
    if (isAtEnd())
        return makeToken(TOKEN_EOF);
    return errorToken("Unexpected character.");
}
