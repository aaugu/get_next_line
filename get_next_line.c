/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaugu <marvin@42lausanne.ch>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/10 10:13:03 by aaugu             #+#    #+#             */
/*   Updated: 2022/11/10 16:36:22 by aaugu            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*temp;
	char		*line;
	char		*buf;
	int			i;

	temp = NULL;
	while (read(fd, buf, BUFFER_SIZE))
	{
		if (temp)
			temp = ft_strjoin_gnl(temp, buf);
		else
			temp = ft_strdup_gnl(buf);
		i = ft_strchr_gnl(temp);
		if (i)
			break ;
	}
	line = ft_strlcpy(line, temp, i - 1);
	temp = ft_substr(temp, i, ft_strlen(temp) - i);
	return (line);
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
