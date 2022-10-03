/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   hook_utils_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith < jsmith@student.42urduliz.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 22:35:47 by jsmith            #+#    #+#             */
/*   Updated: 2022/10/03 10:55:24 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	click(int key, int x, int y, t_hook *hk)
{
	(void)x;
	(void)y;
	(void)key;
	(void)hk;
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->fired, 438, 380);
	return (1);
}

int	mouse(int x, int y, t_hook *hk)
{
	double	whereis;

	whereis = x - (WIN_WIDTH / 2);
	mlx_mouse_get_pos(hk->gr->mlx_win, &x, &y);
	(void)y;
	if (whereis < 0)
	{
		hk->dt->rotation_left = true;
		hk->dt->rotation_right = false;
	}
	if (whereis > 0)
	{
		hk->dt->rotation_right = true;
		hk->dt->rotation_left = false;
	}
	if (whereis == 0)
	{
		hk->dt->rotation_left = false;
		hk->dt->rotation_right = false;
	}
	mlx_mouse_move(hk->gr->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	return (1);
}

int	unset(int keycode, t_hook *hk)
{	
	if (keycode == 13)
		hk->dt->up = false;
	if (keycode == 0)
		hk->dt->left = false;
	if (keycode == 2)
		hk->dt->right = false;
	if (keycode == 1)
		hk->dt->down = false;
	if (keycode == 123)
		hk->dt->rotation_left = false;
	if (keycode == 124)
		hk->dt->rotation_right = false;
	return (1);
}

int	set(int keycode, t_hook *hk)
{	
	if (keycode == 53)
		close_button(hk);
	if (keycode == 13)
		hk->dt->up = true;
	if (keycode == 0)
		hk->dt->left = true;
	if (keycode == 2)
		hk->dt->right = true;
	if (keycode == 1)
		hk->dt->down = true;
	if (keycode == 123)
		hk->dt->rotation_left = true;
	if (keycode == 124)
		hk->dt->rotation_right = true;
	return (1);
}

int	close_button(t_hook *hk)
{
	mlx_destroy_window(hk->gr->mlx, hk->gr->mlx_win);
	mlx_destroy_image(hk->gr->mlx, hk->gr->img);
	ft_free_hk(hk);
	exit(1);
}
