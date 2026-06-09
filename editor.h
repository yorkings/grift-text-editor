#pragma once
#include <string>
#include <vector>
struct Editor
{
    std::vector<std::string> lines;
    int cursorRow;
    int cursorCol;
    Editor() : cursorRow(0), cursorCol(0) {
        lines.push_back(""); // Start with an empty line
    }
};
void insertChar(Editor& editor, char c);