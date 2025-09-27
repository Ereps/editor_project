#ifndef __FILE_MANAGEMENT_H__
#define __FILE_MANAGEMENT_H__

/*
 *Open the file
 */
void init_file( char* file_name );

/*
 * Print the content of the file
 */
void print_file();
/*
 *Close the file
 */
void exit_file();
/*
 * Write in the file opened
 */
void write_file( char* buffer );

#endif // __FILE_MANAGEMENT_H__
