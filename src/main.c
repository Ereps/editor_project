#include "file_management.h"
#include <string.h>
#include <termios.h>
#include <unistd.h>
struct termios original_terminal;
struct termios terminal;

const char* CLEAR_TERM = "\033[2J";
const char* RETURN_TERM = "\r";

int cursor_x = 0;
int cursor_y = 0;

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

int main( int argc, char* argv[] )
{
    int    BYPASS_ERROR = argc;
    char** BYPASS_ARGV = argv;
    char*  file_name = "tmp/toto.tmp";
    char   buffer[1024];
    int    index_buffer = 0;
    char   c = 0;

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
    int rdr = read( STDIN_FILENO, &c, 1 );
    while ( ( c != 'q' ) )
    {
        // printf( "%s", CLEAR_TERM );
        // key pressed
        if ( rdr == 1 )
        {
            if ( c == 27 )
            { // Escape sequence start, skip for now
                // You might handle arrow keys etc here
                continue;
            }
            else if ( c == 127 || c == 8 )
            {
                index_buffer--;
            }
            else if ( c == '\r' || c == '\n' )
            {
                printf( "\nEnter pressed!\n" );
            }
            else if ( c == 3 )
            { // Ctrl+C to exit
                break;
            }
            else
            {
                // reset cursor
                goto_cursor( 0, 0 );
                write( STDOUT_FILENO, CLEAR_TERM,
                       sizeof( char ) * strlen( CLEAR_TERM ) );
                // ca reste a la find de la ligne car y'a le buffer qui write
                // tout write( STDOUT_FILENO, RETURN_TERM, sizeof( char ) );
                buffer[index_buffer] = c;
                index_buffer++;
                // TODO changer dans le programme pour que tout les appuis de \r
                // soit directement convertie en \r\n
                for ( int i = 0; i < index_buffer; i++ )
                {
                    int temp = 1;
                    if ( buffer[i] == '\r' || buffer[i] == '\n' )
                    {
                        write( STDOUT_FILENO, "\r\n", sizeof( char ) * 2 );
                    }
                    else
                        write( STDOUT_FILENO, &buffer[i], sizeof( char ) );
                }
            }
        }
        rdr = read( STDIN_FILENO, &c, 1 );
    }
    tcsetattr( STDIN_FILENO, TCSAFLUSH, &original_terminal );
    return EXIT_SUCCESS;
}
