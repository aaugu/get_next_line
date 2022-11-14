/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:13:03 by aaugu             #+#    #+#             */
/*   Updated: 2022/11/14 20:48:10 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

ssize_t	get_line_break(int fd, char **stash);
void	append_buf_to_stash(char *buf, char **stash);
char	*get_line(char **stash);

char	*get_next_line(int fd)
{
	static char	*stash;
	ssize_t		read_bytes;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = ft_strdup("");
	read_bytes = get_line_break(fd, &stash);
	line = get_line(&stash);
	return (line);
}

/*
-> Until a '\n' is found in stash
	-> Read
	-> Then append buf on stash
-> Free buf as it is not needed anymore
-> Returns how many bytes where read on last read
*/
ssize_t	get_line_break(int fd, char **stash)
{
	char	buf[BUFFER_SIZE + 1];
	ssize_t	read_bytes;

	read_bytes = 0;
	while (ft_strchr(*stash, '\n') == NULL)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		buf[read_bytes] = '\0';
		append_buf_to_stash(buf, stash);
	}
	return (read_bytes);
}

void	append_buf_to_stash(char *buf, char **stash)
{
	char	*temp;

	temp = ft_strjoin(*stash, buf);
	free(*stash);
	*stash = temp;
}

//Manipulating stash to get the line and delete that line part from stash
char	*get_line(char **stash)
{
	char	*temp;
	char	*line;
	int		i;

	i = 0;
	while (*stash[i] != '\n')
		i++;
	line = ft_substr(*stash, 0, i + 1);
	temp = ft_substr(*stash, i + 1, ft_strlen(*stash) - i + 1);
	free(*stash);
	*stash = temp;
	return (line);
}

int	main(void)
{
	int	fd;

	fd = open("numbers.dict", O_RDONLY);
	if (fd == -1)
	{
		write(1, "Dict Error\n", 11);
		return (0);
	}
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	printf("%s", get_next_line(fd));
	return (0);
}

/*
Fonctions externes > read, malloc, free

- Tant qu'on est pas à la fin du fd, lire de la taille du buffer
	- Concaténer ou joindre le buff dans une variable tampon
	- Vérifier si '\n' est dans la variable tampon
		-> si oui arrêter la boucle
		-> sinon continuer à lire

- Après avoir trouvé '\n' dans tampon
	- stocker toute la string jusqu'à "\n" compris dans une variable line
	- retirer du tampon la partie qui a été stockée dans line

- Renvoyer line

*/
