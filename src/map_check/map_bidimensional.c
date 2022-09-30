/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_bidimensional.c                                :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:03:25 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:16:48 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_create_bid(t_in *dt)
{
	int	i;
	int	j;

	if (ft_ch_line_first(dt->info) == -1)
		return (-1);
	dt->map = (char **) malloc (sizeof(char *) * (ft_count_fd (dt->info, 2)
				+ 1));
	if (!dt->map)
		return (-1);
	i = -1;
	j = -1;
	while (dt->info[++i])
	{
		if (ft_check_line (dt->info[i], 2) == 0)
		{
			dt->map[++j] = ft_dup(dt->info[i]);
		}
	}
	dt->map[++j] = NULL;
	if (ft_data_map(dt) == -1)
		return (-1);
	return (0);
}

int	ft_ch_line_first(char **info)
{
	int	i;
	int	j;

	i = -1;
	while (info[++i])
	{
		j = 0;
		while (info[i][j] == ' ')
			j++;
		if (info[i][j] != 'N' && info[i][j] != 'S' && info[i][j] != 'E'
				&& info[i][j] != 'W' && info[i][j] != 'C' && info[i][j] != 'F'
				&& info[i][j] != '1' && info[i][j] != '0')
		{
			printf ("Error\nForbiden line text\n");
			return (-1);
		}
	}
	return (0);
}

int	ft_count_fd(char **info, int n)
{
	int	i;
	int	r;

	i = 0;
	r = 0;
	while (info[i])
	{
		if (ft_check_line (info[i], n) == 0)
			r++;
		i++;
	}
	return (r);
}

int	ft_check_line(char *line, int n)
{
	int	i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if (n == 1 && line[i] && line[i + 1])
	{
		if ((((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O')
				|| (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W'
					&& line [i + 1] == 'E')) && line[i + 2] == ' ')
			return (0);
	}
	else if (n == 2 && line[i])
	{
		if (((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O')
			|| (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W'
				&& line [i + 1] == 'E'))
			return (1);
		if ((line[i] == 'F' || line[i] == 'C') && (line[i + 1] == ' '))
			return (1);
		else
			return (0);
	}
	return (1);
}

int	ft_data_map(t_in *dt)
{
	int	j;

	dt->maxy = 0;
	dt->maxx = 0;
	while (dt->map[dt->maxy])
	{
		j = ft_strlen(dt->map[dt->maxy]);
		if (j > dt->maxx)
			dt->maxx = j;
		dt->maxy++;
	}
	if (dt->maxy < 4 || dt->maxx < 4)
	{
		printf ("Error\nBad map dimension - Error map\n");
		return (-1);
	}
	return (0);
}
