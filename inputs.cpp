#include "editor.h"

KeyEvent readKey()
{
    char c;
    if(read(STDIN_FILENO, &c, 1) != 1){
        return {KEY_UNKNOWN, 0};
    }
    if(c == 127 || c == 8)
    {
        return {KEY_BACKSPACE, 0};
    }
    if(c == '\r' || c == '\n')
    {
        return {KEY_ENTER, 0};
    }
    if(c == 27) {
        char seq[2];
        if(read(STDIN_FILENO, &seq[0], 1) != 1) return {KEY_ESCAPE, 0};
        if(read(STDIN_FILENO, &seq[1], 1) != 1) return {KEY_ESCAPE, 0};
        if(seq[0] == '[') {
            switch(seq[1])
            {
                case 'A':
                    return {KEY_UP, 0};

                case 'B':
                    return {KEY_DOWN, 0};

                case 'C':
                    return {KEY_RIGHT, 0};

                case 'D':
                    return {KEY_LEFT, 0};
            }
        }

        return {KEY_UNKNOWN, 0};
    }

    return {KEY_CHARACTER, c};
}