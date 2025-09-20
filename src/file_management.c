#include "file_management.h"
FILE* file_ptr_to_modify;
FILE* file_ptr_to_print;

void print_file()
{
    rewind( file_ptr_to_print );
    char buffer[1024];
    while ( fgets( buffer, 1024, file_ptr_to_print ) != NULL )
    {
        printf( "%s\r\n", buffer );
    }
}

void init_file( char* file_name )
{
    file_ptr_to_modify = fopen( file_name, "a" );
    file_ptr_to_print = fopen( file_name, "r" );
    // TODO error routine
}

void exit_file()
{
    fclose( file_ptr_to_modify );
    fclose( file_ptr_to_print );
}

void write_file( char* buffer )
{
    fputs( buffer, file_ptr_to_modify );
}
