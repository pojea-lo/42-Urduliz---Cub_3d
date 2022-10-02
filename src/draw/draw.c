/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith < jsmith@student.42urduliz.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:56:32 by jsmith            #+#    #+#             */
/*   Updated: 2022/10/02 22:01:21 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

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
			WIN_HEIGHT, "Cub3d");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel,
			&hk->gr->line_length, &hk->gr->endian);
	init_hook_threads(hk);
	mlx_loop(hk->gr->mlx);
	return (0);
}
