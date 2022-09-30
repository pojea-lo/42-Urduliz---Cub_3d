/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*   By: jsmith <marvin@42.fr>                        +:+ +:+         +:+     */
/*   By: pojea-lo <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 08:06:28 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/09/30 08:06:51 by pojea-lo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/cub3d.h"

int	ft_draw_texture(t_hook *hk, int x)
{
	hk->dt->texnum = ft_cal_texnum(hk);
	if (hk->dt->side == 0)
		hk->dt->wallx = hk->dt->yo + (hk->dt->perpwalldist * hk->dt->raydiry);
	else if (hk->dt->side == 1)
		hk->dt->wallx = hk->dt->xo + (hk->dt->perpwalldist * hk->dt->raydirx);
	hk->dt->wallx -= floor((hk->dt->wallx));
	hk->dt->texx = (int)(hk->dt->wallx * (double)hk->dt->texwidth);
	if (hk->dt->side == 0 && hk->dt->raydirx > 0)
		hk->dt->texx = hk->dt->texwidth - hk->dt->texx - 1;
	if (hk->dt->side == 1 && hk->dt->raydiry < 0)
			hk->dt->texx = hk->dt->texwidth - hk->dt->texx - 1;
	hk->dt->step = 1.0 * hk->dt->texheight / hk->dt->lineheight;
	hk->dt->texpos = ((hk->dt->drawstart - hk->dt->maph / 2)
			+ (hk->dt->lineheight / 2)) * hk->dt->step;
	ft_print_tex(hk, x);
	return (0);
}

int	ft_cal_texnum(t_hook *hk)
{
	int	texnum;

	texnum = 0;
	if (hk->dt->side == 0)
	{
		if (hk->dt->raydirx > 0)
			texnum = 3;
		else
			texnum = 2;
	}
	else if (hk->dt->side == 1)
	{
		if (hk->dt->raydiry > 0)
			texnum = 1;
		else
			texnum = 0;
	}
	hk->dt->texwidth = hk->dt->texture[texnum].w;
	hk->dt->texheight = hk->dt->texture[texnum].h;
	return (texnum);
}

void	ft_print_tex(t_hook *hk, int x)
{
	int	y;
	int	color_c;
	int	color_f;

	y = 0;
	color_c = ft_color_converter(hk->dt, 0);
	color_f = ft_color_converter(hk->dt, 1);
	while (y < hk->dt->drawstart)
		my_mlx_pixel_put(hk, x, y++, color_c);
	y = hk->dt->drawstart;
	while (y < hk->dt->drawend)
	{
		hk->dt->texy = (int)hk->dt->texpos & (int)(hk->dt->texheight - 1);
		hk->dt->texpos += hk->dt->step;
		hk->dt->colo = get_mlx_pixel_color(&hk->dt->texture[hk->dt->texnum],
				hk->dt->texx, hk->dt->texy);
		my_mlx_pixel_put(hk, x, y, hk->dt->colo);
		y++;
	}
	while (y < hk->dt->maph)
	{
		my_mlx_pixel_put(hk, x, y, color_f);
		y++;
	}
}

int	ft_color_converter(t_in *dt, int i)
{
	int		res;
	int		j;

	res = 0;
	j = 0;
	if (ft_ch_sky(dt) != 0)
		j = 1;
	if (i == 0)
	{
		res = dt->color[j][0];
		res = (res << 8) | dt->color[j][1];
		res = (res << 8) | dt->color[j][2];
	}
	else if (i != 0)
	{
		if (j == 0)
			j = 1;
		else if (j == 1)
			j = 0;
		res = dt->color[j][0];
		res = (res << 8) | dt->color[j][1];
		res = (res << 8) | dt->color[j][2];
	}
	return (res);
}

int	ft_ch_sky(t_in *dt)
{
	int	i;

	i = -1;
	while (dt->info[++i])
	{
		if (ft_ch_line_two(dt->info[i]) == 0)
			return (0);
		else if (ft_ch_line_two(dt->info[i]) == 1)
			return (1);
	}
	return (-1);
}
