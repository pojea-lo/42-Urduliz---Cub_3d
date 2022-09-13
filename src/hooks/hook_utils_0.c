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
	(void) 	hk;
	
	if (keycode == 53)
	{
		printf("EXIT");
		exit (1);
	}
//	printf("keycode %d\n", keycode);
	//Checkbounds
	if (keycode == 13)//Delante
	{
		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx * hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
			hk->dt->xo += hk->dt->dirx * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->yo += hk->dt->diry * hk->dt->movespeed;
	}
	if (keycode == 1)//Detras
	   hk->dt->yo += 1;
	if (keycode == 0)//Izquierda
		hk->dt->xo -= 1;
	if (keycode == 2)//Derecha
		hk->dt->xo += 1;
	if (keycode == 123) //Giro Izquierda
	{
		double oldDirX = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(-hk->dt->rotspeed) - hk->dt->diry * sin(-hk->dt->rotspeed);
		hk->dt->diry = oldDirX * sin(-hk->dt->rotspeed) + hk->dt->diry * cos(-hk->dt->rotspeed);
		double oldPlaneX = hk->dt->planex;
		hk->dt->planex = hk->dt->planex * cos(-hk->dt->rotspeed) - hk->dt->planey * sin(-hk->dt->rotspeed);
		hk->dt->planey = oldPlaneX * sin(-hk->dt->rotspeed) + hk->dt->planey * cos(-hk->dt->rotspeed);
	}
	if (keycode == 124) //Giro Derecha
	{
		double oldDirX = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(hk->dt->rotspeed) - hk->dt->diry * sin(hk->dt->rotspeed);
		hk->dt->diry = oldDirX * sin(hk->dt->rotspeed) + hk->dt->diry * cos(hk->dt->rotspeed);
		double oldPlaneX = hk->dt->planex;
		hk->dt->planex = hk->dt->planex * cos(hk->dt->rotspeed) - hk->dt->planey * sin(hk->dt->rotspeed);
		hk->dt->planey = oldPlaneX * sin(hk->dt->rotspeed) + hk->dt->planey * cos(hk->dt->rotspeed);	
	}
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

