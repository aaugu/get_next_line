/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/17 09:59:00 by aaugu             #+#    #+#             */
/*   Updated: 2022/11/17 11:04:04 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

int		ft_get_line_break(int fd, char **stash);
char	*ft_get_line(char **stash);
void	ft_free(char **p);

char	*get_next_line(int fd)
{
	static char	*stash[MAX_FD];
	char		*line;
	int			read_bytes;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > MAX_FD)
		return (NULL);
	if (!stash[fd])
		stash[fd] = ft_strdup("");
	if (!stash[fd])
		return (NULL);
	read_bytes = ft_get_line_break(fd, &stash[fd]);
	if ((read_bytes == -1) || (read_bytes == 0 && !ft_strlen(stash[fd])))
	{
		ft_free(&stash[fd]);
		return (NULL);
	}
	line = ft_get_line(&stash[fd]);
	if (!line)
	{
		ft_free(&stash[fd]);
		return (NULL);
	}
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
		{
			read_bytes = -1;
			break ;
		}
		free(*stash);
		*stash = temp;
	}
	free(buff);
	return ((int)read_bytes);
}

// Manipulating stash to get the line
// And delete the line part from it and getting checkpoint
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
	{
		ft_free(&line);
		return (NULL);
	}
	free(*stash);
	*stash = temp;
	return (line);
}

void	ft_free(char **p)
{
	free(*p);
	*p = NULL;
}
