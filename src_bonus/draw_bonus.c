/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith < jsmith@student.42urduliz.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/03 10:33:09 by jsmith            #+#    #+#             */
/*   Updated: 2022/10/03 11:00:11 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int	ft_draw_line(t_hook *hk, int x)
{
	int	i;

	i = -1;
	while (i++ < hk->dt->drawstart)
		my_mlx_pixel_put(hk, x, i, 0x00FFFF / 2);
	while (i++ < hk->dt->drawend)
	{
		if (hk->dt->side == 0)
		{
			if (hk->dt->dirx > 0)
				my_mlx_pixel_put(hk, x, i, 0xFF00FF);
			else
				my_mlx_pixel_put(hk, x, i, 0xFFFF00);
		}
		else if (hk->dt->side == 1)
		{
			if (hk->dt->diry > 0)
				my_mlx_pixel_put(hk, x, i, 0xFF00FF / 2);
			else
				my_mlx_pixel_put(hk, x, i, 0x000000 / 2);
		}
	}
	while (i++ < hk->dt->maph)
		my_mlx_pixel_put(hk, x, i, 0xFFFFFF / 2);
	return (0);
}

int	ft_draw_map(t_hook *hk)
{
	ft_rayc_memset(hk);
	ft_rayc_memset_2(hk);
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, WIN_WIDTH,
			WIN_HEIGHT + 100, "Cub3d");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel,
			&hk->gr->line_length, &hk->gr->endian);
	load_hud_images(hk);
	load_bullets(hk);
	init_hook_threads(hk);
	mlx_loop(hk->gr->mlx);
	return (0);
}

void	load_bullets(t_hook *hk)
{
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->hud, 0, WIN_HEIGHT);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 60, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 100, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 140, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 180, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 220, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 260, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 300, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 340, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->bullet, WIN_WIDTH - 380, WIN_HEIGHT +18);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win,
		hk->gr->face, WIN_WIDTH / 2, WIN_HEIGHT +18);
}

void	load_hud_images(t_hook *hk)
{
	int	res;
	int	res2;
	int	res3;

	res2 = WIN_WIDTH;
	res = 100;
	res3 = 150;
	hk->gr->hud = mlx_xpm_file_to_image(hk->gr->mlx,
			"./pics/hud.xpm", &res2, &res);
	hk->gr->gn = mlx_xpm_file_to_image(hk->gr->mlx,
			"./pics/gun.xpm", &res3, &res3);
	hk->gr->fired = mlx_xpm_file_to_image(hk->gr->mlx,
			"./pics/fire_gun.xpm", &res3, &res3);
	hk->gr->bullet = mlx_xpm_file_to_image(hk->gr->mlx,
			"./pics/bullet.xpm", &res3, &res3);
	hk->gr->face = mlx_xpm_file_to_image(hk->gr->mlx,
			"./pics/face.xpm", &res3, &res3);
}
