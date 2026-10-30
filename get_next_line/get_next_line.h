#ifndef GET_NEXT_LINE
#define GET_NEXT_LINE

#include <unistd.h>
#include <stdlib.h>
char    *get_next_line(int fd);
char    *strjoin(char *s1, char *s2);
char    *read_file(int fd, char *storage);
char    *line_extract(char *storage);
int     position(char *storage);

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 8
#endif

#endif

