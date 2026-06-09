#include<iostream>
#include<vector>
#include "editor.h"
#include "tasks.cpp"

int main(int argc, char* argv[]) {
    Editor editor;
    insertChar(editor, 'H');
    std::cout << "Hello, World!" << std::endl;
    return 0;
}