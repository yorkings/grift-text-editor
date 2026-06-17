#pragma once
#include <string>
#include <vector>
#include<termios.h>
#include <unistd.h>
#include <algorithm>
#include <cstdlib>

constexpr int SCREEN_HEIGHT = 30;
constexpr int SCREEN_WIDTH = 80;

struct Editor{
    std::vector<std::string> lines;
    int cursorRow;
    int cursorCol;
    int scrollRow;
    int scrollCol;
    std::string filename;
    std::string statusMessage;
    int statusMessageTimer;
    bool waitingForInput;
    Editor() : cursorRow(0), cursorCol(0),scrollRow(0),scrollCol(0), waitingForInput(false) {
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
    bool ctrl;
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

void normalizeCursor(Editor& editor);
void moveTerminalCursor(int row, int col);
void refreshCursor(Editor& editor);

void updateScroll(Editor& editor,int screenHeight);
void handle_input(Editor &editor, KeyEvent event,bool &running);

// file handling functions
bool loadFile(Editor &editor, const std::string &filename);
bool saveFile(const Editor &editor);
std::string promptForFilename();