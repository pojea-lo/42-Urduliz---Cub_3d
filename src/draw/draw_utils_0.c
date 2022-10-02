/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_utils_0.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith < jsmith@student.42urduliz.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/02 21:31:14 by jsmith            #+#    #+#             */
/*   Updated: 2022/10/02 22:12:54 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

void	my_mlx_pixel_put(t_hook *hk, int x, int y, int color)
{
	char	*dst;

	dst = hk->gr->addr + (y * hk->gr->line_length
			+ x * (hk->gr->bits_per_pixel / 8));
	*(unsigned int *)dst = color;
}

unsigned int	get_mlx_pixel_color(t_mlx *img, int x, int y)
{
	int				buffer;
	char			*dst;
	unsigned int	color;

	color = 0;
	buffer = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = img->addr + buffer;
	color = *(unsigned int *)dst;
	return (color);
}
