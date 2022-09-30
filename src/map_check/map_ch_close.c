/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_ch_close.c                                     :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:18:14 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:19:01 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_ch_close(t_in *dt)
{
	int	i;
	int	j;
	int	max;

	i = -1;
	while (dt->map[++i])
	{
		max = dt->maxx - 1;
		while (dt->map[i][max] == ' ')
			max--;
		j = -1;
		while (dt->map[i][++j])
		{
			if (dt->map[i][j] == '0')
			{
				if (ft_ch_close_aux(i, j, max, dt) == -1)
				{
					printf ("Error\nNo closed map - ");
					return (-1);
				}
			}
		}
	}
	return (0);
}

int	ft_ch_close_aux(int i, int j, int max, t_in *dt)
{
	if (i == 0)
		return (-1);
	else if (i == dt->maxy - 1)
		return (-1);
	else
	{
		if (ft_ch_cl_aux_irow(i, j, max, dt) == -1)
			return (-1);
	}
	return (0);
}

int	ft_ch_cl_aux_irow(int i, int j, int max, t_in *dt)
{
	if (j == 0 || j == max)
		return (-1);
	else
	{
		if (ft_ch(i, j + 1, dt, 1) == -1 || ft_ch(i, j - 1, dt, 1) == -1
			|| ft_ch(i + 1, j, dt, 1) == -1 || ft_ch(i - 1, j, dt, 1) == -1)
		{
			return (-1);
		}
	}
	return (0);
}
