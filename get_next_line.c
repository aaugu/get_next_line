/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:13:03 by aaugu             #+#    #+#             */
/*   Updated: 2022/11/15 14:16:27 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_break(int fd, char *stash);
char	*get_line(char *stash);
char	*get_new_stash(char *stash);

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;

	printf("%d", fd);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!stash)
		stash = ft_strdup("");
	stash = get_line_break(fd, stash);
	if (stash == NULL)
		return (NULL);
	line = get_line(stash);
	stash = get_new_stash(stash);
	return (line);
}

// Until a '\n' is found in stash, read and then append buff on stash
char	*get_line_break(int fd, char *stash)
{
	char	buff[BUFFER_SIZE + 1];
	ssize_t	read_bytes;

	read_bytes = 1;
	while (!ft_strchr(stash, '\n') || read_bytes == 0)
	{
		read_bytes = read(fd, buff, BUFFER_SIZE);
		if (read_bytes == -1)
			return (NULL);
		buff[read_bytes] = '\0';
		stash = ft_strjoin(stash, buff);
	}
	return (stash);
}

//Manipulating stash to get the line
char	*get_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	while (stash[i] != '\n' && !stash[i])
		i++;
	line = ft_substr(stash, 0, i + 1);
	return (line);
}

//Manipulating stash to delete the line part from it and getting checkpoint
char	*get_new_stash(char *stash)
{
	int		i;

	i = 0;
	while (stash[i] != '\n')
		i++;
	stash = ft_substr(stash, i + 1, ft_strlen(stash) - i + 1);
	return (stash);
}
/*
int	main(void)
{
	int	fd;

	fd = open("numbers.dict", O_RDONLY);
	if (fd == -1)
	{
		close(fd);
		write(1, "Dict Error\n", 11);
		return (0);
	}
	printf("Line > %s", get_next_line(fd));
	printf ("===========\n");
	printf("Line > %s", get_next_line(fd));
	printf ("===========\n");
	printf("Line > %s", get_next_line(fd));
	printf ("===========\n");
	close(fd);
	return (0);
}
*/