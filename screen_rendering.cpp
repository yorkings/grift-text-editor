#include <iostream>
#include <vector>
#include "editor.h" 

struct termios originalTermios;
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &originalTermios);
    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ECHO | ICANON); // Disable echo and canonical mode
    raw.c_cc[VMIN] = 0; // Minimum number of bytes before read() returns
    raw.c_cc[VTIME] = 1; // Timeout for read() in tent
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode(){
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&originalTermios);
}


void clearScreen() {
    // Clear the console screen
    std::cout << "\033[2J\033[1;1H"; // ANSI escape codes to clear screen and move cursor to top-left
}

void  moveTerminalCursor(int row, int col){
    std::cout << "\033[" << row + 1 << ";" << col + 1 << "H";
}

ScreenBuffer buildScreenBuffer(const Editor& editor,int screenHeight) {
    ScreenBuffer buffer;
    int start= editor.scrollRow;
    int end=std::min(start+screenHeight,(int)editor.lines.size());
    for(int i=start;i<end;i++){
        buffer.rows.push_back(editor.lines[i]);
    }
    return buffer;
}
    

void renderScreen(const Editor& editor) {
    clearScreen();
    ScreenBuffer buffer = buildScreenBuffer(editor, 24); // Assuming a screen height of 24 lines
    for (const auto &line : buffer.rows) {
        std::cout << line <<"\n";
    }
    moveTerminalCursor(editor.cursorRow, editor.cursorCol);
    if (editor.cursorRow < editor.lines.size()) {
        char currentChar = ' ';
        if (editor.cursorCol < editor.lines[editor.cursorRow].size()) {
            currentChar = editor.lines[editor.cursorRow][editor.cursorCol];
        }
        std::cout << "\033[7m" << currentChar << "\033[0m";        
        // Move cursor back so the terminal cursor doesn't overlap weirdly 
        // if you decide to show it later, or just leave it hidden.
        moveTerminalCursor(editor.cursorRow-editor.scrollRow, editor.cursorCol); 
    }
    // Ensure system cursor is hidden for a clean look
    std::cout << "\033[?25l"; 
    std::cout.flush();

}
