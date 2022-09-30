/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:51:36 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 10:52:25 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

char	*ft_gnl(int fd)
{
	char	*buf;
	char	*rest;
	int		rb;

	rest = NULL;
	buf = (char *) malloc (sizeof (char) * 2);
	if (buf == NULL)
		return (NULL);
	while (ft_check (rest) == 0)
	{
		rb = read (fd, buf, 1);
		if (rb == 0)
		{
			free (buf);
			return (rest);
		}
		buf[1] = 00;
		rest = ft_copy (buf, rest);
	}
	rest = ft_update_rest (rest);
	free(buf);
	return (rest);
}

char	*ft_update_rest(char *rest)
{
	char	*aux;
	int		i;
	int		j;

	if (!rest)
		return (NULL);
	i = ft_strlen(rest);
	aux = (char *) malloc (sizeof(char) * (i));
	if (!aux)
		return (NULL);
	j = -1;
	while (++j < (i - 1))
		aux[j] = rest[j];
	aux[j] = 00;
	free (rest);
	return (aux);
}

char	*ft_dup(char *oldstr)
{
	int		sz;
	int		i;
	char	*newstr;

	if (!oldstr)
		return (NULL);
	i = -1;
	sz = ft_strlen(oldstr);
	newstr = (char *)malloc (sizeof(char) * (sz + 1));
	while (++i < sz)
		newstr[i] = oldstr[i];
	newstr[i] = 00;
	return (newstr);
}

char	*ft_copy(char *buf, char *rest)
{
	int		sz;
	int		i;
	char	*aux;

	if (!rest)
		aux = ft_dup(buf);
	else
	{
		sz = ft_strlen(rest);
		aux = (char *) malloc (sizeof(char) * (sz + 2));
		i = -1;
		while (++i < sz)
			aux[i] = rest[i];
		free (rest);
		aux[i] = buf[0];
		aux[i + 1] = 00;
	}
	return (aux);
}

int	ft_strlen(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}
