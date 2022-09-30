/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_color_0.c                                      :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:33:03 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:35:56 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_create_color(t_hook *hk)
{
	if (ft_count_col(hk->dt->info) == -1)
	{
		printf ("Error\nError in number of valid colors - ");
		return (-1);
	}
	if (ft_create_text_col(hk->dt) == -1)
		return (-1);
	return (0);
}

int	ft_count_col(char **info)
{
	int	i;
	int	j;
	int	n[2];

	i = -1;
	while (++i < 2)
		n[i] = 0;
	i = -1;
	while (info[++i])
	{
		j = ft_count_col_aux(info[i]);
		if (j == 0 || j == 1)
			n[j] += 1;
	}
	i = -1;
	while (++i < 2)
	{
		if (n[i] != 1)
			return (-1);
	}
	return (0);
}

int	ft_count_col_aux(char *info)
{
	int	j;

	j = 0;
	while (info[j] == ' ')
		j++;
	if (info[j] == 'C')
	{
		if (info[++j] && info[j] == ' ')
			return (0);
	}
	else if (info[j] == 'F')
	{
		if (info[++j] && info[j] == ' ')
			return (1);
	}
	return (-1);
}

int	ft_create_text_col(t_in *dt)
{
	int		i;
	int		j;

	i = 0;
	j = -1;
	while (dt->info[i])
	{
		if (ft_ch_line_two (dt->info[i]) == 0
			|| ft_ch_line_two(dt->info[i]) == 1)
		{
			++j;
			if (ft_dup_atoi(dt, dt->info[i], j) == -1)
			{
				printf ("Error\nBad imput in colors - ");
				return (-1);
			}
		}
		else if (ft_ch_line_two (dt->info[i]) == -1)
		{
			printf ("Error\nBad imput in colors - ");
			return (-1);
		}
		i++;
	}
	return (0);
}

int	ft_ch_line_two(char *line)
{
	int	i;
	int	j;

	if (!line)
		return (-1);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	j = i;
	if ((line[i] == 'F' || line[i] == 'C') && line [i + 1] == ' ')
	{
		while (line[++i])
		{
			if (line[i] != ',' && line[i] != ' ' && !(line[i] > 47 && line[i]
					< 58))
				return (-1);
		}
		if (line[j] == 'C')
			return (0);
		return (1);
	}
	return (2);
}
