#include <iostream>
#include <vector>
#include "editor.h"

void insertChar(Editor& editor, char c) {
    // Implementation for inserting a character at the current cursor position
  std::string &currentLine = editor.lines[editor.cursorRow];
  currentLine.insert(currentLine.begin() + editor.cursorCol, c);
  editor.cursorCol++;
}

void removeChar(Editor &editor){
   if(editor.cursorRow == 0 && editor.cursorCol == 0){
        return;
    }
    else if(editor.cursorCol > 0){
        std::string &currentLine = editor.lines[editor.cursorRow];
        currentLine.erase(editor.cursorCol - 1,1);
        editor.cursorCol--;
    }
    else{
        std::string &currentLine = editor.lines[editor.cursorRow];
        std::string &previousLine = editor.lines[editor.cursorRow - 1];
        int previousLineLength = previousLine.size();
        previousLine += currentLine;
        editor.lines.erase(editor.lines.begin() + editor.cursorRow);
        editor.cursorRow--;
        editor.cursorCol = previousLineLength;
    }
  
}

void insertNewLine(Editor &editor){
  std::string &currentLine = editor.lines[editor.cursorRow];
  std::string leftpart=currentLine.substr(0,editor.cursorCol);
  std::string rightpart=currentLine.substr(editor.cursorCol);
  currentLine=leftpart;
  editor.lines.insert(editor.lines.begin()+editor.cursorRow+1,rightpart);
  editor.cursorRow++;
  editor.cursorCol=0;
}

void moveCursorLeft(Editor& editor){
    if(editor.cursorCol > 0)
    {
        editor.cursorCol--;
    }
    else if(editor.cursorRow > 0)
    {
        editor.cursorRow--;
        editor.cursorCol =
            editor.lines[editor.cursorRow].size();
    }
}

void moveCursorRight(Editor &editor){
    if(editor.cursorCol < editor.lines[editor.cursorRow].size())
    {
        editor.cursorCol++;
    }
    else if(editor.cursorRow < editor.lines.size() - 1)
    {
        editor.cursorRow++;
        editor.cursorCol = 0;
    }
}

void moveCursorUp(Editor& editor){
    if(editor.cursorRow == 0)
        return;
    int desiredCol = editor.cursorCol;
    editor.cursorRow--;
    int lineLength = editor.lines[editor.cursorRow].size();
    editor.cursorCol = std::min(desiredCol, lineLength);
}

void moveCursorDown(Editor& editor){
    if(editor.cursorRow == editor.lines.size() - 1)
        return;
    int desiredCol = editor.cursorCol;
    editor.cursorRow++;
    int lineLength = editor.lines[editor.cursorRow].size();
    editor.cursorCol = std::min(desiredCol, lineLength);
}
void updateScroll(Editor& editor,int screenHeight){
    if(editor.cursorRow < editor.scrollRow)
    {
        editor.scrollRow = editor.cursorRow;
    }
    else if(editor.cursorRow >= editor.scrollRow + screenHeight)
    {
        editor.scrollRow = editor.cursorRow - screenHeight + 1;
    }
}