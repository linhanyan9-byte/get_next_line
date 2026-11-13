#define BUFFER_SIZE 8
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

char	*strjoin(char *storage, char *transporter)
{
	char	*join;
	size_t	len_storage;
	size_t	len_transporter;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	len_storage = 0;
	len_transporter = 0;
	while (storage[len_storage])
		len_storage++;
	while (transporter[len_transporter])
		len_transporter++;
	join = malloc(sizeof(char) * (len_storage + len_transporter + 1));
	if (!join)
		return (NULL);
	while (j < len_storage)
		join[i++] = storage[j++];
	j = 0;
	while (j < len_transporter)
		join[i++] = transporter[j++];
	join[i] = '\0';
	return (join);
}

int find_new_line(char *storage)
{
	int i;

	while (storage[i])
	{
		if (storage[i] == '\n')
			return (i);
		else
			i++;
	}
	return (0);
}

char *get_the_storage(int fd, char *storage, int *new_line_position)
{
    int read_byte;
    char *transporter;

    read_byte = 1;
    transporter = malloc(sizeof(char) * (BUFFER_SIZE + 1));
    if (!transporter)
        return (NULL);
    //right now storage is null
    if (!storage)
    {
        storage = malloc(1);
        if (!storage)
        {
            free(transporter);
            return (NULL);
        }
        storage[0] = '\0';
    }
    while (read_byte > 0 && *new_line_position == 0)
    {
        //if read_byte = 0, it means no end of file
        read_byte = read(fd, transporter, BUFFER_SIZE);
        *new_line_position = find_new_line(storage);
        storage = strjoin(storage, transporter);
    }
    //maybe there is new line in sthe storage, maybe there is no and its already the end of the file
    //but either way, we will deal with the storage in the next function
    if (read_byte == 0)
        return (NULL);
    return (storage);
}

char *return_new_line(char *storage, int *new_line_position, char *new_line)
{
    int storage_len;
    int i;

    i = 0;
    storage_len = 0;
    if (*new_line_position == 0)
    {
        while (storage[storage_len])
            storage_len++;
        new_line = malloc(sizeof(char) * (storage_len + 1));
        if (!new_line)
            return (NULL);
    }
    else
    {
        new_line = malloc(sizeof(char) * (*new_line_position + 1));
        if (!new_line)
            return (NULL);
    }
    while (storage[i])
    {
        if (*new_line_position != 0 && i == *new_line_position)
            break ;
        new_line[i] = storage[i];
        i++;
    }
    new_line[i] = '\0';
    return (new_line);
}

char *save_rest(char *storage, int *new_line_position)
{
    char *new_storage;
    int size;
    int len;
    int i;

    size = 0;
    len = 0;
    while (storage[len])
        len++;
    size = len - *new_line_position;
    new_storage = malloc(sizeof(char) * size);
    while (i < size)
    {
        new_storage[i] = storage[*new_line_position + i];
        i++;
    }
    new_storage[i] = '\0';
    return (new_storage);
}


char *get_next_line(int fd)
{
    static char *storage;
    char *new_line;
    int *new_line_position;

    *new_line_position = 0;
    if (fd < 0 || BUFFER_SIZE < 0)
        return (NULL);
    new_line = NULL;
    storage = NULL;
    //transport from file to the storage
    storage = get_the_storage(fd, storage, new_line_position);
    if (!storage)
        return (NULL);
    //get the new line in storage
    new_line = return_new_line(storage, new_line_position, new_line);
    //reput the rest back to the storage
    if (*new_line_position != 0)
    {
        storage = save_rest(storage, new_line_position);
        if (!storage)
            return (NULL);
    }
    return (new_line);
}

// A difficulty is to manipulate the size of the storage for the bytes of new line str

int main(int argc, char **argv)
{
    int fd;
    char *new_line;

    if (argc != 2)
        return (1);
    fd = open(argv[1], O_RDONLY);
    if (fd < 0)
        return (1);
    while (new_line)
    {
        new_line = get_next_line(fd);
        printf("%s", new_line);
        free(new_line);
    }
    close(fd);
    return (0);
}