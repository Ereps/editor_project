#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios original_terminal;
struct termios terminal;

int main(int argc, char *argv[])
{
  // init terminal 
  tcgetattr(STDIN_FILENO,&original_terminal);
  cfmakeraw(&terminal);
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&terminal);
  char buffer[1024];
  int index_buffer = 0;
  char c;
  int rdr = read(STDIN_FILENO, &c, 1); 
  while(rdr == 1 && (c != 'q') ){
    buffer[index_buffer] = c;
    index_buffer++;
    printf("%c\n",c);
    if(c == '\r'){
      for (int i = 0;i < index_buffer;i++) {
        printf("%c | %d\n",buffer[i],index_buffer) ;
      }
    } 
    rdr = read(STDIN_FILENO, &c, 1); 
  };
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&original_terminal);
  return EXIT_SUCCESS;
}
