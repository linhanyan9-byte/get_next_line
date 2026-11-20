/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: halin <halin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/18 15:33:45 by halin             #+#    #+#             */
/*   Updated: 2026/11/19 10:12:10 by halin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 8
# endif
# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>

int		ft_strlen(char *str);
char	*get_the_line(char *storage);
char	*store_rest(char *storage);
char	*get_next_line(int fd);
char	*strjoin(char *storage, char *transporter);
int		position(char *storage);
void	*clean(char *to_clean);
char	*transporting(int *read_byte, char *storage, int fd);
char	*get_storage(char *storage, int fd, int *read_byte);
char	*get_new_stor(char *storage, char *new_stor, int i, int j);

#endif