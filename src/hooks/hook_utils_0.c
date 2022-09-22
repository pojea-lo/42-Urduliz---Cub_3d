#include "../../include/cub3d.h"


int manage_mouse_hook_options(t_hook *hk)
{
	(void)hk;
/*	int x[2] = {5,5};
	int y[2] = {6,6};
	(void)hk;
	printf("%d\n", mlx_mouse_get_pos(hk->gr->mlx_win,x,y));
*/	return (1);
}

//close window with red botton
int	close_button(t_hook *hk)
{
	mlx_destroy_window(hk->gr->mlx, hk->gr->mlx_win);
	mlx_destroy_image(hk->gr->mlx, hk->gr->img);
	ft_free_hk(hk);
//	system ("leaks cub");
	exit(1);
}

