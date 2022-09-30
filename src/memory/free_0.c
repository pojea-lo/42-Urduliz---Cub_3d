/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_0.c                                           :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:48:05 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:48:36 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	ft_free_structur(t_hook *hk)
{
	if (hk->gr)
	{
		free(hk->gr);
		hk->gr = NULL;
	}
	if (hk)
	{
		free(hk);
		hk = NULL;
	}
}

void	ft_free(t_in *dt)
{
	int	i;

	if (dt->info)
	{
		i = -1;
		while (dt->info[++i])
			free (dt->info[i]);
		free (dt->info);
		dt->info = NULL;
	}
	if (dt->map)
	{
		i = -1;
		while (dt->map[++i])
			free (dt->map[i]);
		free (dt->map);
		dt->map = NULL;
	}
	ft_free_aux(dt);
}

void	ft_free_aux(t_in *dt)
{
	int	i;

	if (dt->tex)
	{
		i = -1;
		while (dt->tex[++i])
			free (dt->tex[i]);
		free (dt->tex);
		dt->tex = NULL;
	}
	if (dt->color)
	{
		if (dt->color[0])
			free (dt->color[0]);
		if (dt->color[1])
			free (dt->color[1]);
		free (dt->color);
		dt->color = NULL;
	}
}

void	ft_free_hk(t_hook *hk)
{
	int	i;

	if (hk->dt->info)
	{
		i = -1;
		while (hk->dt->info[++i])
			free (hk->dt->info[i]);
		free (hk->dt->info);
		hk->dt->info = NULL;
	}
	if (hk->dt->map)
	{
		i = -1;
		while (hk->dt->map[++i])
			free (hk->dt->map[i]);
		free (hk->dt->map);
		hk->dt->map = NULL;
	}
	ft_free_hk_aux (hk);
}

void	ft_free_hk_aux(t_hook *hk)
{
	int	i;

	if (hk->dt->tex)
	{
		i = -1;
		while (hk->dt->tex[++i])
			free (hk->dt->tex[i]);
		free (hk->dt->tex);
		hk->dt->tex = NULL;
	}
	if (hk->dt->color)
	{
		free (hk->dt->color[0]);
		free (hk->dt->color[1]);
		free (hk->dt->color);
		hk->dt->color = NULL;
	}
	free (hk->gr);
	hk->gr = NULL;
	free (hk);
	hk = NULL;
}
