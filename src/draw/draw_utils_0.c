#include "../../include/cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa
int	ft_draw_map(t_hook *hk)
{
	ft_rayc_memset(hk);
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, hk->dt->mapw, hk->dt->maph,"");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel, &hk->gr->line_length, &hk->gr->endian);
	ft_rayc_init(hk);
//	mlx_mouse_hook(hk->gr->mlx_win,&manage_mouse_hook_options, hk);
	mlx_key_hook(hk->gr->mlx_win, &manage_key_hook_options,hk);
	mlx_hook(hk->gr->mlx_win, 17, 0, close_button, hk);
//	mlx_hook(hk->gr->mlx_win, 2, 1L << 0, keyw, hk);
	mlx_loop(hk->gr->mlx);
	return (0);
}

//funcion que me dibuja las lineas verticales
int	ft_draw_line(t_hook *hk, int x)
{
	int	i;

	i = 0;
	while (i < hk->dt->drawstart)
	{
		my_mlx_pixel_put(hk, x, i, 0x00FFFF/ 2);
		i++;
	}
	while (i < hk->dt->drawend)
	{
		if (hk->dt->side == 0)
		{
			my_mlx_pixel_put(hk, x, i, 0xFF00FF);
			i++;
		}
		else if (hk->dt->side == 1)
		{
			my_mlx_pixel_put(hk, x, i, 0xFF00FF / 2);
			i++;
		}
	}
	while (i < hk->dt->maph) 
	{
		my_mlx_pixel_put(hk, x, i, 0xFFFF00 / 2);
		i++;
	}
	return (0);
}

void	my_mlx_pixel_put(t_hook *hk, int x, int y, int color)
{
	char	*dst;

	dst = hk->gr->addr + (y * hk->gr->line_length + x * (hk->gr->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

unsigned int	get_mlx_pixel_color(t_mlx *img, int x, int y)
{
	int				buffer;
	char			*dst;
	unsigned int	color = 0;

	buffer = (y * img->line_length + x * (img->bits_per_pixel / 8));
	dst = img->addr + buffer;
	color = *(unsigned int *)dst;
	return (color);
}
