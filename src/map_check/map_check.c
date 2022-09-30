/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_check.c                                        :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:26:15 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:26:43 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_ch_map(t_in *dt)
{
	if (ft_ch_chars(dt) == -1)
		return (-1);
	dt->map = ft_add_columns(dt);
	if (ft_ch_personage(dt) == -1)
		return (-1);
	dt->map[(int)dt->yo][(int)dt->xo] = '0';
	if (ft_ch_spaces(dt) == -1)
		return (-1);
	if (ft_ch_close(dt) == -1)
		return (-1);
	if (!dt->map)
		return (-1);
	return (0);
}

int	ft_ch_chars(t_in *dt)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	n = 0;
	while (dt->map[++i])
	{
		j = -1;
		while (dt->map[i][++j])
		{
			if (dt->map[i][j] != '0' && dt->map[i][j] != '1' && dt->map[i][j]
				!= ' ')
			{
				if (dt->map[i][j] != 'N' && dt->map[i][j] != 'S'
					&& dt->map[i][j] != 'E' && dt->map[i][j] != 'W')
					return (printf ("Error\nBad char in map - "), -1);
				n++;
			}
		}
	}
	if (ft_ch_chars_aux(dt, n) == -1)
		return (-1);
	return (0);
}

int	ft_ch_chars_aux(t_in *dt, int n)
{
	int	i;
	int	j;

	if (n != 1)
		return (printf ("Error\nIncorrect personage number - "), -1);
	else
	{
		i = -1;
		while (dt->map[++i])
		{
			j = -1;
			while (dt->map[i][++j])
			{
				if (dt->map[i][j] != '0' && dt->map[i][j] != '1'
					&& dt->map[i][j] != ' ')
				{
					dt->xo = j + 0.5;
					dt->yo = i + 0.5;
				}
			}
		}
	}
	return (0);
}

int	ft_ch_personage(t_in *dt)
{
	int	i;
	int	j;
	int	n;

	i = -1;
	while (dt->map[++i])
	{
		j = -1;
		while (dt->map[i][++j])
		{
			if (dt->map[i][j] == 'N' || dt->map[i][j] == 'S' || dt->map[i][j]
				== 'E' || dt->map[i][j] == 'W')
			{
				n = ft_ch_personage_aux(i, j, dt);
				if (n == 1)
					return (printf ("Error\nPersonage inside limits - "), -1);
				else if (n == 2)
					return (printf ("Error\nPersonage in the air - "), -1);
				else if (n == 3)
					return (printf ("Error\nEncapsulated personage - "), -1);
			}
		}
	}
	return (0);
}

int	ft_ch_personage_aux(int i, int j, t_in *dt)
{
	dt->dir = dt->map[i][j];
	if (i == 0 || i == (dt->maxy - 1) || j == 0 || j == (dt->maxx - 1))
		return (1);
	else if (dt->map[i][j - 1] == ' ' || dt->map[i][j + 1] == ' ' || dt->map[i
		- 1][j] == ' ' || dt->map[i + 1][j] == ' ')
		return (2);
	else if (dt->map[i][j - 1] == '1' && dt->map[i][j + 1] == '1' && dt->map[i
		- 1][j] == '1' && dt->map[i + 1][j] == '1')
		return (3);
	return (0);
}
