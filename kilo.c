//
// Created by 87747 on 2023/10/22.
//
#include <stdlib.h>
#include <termios.h>
#include <unistd.h>

void enableRawMode();
void disableRawMode();

struct termios orig_termios;



int main() {
    char c;
    //read() returns the number of bytes that it read, and will return 0 when it reaches the end of a file
    while (read(STDIN_FILENO, &c, 1) == 1 && c != 'q');
    return 0;
}

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    atexit(disableRawMode);

    struct  termios raw = orig_termios;
    raw.c_lflag &= ~(ECHO);

    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}

void disableRawMode(){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);
}