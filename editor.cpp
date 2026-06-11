#include<iostream>
#include<vector>
#include <cstdlib>
#include "editor.h"

int main() {
    enableRawMode();
    atexit(disableRawMode);
    Editor editor;
    while (1){       
       KeyEvent event = readKey();
       switch (event.type) {
           case KEY_CHARACTER:
               insertChar(editor, event.character);
               break;
           case KEY_BACKSPACE:
               removeChar(editor);
               break;
           case KEY_ENTER:
               insertNewLine(editor);
               break;
           case KEY_UP:
               moveCursorUp(editor);
               break;
           case KEY_DOWN:
               moveCursorDown(editor);
               break;
           case KEY_LEFT:
               moveCursorLeft(editor);
               break;
           case KEY_RIGHT:
               moveCursorRight(editor);
               break;
            case KEY_ESCAPE:
               exit(0);               
           default:
               break;

       }
         renderScreen(editor);
    
    }
    disableRawMode();
    return 0;
}