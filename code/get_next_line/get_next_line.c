/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: leberton <leberton@42vienna.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/09 17:32:04 by leberton          #+#    #+#             */
/*   Updated: 2025/05/11 19:09:57 by leberton         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*free_buffer(char *buffer, char *read_content, ssize_t read_size)
{
	char	*temp;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	temp = (char *)ft_calloc(ft_strlen(buffer) + read_size + 1, sizeof(char));
	if (!temp)
		return (NULL);
	while (buffer[i])
	{
		temp[i] = buffer[i];
		i++;
	}
	while (j < (size_t)read_size)
	{
		temp[i + j] = read_content[j];
		j++;
	}
	free(buffer);
	return (temp);
}

char	*prepare_for_next(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*new_buffer;

	i = 0;
	j = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	if (!buffer[i])
	{
		free(buffer);
		return (NULL);
	}
	new_buffer = (char *)ft_calloc((ft_strlen(buffer) - i), sizeof(char));
	if (!new_buffer)
		return (NULL);
	i++;
	while (buffer[i])
		new_buffer[j++] = buffer[i++];
	free(buffer);
	return (new_buffer);
}

char	*get_line_from_buffer(char *buffer)
{
	size_t	i;
	size_t	j;
	char	*line;

	i = 0;
	while (buffer[i] && buffer[i] != '\n')
		i++;
	line = (char *)ft_calloc(i + 2, sizeof(char));
	if (!line)
		return (NULL);
	j = 0;
	while (j < i)
	{
		line[j] = buffer[j];
		j++;
	}
	if (buffer[i] == '\n')
		line[i] = '\n';
	return (line);
}

char	*rdff(int fd, char *buffer)
{
	ssize_t		read_size;
	char		*read_content;

	if (!buffer)
		buffer = (char *)ft_calloc(1, 1);
	read_content = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!read_content)
		return (NULL);
	while (1)
	{
		read_size = read(fd, read_content, BUFFER_SIZE);
		if (read_size <= 0)
		{
			free(read_content);
			if (buffer[0] == '\0')
				return (free_and_return_null(buffer));
			return (buffer);
		}
		buffer = free_buffer(buffer, read_content, read_size);
		if (ft_strchr(buffer, '\n'))
			break ;
	}
	free(read_content);
	return (buffer);
}

char	*get_next_line(int fd)
{
	static char	*buffer;
	char		*line;

	if (fd < 0 || BUFFER_SIZE < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	buffer = rdff(fd, buffer);
	if (buffer == NULL)
		return (NULL);
	line = get_line_from_buffer(buffer);
	buffer = prepare_for_next(buffer);
	return (line);
}
