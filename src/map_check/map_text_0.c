/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_text_0.c                                       :+:      :+:    :+:   */
/*   By: jsmith <marvi@42.fr>                         +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:43:29 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:45:11 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_create_text(t_hook *hk)
{
	int	i;
	int	fd;

	if (ft_count_tex(hk->dt->info) == -1)
	{
		printf ("Error\nError in number of valid textures - ");
		return (-1);
	}
	if (ft_create_text_tex(hk->dt) == -1)
		return (-1);
	i = -1;
	while (hk->dt->tex[++i])
	{
		fd = open(hk->dt->tex[i], O_RDONLY);
		if (fd == -1)
		{
			printf ("Error\nTexture file doesn`t exist - ");
			return (-1);
		}
		close (fd);
		hk->dt->texture[i] = ft_charge_tex(hk, i);
	}
	if (ft_create_color(hk) == -1)
		return (-1);
	return (0);
}

int	ft_count_tex(char **info)
{
	int		i;
	int		j;
	int		n[4];

	i = -1;
	while (++i < 4)
		n[i] = 0;
	i = -1;
	while (info[++i])
	{
		if (ft_check_line (info[i], 1) == 0)
		{
			j = ft_count_tex_aux(info[i]);
			if (j == -1)
				return (-1);
			else
				n[j] += 1;
		}
	}
	if (ft_count_tex_aux_bi(n) == -1)
		return (-1);
	return (0);
}

int	ft_count_tex_aux(char *info)
{
	int	j;

	j = 0;
	while (info[j] == ' ')
		j++;
	if (info[j] == 'N')
		return (0);
	else if (info[j] == 'S')
		return (1);
	else if (info[j] == 'E')
		return (2);
	else if (info[j] == 'W')
		return (3);
	return (-1);
}

int	ft_count_tex_aux_bi(int *n)
{
	int	i;

	i = -1;
	while (++i < 4)
	{
		if (n[i] != 1)
			return (-1);
	}
	return (0);
}

int	ft_create_text_tex(t_in *dt)
{
	int	i;
	int	j;

	dt->tex = (char **)malloc(sizeof(char *) * 5);
	if (!dt->tex)
		return (-1);
	i = -1;
	j = -1;
	while (dt->info[++i])
	{
		if (ft_check_line (dt->info[i], 1) == 0)
		{
			dt->tex[++j] = ft_dup(dt->info[i]);
			dt->tex[j] = ft_regen_tex(dt->tex[j]);
		}
		if (dt->tex[j] == NULL || ft_ch_extension(dt->tex[j]) == -1)
		{
			dt->tex[++j] = NULL;
			printf ("Error\nBad imput in textures - ");
			return (-1);
		}
	}
	dt->tex[++j] = NULL;
	return (0);
}
