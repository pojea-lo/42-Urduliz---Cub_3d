/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith < jsmith@student.42urduliz.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 08:05:21 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/10/02 21:53:54 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_rayc_init(t_hook *hk)
{
	int	x;

	x = -1;
	while (++x < hk->dt->mapw)
	{
		ft_rayc_memset_2(hk);
		hk->dt->camerax = (2 * x) / hk->dt->mapw - 1;
		hk->dt->raydirx = hk->dt->dirx + (hk->dt->planex * hk->dt->camerax);
		hk->dt->raydiry = hk->dt->diry + (hk->dt->planey * hk->dt->camerax);
		hk->dt->deltadistx = fabs(1 / hk->dt->raydirx);
		hk->dt->deltadisty = fabs(1 / hk->dt->raydiry);
		ft_calcul_step(hk);
		ft_dda_algorithm(hk);
		hk->dt->lineheight = (int)(hk->dt->maph / hk->dt->perpwalldist);
		hk->dt->drawstart = -hk->dt->lineheight / 2 + hk->dt->maph / 2;
		if (hk->dt->drawstart < 0)
			hk->dt->drawstart = 0;
		hk->dt->drawend = hk->dt->lineheight / 2 + hk->dt->maph / 2;
		if (hk->dt->drawend >= hk->dt->maph)
			hk->dt->drawend = hk->dt->maph - 1;
		ft_draw_texture(hk, x);
	}
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win, hk->gr->img, 0, 0);
	return (0);
}

int	ft_get_dir(t_hook *hk)
{
	if (hk->dt->dir == 'N')
	{
		hk->dt->dirx = 0;
		hk->dt->diry = -1;
	}
	else if (hk->dt->dir == 'S')
	{
		hk->dt->dirx = 0;
		hk->dt->diry = 1;
	}
	else if (hk->dt->dir == 'E')
	{
		hk->dt->dirx = 1;
		hk->dt->diry = 0;
	}
	else if (hk->dt->dir == 'W')
	{
		hk->dt->dirx = -1;
		hk->dt->diry = 0;
	}
	return (0);
}

int	ft_get_plane(t_hook *hk)
{
	if (hk->dt->dir == 'N' || hk->dt->dir == 'S')
	{
		hk->dt->planey = 0;
		hk->dt->planex = atan(hk->dt->fov / 2);
		if (hk->dt->dir == 'S')
			hk->dt->planex *= -1;
	}
	else if (hk->dt->dir == 'E' || hk->dt->dir == 'W')
	{
		hk->dt->planex = 0;
		hk->dt->planey = atan(hk->dt->fov / 2);
		if (hk->dt->dir == 'W')
			hk->dt->planey *= -1;
	}
	return (0);
}

void	ft_calcul_step(t_hook *hk)
{
	if (hk->dt->raydirx < 0)
	{
		hk->dt->stepx = -1;
		hk->dt->sidedistx = (hk->dt->xo - hk->dt->mapx) * hk->dt->deltadistx;
	}
	else
	{
		hk->dt->stepx = 1;
		hk->dt->sidedistx = (hk->dt->mapx + 1.0 - hk->dt->xo)
			* hk->dt->deltadistx;
	}
	if (hk->dt->raydiry < 0)
	{
		hk->dt->stepy = -1;
		hk->dt->sidedisty = (hk->dt->yo - hk->dt->mapy) * hk->dt->deltadisty;
	}
	else
	{
		hk->dt->stepy = 1;
		hk->dt->sidedisty = (hk->dt->mapy + 1.0 - hk->dt->yo)
			* hk->dt->deltadisty;
	}
}

void	ft_dda_algorithm(t_hook *hk)
{
	while (hk->dt->hit == 0)
	{
		if (hk->dt->sidedistx < hk->dt->sidedisty)
		{
			hk->dt->sidedistx += hk->dt->deltadistx;
			hk->dt->mapx += hk->dt->stepx;
			hk->dt->side = 0;
		}
		else
		{
			hk->dt->sidedisty += hk->dt->deltadisty;
			hk->dt->mapy += hk->dt->stepy;
			hk->dt->side = 1;
		}
		if (hk->dt->map[hk->dt->mapy][hk->dt->mapx] == '1')
			hk->dt->hit = 1;
	}
	if (hk->dt->side == 0)
		hk->dt->perpwalldist = (hk->dt->sidedistx - hk->dt->deltadistx);
	else
		hk->dt->perpwalldist = (hk->dt->sidedisty - hk->dt->deltadisty);
}
