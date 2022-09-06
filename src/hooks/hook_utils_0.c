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

int manage_key_hook_options(int keycode, t_hook *hk)
{
	(void) hk;

	if (keycode == 53)
	{
		printf("EXIT");
		exit (1);
	}
	printf("keycode %d\n", keycode);
	//Checkbounds
	if (keycode == 13)
		hk->dt->yo -= 1; //Delante
	if (keycode == 1)
	   hk->dt->yo += 1; //Detras
	if (keycode == 0)
		hk->dt->xo -= 1;
	if (keycode == 2)
		hk->dt->xo += 1;
	if (keycode == 123) //Izquierda
		hk->dt->dirx -= 1;
	if (keycode == 124) //Derecha
		hk->dt->dirx += 1;		
	mlx_do_sync(hk->gr->mlx);
	ft_rayc_init(hk);
	return  (1);
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

