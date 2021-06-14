// This program can show each character and its ASCII representations each line as a byte
// fun fact backspace is 1 byte whereas delete is 4 bytes :)
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <termio.h>
#include <unistd.h>


struct termios orig_termios;

void disableRawMode() {

	tcsetattr(STDIN_FILENO, TCSAFLUSH, &orig_termios);

}


void enableRawMode() {
	tcgetattr(STDIN_FILENO, &orig_termios);
	atexit(disableRawMode);

	struct termios raw = orig_termios;
	raw.c_lflag &= ~(ECHO | ICANON);
	tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
}


int main() {
	enableRawMode();
	char c;
	while (read(STDIN_FILENO, &c, 1) ==1 && c != 'q') {
		if (iscntrl(c)) {
			printf("%d\n", c);
		} else {
			printf("%d ('%c')\n", c, c);
		}
	
	}
	return 0;
}
