#include <iostream>

#include "editor.h"


int main()
{
    enableRawMode();
    atexit(disableRawMode);
    Editor editor;
    renderScreen(editor);
    bool running = true;
    while(running){
        KeyEvent event = readKey();
        handle_input(editor, event,running);
        refreshCursor(editor);
        renderScreen(editor);
    }
       

    return 0;
}