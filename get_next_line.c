/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:13:03 by aaugu             #+#    #+#             */
/*   Updated: 2022/11/14 13:26:29 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_line_break(int fd, char *stash);

char	*get_next_line(int fd)
{
	static char	*stash;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	stash = get_line_break(fd, stash);
	return (stash);
}

char	*get_line_break(int fd, char *stash)
{
	char	*buf;
	char	*temp;

	buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	buf[BUFFER_SIZE] = '\0';
	stash = ft_strdup("");
	while (ft_strchr(stash, '\n') == NULL)
	{
		read(fd, buf, BUFFER_SIZE);
		if (stash[0] == '\0')
			stash = ft_strdup(buf);
		else
		{
			temp = ft_strjoin(stash, buf);
			free(stash);
			stash = temp;
		}
	}
	free(buf);
	return (stash);
}
/*
char	*get_line(char *line, char *stash)
{
}
*/

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
