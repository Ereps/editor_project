#include "key.h"
#include "cursor.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

const char* CLEAR_TERM = "\033[2J";
const char* RETURN_TERM = "\r";

int key_management()
{
    char buffer[1024];
    int  index_buffer = 0;
    char c = 0;
    int  rdr = read( STDIN_FILENO, &c, 1 );
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
                // reset cursor
                goto_cursor( 0, 0 );
                write( STDOUT_FILENO, CLEAR_TERM,
                       sizeof( char ) * strlen( CLEAR_TERM ) );
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

    return EXIT_SUCCESS;
}
