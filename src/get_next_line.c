/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mreymond <mreymond@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 16:07:24 by mreymond          #+#    #+#             */
/*   Updated: 2022/02/08 16:07:27 by mreymond         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*read_lines(char *str, int fd, char *buffer)
{
	int	lecture;

	lecture = 1;
	while (lecture != 0 && ft_strchr(str, '\n') == NULL)
	{
		lecture = read(fd, buffer, BUFFER_SIZE);
		if (lecture == -1)
		{
			if (buffer)
				free(buffer);
			return (NULL);
		}
		buffer[lecture] = '\0';
		if (!str)
			str = ft_strdup("");
		str = ft_strjoin_gnl(str, buffer);
	}
	return (str);
}

char	*get_next_line(int fd)
{
	char		*buffer;
	char		*tmp;
	char		*returned_line;
	static char	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	buffer = malloc(BUFFER_SIZE + 1);
	if (buffer == NULL)
		return (NULL);
	tmp = line;
	tmp = read_lines(tmp, fd, buffer);
	if (buffer)
	{
		free(buffer);
		buffer = NULL;
	}
	returned_line = clean_end_of_line(tmp);
	line = clean_start_of_line(tmp);
	return (returned_line);
}
