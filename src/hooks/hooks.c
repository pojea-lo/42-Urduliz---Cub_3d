/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hooks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith < jsmith@student.42urduliz.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:50:34 by jsmith            #+#    #+#             */
/*   Updated: 2022/10/03 18:06:09 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	manage_rotation(t_hook *hk)
{
	double	rootspeed;
	double	olddirx;
	double	oldplanex;

	rootspeed = hk->dt->rotspeed * -1;
	if (hk->dt->rotation_right)
		rootspeed = hk->dt->rotspeed;
	if (hk->dt->rotation_right || hk->dt->rotation_left)
	{
			olddirx = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(rootspeed)
			- hk->dt->diry * sin(rootspeed);
		hk->dt->diry = olddirx * sin(rootspeed)
			+ hk->dt->diry * cos(rootspeed);
		oldplanex = hk->dt->planex;
		hk->dt->planex = hk->dt->planex * cos(rootspeed)
			- hk->dt->planey * sin(rootspeed);
		hk->dt->planey = oldplanex * sin(rootspeed)
			+ hk->dt->planey * cos(rootspeed);
	}
}

void	manage_y_axys(t_hook *hk)
{
	if (hk->dt->left)
	{
		if (hk->dt->map[(int)(hk->dt->yo - hk->dt->dirx
				* hk->dt->movespeed)][(int)(hk->dt->xo)] != '1')
			hk->dt->yo -= hk->dt->dirx * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->yo)][(int)(hk->dt->xo
				+ hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->xo += hk->dt->diry * hk->dt->movespeed;
	}
	if (hk->dt->right)
	{
		if (hk->dt->map[(int)(hk->dt->yo + hk->dt->dirx
				* hk->dt->movespeed)][(int)(hk->dt->xo)] != '1')
			hk->dt->yo += hk->dt->dirx * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->yo)][(int)(hk->dt->xo
				- hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->xo -= hk->dt->diry * hk->dt->movespeed;
	}
}

void	manage_x_axys(t_hook *hk)
{
	if (hk->dt->down)
	{
		if (hk->dt->map[(int)(hk->dt->yo - hk->dt->diry
				* hk->dt->movespeed)][(int)(hk->dt->xo)] != '1')
			hk->dt->yo -= hk->dt->diry * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->yo)][(int)(hk->dt->xo
				- hk->dt->dirx * hk->dt->movespeed)] != '1')
			hk->dt->xo -= hk->dt->dirx * hk->dt->movespeed;
	}
	if (hk->dt->up)
	{
		if (hk->dt->map[(int)(hk->dt->yo + hk->dt->diry
				* hk->dt->movespeed)][(int)(hk->dt->xo)] != '1')
			hk->dt->yo += hk->dt->diry * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->yo)][(int)(hk->dt->xo
				+ hk->dt->dirx * hk->dt->movespeed)] != '1')
			hk->dt->xo += hk->dt->dirx * hk->dt->movespeed;
	}
}

int	game_engine(t_hook *hk)
{	
	manage_rotation(hk);
	manage_x_axys(hk);
	manage_y_axys(hk);
	ft_rayc_init(hk);
	return (1);
}

void	init_hook_threads(t_hook *hk)
{
	mlx_hook(hk->gr->mlx_win, 2,
		(1L << 0), &set, hk);
	mlx_loop_hook(hk->gr->mlx, &game_engine, hk);
	mlx_hook(hk->gr->mlx_win, 3, (1 << 0), &unset, hk);
	mlx_hook(hk->gr->mlx_win, 17, (17L << 0), close_button, hk);
}
