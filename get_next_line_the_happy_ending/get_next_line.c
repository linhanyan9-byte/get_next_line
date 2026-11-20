/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halin <halin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:16:44 by halin             #+#    #+#             */
/*   Updated: 2026/11/19 11:46:36 by halin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

char	*get_the_line(char *storage)
{
	char	*new_line;
	int		len;
	int		i;

	i = 0;
	len = 0;
	if (!storage || storage[0] == '\0')
		return (NULL);
	while (storage[len] && storage[len] != '\n')
		len++;
	if (storage[len] == '\n')
		len++;
	new_line = malloc(sizeof(char) * (len + 1));
	if (!new_line)
		return (NULL);
	while (i < len)
	{
		new_line[i] = storage[i];
		i++;
	}
	new_line[i] = '\0';
	return (new_line);
}

char	*get_new_stor(char *storage, char *new_stor, int i, int j)
{
	while (storage[j])
	{
		new_stor[i++] = storage[j];
		j++;
	}
	new_stor[i] = '\0';
	free(storage);
	return (new_stor);
}

char	*store_rest(char *storage)
{
	char	*new_stor;
	int		i;
	int		size_stor;
	int		j;

	i = 0;
	new_stor = NULL;
	if (!storage)
		return (NULL);
	size_stor = ft_strlen(storage);
	if (position(storage) != -1)
	{
		new_stor = malloc(sizeof(char) * (size_stor - position(storage)));
		if (!new_stor)
			return (NULL);
	}
	else
	{
		free(storage);
		return (NULL);
	}
	j = position(storage) + 1;
	return (get_new_stor(storage, new_stor, i, j));
}

char	*get_next_line(int fd)
{
	static char	*storage;
	char		*line;
	int			read_byte;

	read_byte = 1;
	line = NULL;
	storage = get_storage(storage, fd, &read_byte);
	line = get_the_line(storage);
	storage = store_rest(storage);
	return (line);
}

/* int	main(int argc, char **argv)
{
	int		fd;
	char	*new_line;

	new_line = NULL;
	fd = 0;
	fd = open(argv[1], O_RDONLY);
	if (argc != 2)
		return (1);
	new_line = get_next_line(fd);
	printf("%s", new_line);
	while (new_line)
	{
		free(new_line);
		new_line = get_next_line(fd);
		printf("%s", new_line);
	}
	return (0);
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
} */