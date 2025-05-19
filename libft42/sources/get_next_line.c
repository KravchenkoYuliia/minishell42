/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yukravch <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 18:49:14 by yukravch          #+#    #+#             */
/*   Updated: 2025/04/25 11:38:56 by yukravch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "libft.h"

char	*ft_cut_line(char *reserve)
{
	int	i;

	i = 0;
	while (reserve != NULL && reserve[i] && reserve[i] != '\n')
		i++;
	if (reserve != NULL && reserve[i] && reserve[i] == '\n')
		i++;
	ft_strcpy_gnl(reserve, &reserve[i]);
	return (reserve);
}

char	*ft_copy_from_buffer(char *reserve, char *buffer)
{
	int		i;
	int		j;
	char	*array;

	i = 0;
	j = 0;
	array = (char *)ft_calloc((ft_strlen(reserve) + ft_strlen(buffer) + 1), 1);
	if (!array || !reserve || !buffer)
		return (NULL);
	while (reserve[i] && reserve != NULL)
	{
		array[i] = reserve[i];
		i++;
	}
	while (buffer[j] && buffer != NULL)
	{
		array[i] = buffer[j];
		i++;
		j++;
	}
	array[i] = '\0';
	return (free(reserve), array);
}

char	*ft_get_line(char *full_reserve)
{
	char	*line;
	int		i;

	i = 0;
	while (full_reserve[i] && full_reserve[i] != '\n')
		i++;
	if (full_reserve[i] == '\n')
		i++;
	line = (char *)ft_calloc(sizeof(char), (i + 1));
	if (!line)
		return (free(full_reserve), NULL);
	i = 0;
	while (full_reserve != NULL && full_reserve[i] && full_reserve[i] != '\n')
	{
		line[i] = full_reserve[i];
		i++;
	}
	if (full_reserve[i] == '\n')
	{
		line[i] = full_reserve[i];
		i++;
	}
	line[i] = '\0';
	return (line);
}

char	*ft_read_buffer(int fd, char *reserve)
{
	char	*buffer;
	int		read_return;

	read_return = 1;
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (free(reserve), NULL);
	if (!reserve)
	{
		reserve = (char *)ft_calloc(1, 1);
		if (!reserve)
			return (NULL);
	}
	while (read_return != 0 && !ft_strchr_gnl(reserve, '\n'))
	{
		read_return = read(fd, buffer, BUFFER_SIZE);
		if (read_return < 0 || (read_return == 0 && reserve[0] == '\0'))
			return (free(reserve), free(buffer), reserve = NULL);
		buffer[read_return] = '\0';
		reserve = ft_copy_from_buffer(reserve, buffer);
		if (!reserve)
			return (free(reserve), NULL);
	}
	free(buffer);
	return (reserve);
}

char	*get_next_line(int fd)
{
	static char	*reserve[1024];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	reserve[fd] = ft_read_buffer(fd, reserve[fd]);
	if (!reserve[fd])
		return (free(reserve[fd]), NULL);
	line = ft_get_line(reserve[fd]);
	if (!line)
		return (NULL);
	reserve[fd] = ft_cut_line(reserve[fd]);
	return (line);
}
