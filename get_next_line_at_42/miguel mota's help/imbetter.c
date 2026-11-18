#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#define BUFFER_SIZE 5

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

int find_line(char *toret)
{
	int i = 0;
	while (toret[i])
	{
		if (toret[i] == '\n')
			return (1);
		i++;
	}
	return (0);	
}

void	clean_buffer(char *buffer)
{
	int i = 0;
	int j = 0;

	while (buffer[i] && buffer[i] != '\n')
		i++;
	while (buffer[i])
	{
		buffer[j] = buffer[i + 1];
		i++;
		j++;		
	}
}

void	clean_line(char *buffer)
{
	int i = 0;

	while (buffer[i] && buffer[i] != '\n')
		i++;
	buffer[i + 1] = '\0';
}

char *get_next_line(int fd)
{
	static char buffer[BUFFER_SIZE];
	char *toret;
	size_t read_byte = 1;
	
	toret = calloc(1, 1);
	if (strlen(buffer) != 0)
	{
		toret = strjoin(toret, buffer);
		clean_buffer(buffer);
	}
	while (read_byte > 0 && find_line(toret) == 0)
	{
		read_byte = read(fd, buffer, BUFFER_SIZE);
		if (read_byte < 0)
		{
			free(toret);
			return (NULL);			
		}
		buffer[read_byte] = '\0';
		toret = strjoin(toret, buffer);
	}
	clean_line(toret);
	clean_buffer(buffer);
	if (read_byte == 0)
		return (NULL);
	return (toret);
}

int main(int ac, char **av)
{
	char *string;

	if (ac == 2)
	{
		int fd = open(av[1], O_RDONLY);
		string = get_next_line(fd);
		while (string)
		{
			printf("%s", string);
			free(string);
			string = get_next_line(fd);
		}
	}
}
