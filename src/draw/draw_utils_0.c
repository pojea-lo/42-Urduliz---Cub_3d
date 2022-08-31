#include "../../include/cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa
int	ft_draw_map(t_hook *hk)
{
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, 640, 480, "");//hk->dt->mapw, hk->dt->maph, "Prueba");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel, &hk->gr->line_length, &hk->gr->endian);
	return (0);
}

//funcion que me dibuja las lineas verticales
int	ft_draw_line(t_hook *hk, int x)
{
	int	i;

	i = hk->dt->drawstart;
	while (i < hk->dt->drawend)
	{
		mlx_pixel_put(hk->gr->mlx, hk->gr->mlx_win, x, i, 0xFF00FF);
		i++;
	}
	return (0);
}
	
int ft_draw_all(t_hook *hk)
{
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win, hk->gr->img, 100, 60);
	printf ("Hola\n");
	mlx_hook(hk->gr->mlx_win, 17, 0, close_button, hk);
	mlx_loop(hk->gr->mlx);
	return (0);
}
