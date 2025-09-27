#include "cursor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

struct cursor
{
    int cursor_x;
    int cursor_y;
};

void goto_cursor( int x, int y )
{
    char buffer_x[1024];
    char buffer_y[1024];
    sprintf( buffer_x, "%d", x );
    sprintf( buffer_y, "%d", y );
    char goto_string[4096] = "\033[";
    strcat( goto_string, buffer_x );
    strcat( goto_string, ";" );
    strcat( goto_string, buffer_y );
    strcat( goto_string, "H" );
    write( STDOUT_FILENO, goto_string, sizeof( char ) * strlen( goto_string ) );
}
