#include <iostream>
#include<fstream>
#include "editor.h"

std::string promptForFilename(Editor &editor) {
    editor.waitingForInput = true;    
    // Save cursor position and move to bottom
    std::cout << "\033[s";
    std::cout << "\033[" << SCREEN_HEIGHT << ";1H";
    std::cout << "\033[K";
    std::cout << "Save as (Enter to save, ESC to cancel): " << std::flush;
    std::cout << "\033[?25h";  // Show cursor    
    std::string filename;    
    // Read input in raw mode
    while (true) {
        char c;
        if (read(STDIN_FILENO, &c, 1) != 1) continue;
        
        if (c == '\r' || c == '\n') {  // Enter key
            break;
        } 
        else if (c == 27) {  // ESC key
            filename.clear();
            break;
        }
        else if ((c == 127 || c == 8) && !filename.empty()) {  // Backspace
            filename.pop_back();
            std::cout << "\b \b";
            std::cout.flush();
        }
        else if (c >= 32 && c <= 126) {  // Printable characters
            filename += c;
            std::cout << c;
            std::cout.flush();
        }
    }
    
    // Clean up prompt
    std::cout << "\033[?25l";  // Hide cursor
    std::cout << "\033[u";     // Restore cursor position
    std::cout << "\033[J";     // Clear from cursor to bottom
    std::cout.flush();    
    // Flush any remaining input
    tcflush(STDIN_FILENO, TCIFLUSH);    
    editor.waitingForInput = false;
    return filename;
}

bool loadFile(Editor &editor, const std::string &filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }
    editor.lines.clear();
    std::string line;
    while (std::getline(file,line)){
        editor.lines.push_back(line);
    }
    if(editor.lines.empty()){
        editor.lines.push_back("");
    }
    editor.filename=filename;
    return true;
}

bool saveFile(const Editor &editor) {
    if (editor.filename.empty()) {
        std::string filename = promptForFilename(const_cast<Editor&>(editor));
        if (filename.empty()) { 
            filename = "untitled.txt";
        }
        const_cast<Editor&>(editor).filename = filename; // Update the filename in the editor
    }
    std::ofstream file(editor.filename);
    if (!file.is_open()) {
        return false;
    }
    for(size_t i=0;i<editor.lines.size();i++){
        file << editor.lines[i];
        if(i+1<editor.lines.size()){
            file << "\n";
        }
    }
    return true;
}