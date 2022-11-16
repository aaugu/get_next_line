/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:13:03 by aaugu             #+#    #+#             */
/*   Updated: 2022/11/16 16:29:28 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "string.h"

int		ft_get_line_break(int fd, char **stash);
char	*ft_get_line(char **stash);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	int			read_bytes;

	if ((fd < 0 || fd >= 255) || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	if (!stash)
		return (NULL);
	read_bytes = ft_get_line_break(fd, &stash);
	if ((read_bytes == -1) || (read_bytes == 0 && !ft_strlen(stash)))
	{
		free(stash);
		stash = NULL;
		return (NULL);
	}
	line = ft_get_line(&stash);
	return (line);
}

// Until a '\n' is found in stash, read and then append buff on stash
int	ft_get_line_break(int fd, char **stash)
{
	char	*buff;
	char	*temp;
	ssize_t	read_bytes;

	read_bytes = 1;
	buff = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buff)
		return (-1);
	while (!ft_strchr(*stash, '\n'))
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1 || read_bytes == 0)
			break ;
		buff[read_bytes] = '\0';
		temp = ft_strjoin(*stash, buff);
		if (!temp)
			return (-1);
		free(*stash);
		*stash = temp;
	}
	free(buff);
	return ((int)read_bytes);
}

// Manipulating stash to get the line
// Manipulating stash to delete the line part from it and getting checkpoint
char	*ft_get_line(char **stash)
{
	char	*line;
	char	*temp;
	int		i;

	i = 0;
	while ((*stash)[i] != '\n' && (*stash)[i])
		i++;
	line = ft_substr(*stash, 0, i + 1);
	if (!line)
		return (NULL);
	temp = ft_substr(*stash, i + 1, ft_strlen(*stash) - i + 1);
	if (!temp)
		return (NULL);
	free(*stash);
	*stash = temp;
	return (line);
}
/*
int	main(void)
{
	int	fd;
	int	i = 0;

	fd = open("numbers.dict", O_RDONLY);
	if (fd == -1)
	{
		write(1, "Dict Error\n", 11);
		close(fd);
		return (0);
	}
	while (i < 5)
	{
		printf("Line > %s\n", get_next_line(fd));
		i++;
	}
	close(fd);
	return (0);
}
*/
