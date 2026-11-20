/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halin <halin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 14:18:32 by halin             #+#    #+#             */
/*   Updated: 2026/11/19 11:30:31 by halin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

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

int	position(char *storage)
{
	int	i;

	i = 0;
	while (storage[i] && storage[i] != '\n')
		i++;
	if (storage[i] == '\n')
		return (i);
	else
		return (-1);
}

void	*clean(char *to_clean)
{
	free(to_clean);
	return (NULL);
}

char	*transporting(int *read_byte, char *storage, int fd)
{
	char	*temp_stor;
	char	*transporter;

	temp_stor = NULL;
	temp_stor = storage;
	transporter = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	while (*read_byte > 0 && position(storage) == -1)
	{
		*read_byte = read(fd, transporter, BUFFER_SIZE);
		if (*read_byte < 0)
		{
			free(storage);
			return (clean(transporter));
		}
		if (*read_byte == 0)
			break ;
		transporter[*read_byte] = '\0';
		temp_stor = storage;
		storage = strjoin(temp_stor, transporter);
		free(temp_stor);
		if (!storage)
			return (clean(transporter));
	}
	free(transporter);
	return (storage);
}

char	*get_storage(char *storage, int fd, int *read_byte)
{
	if (storage == NULL)
	{
		storage = malloc(1);
		if (!storage)
			return (NULL);
		storage[0] = '\0';
	}
	return (transporting(read_byte, storage, fd));
}
