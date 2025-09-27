#include "file_management.h"
#include "key.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

int main( int argc, char* argv[] )
{
    struct termios original_terminal;
    struct termios terminal;

    char* file_name = "tmp/toto.tmp";

    // clear terminal
    // system("clear");

    // init terminal
    tcgetattr( STDIN_FILENO, &original_terminal );
    terminal = original_terminal;
    cfmakeraw( &terminal );
    // minimum number of byte needed before read can return
    terminal.c_cc[VMIN] = 0;
    // number of seconds before read quit
    terminal.c_cc[VTIME] = 1;
    tcsetattr( STDIN_FILENO, TCSAFLUSH, &terminal );

    key_management();

    tcsetattr( STDIN_FILENO, TCSAFLUSH, &original_terminal );
    return EXIT_SUCCESS;
}
