#include "../../include/cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa
int	ft_draw_map(t_hook *hk)
{
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, hk->dt->mapw, hk->dt->maph, "Prueba");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel, &hk->gr->line_length, &hk->gr->endian);
	mlx_pixel_put(hk->gr->mlx, hk->gr->mlx_win, 5, 5, 0xFFFFFF);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win, hk->gr->img, 100, 60);
	mlx_hook(hk->gr->mlx_win, 17, 0, close_button, hk);
	mlx_loop(hk->gr->mlx);
	return (0);
}
