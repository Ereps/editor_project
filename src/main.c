#include "file_management.h"
#include <termios.h>
#include <unistd.h>
struct termios original_terminal;
struct termios terminal;

const char* CLEAR_TERM = "\033[2J";

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
        write( STDOUT_FILENO, &rdr, sizeof( int ) );
        if ( rdr == 1 )
            write( STDOUT_FILENO, &c, sizeof( char ) );
        if ( c == '\r' )
        {
            printf( "toto" );
            c = '\n';
        }
        buffer[index_buffer] = c;
        index_buffer++;
        for ( int i = 0; i < index_buffer; i++ )
        {
        }

        if ( c == '\n' )
        {
            printf( "tata" );
        }

        rdr = read( STDIN_FILENO, &c, 1 );
    }
    tcsetattr( STDIN_FILENO, TCSAFLUSH, &original_terminal );
    return EXIT_SUCCESS;
}
