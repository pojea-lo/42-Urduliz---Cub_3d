#include "cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa
int	ft_draw_map(t_hook *hk)
{
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, 00, 600, "Prueba");
	mlx_hook(hk->gr->mlx_win, 17, 0, close_button, hk);
	mlx_loop(hk->gr->mlx);
	return (0);
}
