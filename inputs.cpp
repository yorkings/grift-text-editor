#include "editor.h"

KeyEvent readKey()
{
    char c;

    if(read(STDIN_FILENO, &c, 1) != 1)
    {
        return {KEY_UNKNOWN, 0, false};
    }

    if(c == 127 || c == 8)
    {
        return {KEY_BACKSPACE, 0, false};
    }

    if(c == '\r' || c == '\n')
    {
        return {KEY_ENTER, 0, false};
    }

    // Ctrl+A through Ctrl+Z
    if(c >= 1 && c <= 26)
    {
        return {
            KEY_CHARACTER,
            (char)('a' + c - 1),
            true
        };
    }

    if(c == 27)
    {
        char seq[2];
        if(read(STDIN_FILENO, &seq[0], 1) != 1)
        {
            return {KEY_ESCAPE, 0, false};
        }

        if(read(STDIN_FILENO, &seq[1], 1) != 1)
        {
            return {KEY_ESCAPE, 0, false};
        }

        if(seq[0] == '[')
        {
            switch(seq[1])
            {
                case 'A':
                    return {KEY_UP, 0, false};

                case 'B':
                    return {KEY_DOWN, 0, false};

                case 'C':
                    return {KEY_RIGHT, 0, false};

                case 'D':
                    return {KEY_LEFT, 0, false};
            }
        }

        return {KEY_UNKNOWN, 0, false};
    }

    return {KEY_CHARACTER, c, false};
}