/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memset.c                                           :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 07:49:43 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 07:57:51 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

t_hook	*ft_memset(t_in *dt)
{
	t_mlx	*gr;
	t_hook	*hk;

	dt->info = NULL;
	dt->map = NULL;
	dt->tex = NULL;
	dt->color = NULL;
	dt->xo = 0;
	dt->yo = 0;
	gr = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	hk = (t_hook *)malloc(sizeof(t_hook) * 1);
	dt->color = (int **)malloc(sizeof(int *) * 2);
	dt->color[0] = (int *)malloc(sizeof(int) * 3);
	dt->color[1] = (int *)malloc(sizeof(int) * 3);
	if (!gr || !hk || !dt->color || !dt->color[0] || !dt->color[1])
		return (NULL);
	hk->dt = dt;
	hk->gr = gr;
	gr->mlx = mlx_init();
	return (hk);
}

int	ft_rayc_memset(t_hook *hk)
{
	hk->dt->mapw = WIN_WIDTH;
	hk->dt->maph = WIN_HEIGHT;
	hk->dt->fov = 1.5708;
	hk->dt->movespeed = 0.20;
	hk->dt->rotspeed = 0.10;
	ft_get_dir(hk);
	ft_get_plane(hk);
	hk->dt->sidedistx = 0;
	hk->dt->sidedisty = 0;
	hk->dt->deltadistx = 0;
	hk->dt->deltadisty = 0;
	hk->dt->rotation_left = false;
	hk->dt->rotation_right = false;
	hk->dt->up = false;
	hk->dt->down = false;
	hk->dt->right = false;
	hk->dt->left = false;
	hk->dt->stepx = 0;
	hk->dt->stepy = 0;
	hk->dt->side = -1;
	return (0);
}

int	ft_rayc_memset_2(t_hook *hk)
{
	hk->dt->mapx = hk->dt->xo;
	hk->dt->mapy = hk->dt->yo;
	hk->dt->hit = 0;
	return (0);
}
