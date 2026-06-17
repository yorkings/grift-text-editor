#include <iostream>
#include <vector>
#include "editor.h" 

struct termios originalTermios;
void enableRawMode() {
    tcgetattr(STDIN_FILENO, &originalTermios);
    struct termios raw = originalTermios;
    raw.c_lflag &= ~(ECHO | ICANON); // Disable echo and canonical mode
    raw.c_iflag &= ~(IXON | ICRNL); // Disable Ctrl-S/Q and carriage return to newline translation
    raw.c_cc[VMIN] = 0; // Minimum number of bytes before read() returns
    raw.c_cc[VTIME] = 1; // Timeout for read() in tent
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode(){
    tcsetattr(STDIN_FILENO,TCSAFLUSH,&originalTermios);
    std::cout << "\033[?25h"; // Show the cursor again
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
    ScreenBuffer buffer = buildScreenBuffer(editor, SCREEN_HEIGHT);
    for (const auto &line : buffer.rows) {
        std::cout << line <<"\n";
    }
    std::cout << "\033[7m";  // Reverse video
    std::cout << editor.statusMessage.substr(0, 80);
    std::cout << std::string(80 - editor.statusMessage.length(), ' ');
    std::cout << "\033[0m";
    moveTerminalCursor(editor.cursorRow, editor.cursorCol);
    if (editor.cursorRow < editor.lines.size()) {
        char currentChar = ' ';
        if (editor.cursorCol < editor.lines[editor.cursorRow].size()) {
            currentChar = editor.lines[editor.cursorRow][editor.cursorCol];
        }
        std::cout << "\033[7m" << currentChar << "\033[0m";        
        // Move cursor back so the terminal cursor doesn't overlap weirdly 
        moveTerminalCursor(editor.cursorRow-editor.scrollRow, editor.cursorCol); 
    }
    // Ensure system cursor is hidden for a clean look
    std::cout << "\033[?25l"; 
    std::cout.flush();

}
