#include "../../include/cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa
int	ft_draw_map(t_hook *hk)
{
//	ft_rayc_memset(hk);
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, hk->dt->mapw, hk->dt->maph,"");//960.00, 720.00, "");
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, 960.00, 720.00, "");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel, &hk->gr->line_length, &hk->gr->endian);
	ft_rayc_init(hk);
//	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win, hk->gr->img, 100, 60);
	mlx_mouse_hook(hk->gr->mlx_win,&manage_mouse_hook_options, hk);
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

	i = -1;
	while (++i < hk->dt->drawstart) 
		mlx_pixel_put(hk->gr->mlx, hk->gr->mlx_win, x, i, 0x00FFFF/ 2);
	while (i++ < hk->dt->drawend)
	{
		if (hk->dt->side == 0)
			mlx_pixel_put(hk->gr->mlx, hk->gr->mlx_win, x, i, 0xFF00FF);
		else if (hk->dt->side == 1)
			mlx_pixel_put(hk->gr->mlx, hk->gr->mlx_win, x, i, 0xFF00FF / 2);
	}
	while (i++ < hk->dt->maph) 
		mlx_pixel_put(hk->gr->mlx, hk->gr->mlx_win, x, i, 0xFFFF00/ 2);
	return (0);
}
