#include "get_next_line.h"

char *strjoin(char *s1, char *s2)
{
    int len_s1;
    int len_s2;
    int i;
    int j;

    for (len_s1 = 0; s1[len_s1] != '\0'; len_s1++);
    for (len_s2 = 0; s2[len_s2] != '\0'; len_s2++);
    char *join;
    join = malloc(sizeof(char) * (len_s1 + len_s2 + 1));
     // TODO: check malloc
    // TODO: no need to have outerloop, remember to initialize i
    for (i = 0; i <= len_s1 + len_s2; i++)
    {
        for (j = 0; s1[j] != '\0'; j++)
        {
            join[i] = s1[j];
            i++;
        }
            
        for (j = 0; s2[j] != '\0'; j++)
        {
            join[i] = s2[j];
            i++;
        }
    }
    join[i] = '\0';
    return (join);
}

//mark the position of '\n'//
int postion(char *storage)
{
    int i = 0;
    if (!storage)                        
        return (-1);
    while (storage[i] != '\n' && storage[i])
    {
        i++;
    }
    if (storage[i] == '\0')
        return (-1);
    return (i);

    
}

//2 read the chunks of text, separated by the new line//

char *read_file(int fd, char *storage)
{
    //2.1 using read() to write in the memory of buffer, while be aware of how many bytes to put in//
    int byte_read;
    char *transporter;
    int i = 0;
    int new_line = 0;
    int j = 0;
 
    transporter = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    // TODO: check the malloc sucess
    
    //TODO: initializing storage, malloc a '\0' and dont forget to check the malloc

    //2.2 seach if there is '\n' written in the memory already//
    while (position(storage) == -1)
    {
        byte_read = read(fd, transporter, BUFFER_SIZE);
        if (byte_read < 0)
        //TODO:need to free the storage and the transporter//
            return (NULL);
        //TODO:forgot the end of line situation(what if byte_read == 0)
        
        transporter[byte_read] = '\0';

        //TODO: memory leak beaware!! better use temp and then free storage, and always remember to check melloc, if not able to allocate, free everythnig //
        storage = (strjoin(storage, transporter));

    }
    //TODO: need to free the transporter
    return (storage);
}



//3 extract the chunk//
char *line_extract(char *storage)
{
    char *line;
    int j = 0;
    int i = 0;
    
    //TODO:what if its end of line situation, or storage is a null pointer? you should return null
    
   
    //storage[j] should also be examined upon the \0
    while (storage[j] != '\n')
    {
        j++;
    }
    //you have to increase by one cause yoou have index incorrespondence!
    if (storage[j] == '\n')
        j++;
    //TODO: remember to return null if malloc is not done
    line = malloc(sizeof(char) * (j + 1));

    while (i < j)
    {
        line[i] = storage[i];
        i++;
    }

    line[i] = '\0';
    return (line);
}



char *get_next_line(int fd)
{
    static char *storage;
    char *line;
    char *temp;
    int position_;
 
    //1 validate the input//
    if (fd < 0 || read(fd, 0, 0) < 0 || BUFFER_SIZE <= 0)
        return NULL;
    //2 read the chunks of text, separated by the new line//
    storage = read_file(fd, storage);
    //3 extract the chunk，using line()//
    line = line_extract(storage);
    //4 save the rest for the next use, using next()//
    position_ = position(storage);
    //TODO:what if position = -1?

    //TODO: better having strjoin so you get the '\0' fixed as well; also you need to move the current pointer by one to start after '\n'
    temp = &storage[position_];
    // TODO: first transport then free
    free(storage);
    storage = temp;
    //5 return the line//
    return (line);
}

