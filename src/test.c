#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>

struct termios original_terminal;
struct termios terminal;

int main(int argc, char *argv[])
{

  // clear terminal
  system("clear"); 

  // init terminal 
  tcgetattr(STDIN_FILENO,&original_terminal);
  terminal = original_terminal;
  cfmakeraw(&terminal);
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&terminal);
  char buffer[1024];
  int index_buffer = 0;
  char c;
  int rdr = read(STDIN_FILENO, &c, 1); 
  while(rdr == 1 && (c != 'q') ){
    buffer[index_buffer] = c;
    index_buffer++;
    if (c == '\r') {
    c = '\n';
}
    if(c == '\n'){
      for (int i = 0;i < index_buffer;i++) {
        printf("%c | %d\r\n",buffer[i],index_buffer) ;
}
      }
     
    rdr = read(STDIN_FILENO, &c, 1); 
  }
  tcsetattr(STDIN_FILENO,TCSAFLUSH,&original_terminal);
  return EXIT_SUCCESS;
}
