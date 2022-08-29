#include "../../include/cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa
int	ft_draw_map(t_hook *hk)
{
	hk->gr->relative_path = "./prueba.xpm";
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, 900, 600, "Prueba");
//	hk->gr->img = mlx_xpm_file_to_image(hk->gr->mlx, hk->gr->relative_path, &hk->gr->img_width, &hk->gr->img_height);
//	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win, hk->gr->img, 100, 60);
	mlx_hook(hk->gr->mlx_win, 17, 0, close_button, hk);
	mlx_loop(hk->gr->mlx);
	return (0);
}
