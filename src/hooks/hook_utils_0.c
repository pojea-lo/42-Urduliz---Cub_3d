#include "../../include/cub3d.h"



//close window with red botton
int	close_button(t_hook *hk)
{
	mlx_destroy_window(hk->gr->mlx, hk->gr->mlx_win);
	mlx_destroy_image(hk->gr->mlx, hk->gr->img);
	ft_free_hk(hk);
	system ("leaks cub");
	exit(1);
}

