#include "editor.h"

void handle_input(Editor &editor, KeyEvent event,bool &running){
     if (editor.waitingForInput) {
        return;
    }
    // Handle shortcuts first
    if(event.ctrl){
        switch(event.character)
        {
            case 'q':
                running = false;
                break;

            case 's':
                if(saveFile(editor)){
                    editor.statusMessage = "File saved successfully.";
                    editor.statusMessageTimer = 2;
                } else {
                    editor.statusMessage = "Error saving file.";
                    editor.statusMessageTimer = 5;
                }
                break;
        }

        return;
    }

    switch(event.type){
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
    }
    updateScroll(editor, SCREEN_HEIGHT);
}