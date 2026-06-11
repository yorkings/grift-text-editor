#pragma once
#include <string>
#include <vector>
#include<termios.h>
#include <unistd.h>
#include <algorithm>

struct Editor{
    std::vector<std::string> lines;
    int cursorRow;
    int cursorCol;
    int scrollRow;
    Editor() : cursorRow(0), cursorCol(0),scrollRow(0) {
        lines.push_back("");

    }
};

enum KeyType {
    KEY_UNKNOWN,
    KEY_ESCAPE,
    KEY_BACKSPACE,
    KEY_ENTER,
    KEY_UP,
    KEY_DOWN,
    KEY_LEFT,
    KEY_RIGHT,
    KEY_CHARACTER
};

struct KeyEvent {
    KeyType type;
    char character; 
};

struct  ScreenBuffer {
    std::vector<std::string>rows;
};

KeyEvent readKey();

void enableRawMode();
void disableRawMode();

void insertChar(Editor& editor, char c);
void removeChar(Editor &editor);
void insertNewLine(Editor &editor);
void moveCursorLeft(Editor& editor);
void moveCursorRight(Editor &editor);
void moveCursorUp(Editor& editor);
void moveCursorDown(Editor& editor);  
void renderScreen(const Editor& editor);
void clearScreen();  

void updateScroll(Editor& editor,int screenHeight);

