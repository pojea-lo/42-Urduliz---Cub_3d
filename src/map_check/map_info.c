/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_info.c                                         :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:39:00 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/10/04 11:16:40 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

char	**ft_get_info(int fd, char *argv, t_in *dt)
{
	int		i;
	int		j;
	char	*line;

	i = ft_count_info (fd);
	if (i == 0)
		return (NULL);
	dt->info = (char **) malloc (sizeof(char *) * (i + 1));
	if (!dt->info)
		return (NULL);
	fd = open(argv, O_RDWR);
	line = ft_gnl(fd);
	j = -1;
	while (line)
	{
		if (fd_copy_info(dt, line) == 0)
			dt->info[++j] = ft_dup(line);
		else if (fd_copy_info(dt, line) == -1)
			return (ft_free_breakmap(dt, j, line), NULL);
		free (line);
		line = ft_gnl(fd);
	}
	dt->info[++j] = NULL;
	return (close(fd), dt->info);
}

int	fd_copy_info(t_in *dt, char *line)
{	
	int		i;

	while (line)
	{
		i = 0;
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] != 00)
		{
			if (line[i] == '1' && dt->findmap == 0)
				dt->findmap = 1;
			else if (line[i] == '1' && dt->findmap == 2)
				return (-1);
			return (0);
		}
		else
		{
			if (dt->findmap == 1)
				dt->findmap = 2;
			return (1);
		}
	}
	return (1);
}

int	ft_count_info(int fd)
{
	int		i;
	int		n;
	char	*line;

	n = 0;
	line = ft_gnl(fd);
	while (line)
	{
		i = -1;
		while (line[++i] == ' ' && line[i])
			i++;
		if (line[i] != 00)
			n++;
		free (line);
		line = ft_gnl(fd);
	}
	close(fd);
	return (n);
}
