#include "../../include/cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa

int set(int keycode, t_hook *hk)
{	
	if (keycode == 53)
		close_button(hk);
	if (keycode == 13) //Arriba w
		hk->dt->up = true;
	if (keycode == 0) //Izquierda a
		hk->dt->left = true;
	if (keycode == 2) //Derecha d
		hk->dt->right =	true;
	if (keycode == 1) //Abajo s 
		hk->dt->down = true;
	//if (keycode == 126) //Arriba flecha
	//if (keycode == 125) //Abajo flecha
	if (keycode == 123) //Derecha flecha
		hk->dt->rotation_left = true;
	if (keycode == 124) //Derecha flecha
		hk->dt->rotation_right = true;
	return (1);
}

int unset(int keycode, t_hook *hk)
{	
	//printf();
	if (keycode == 13) //Arriba w
		hk->dt->up = false;
	if (keycode == 0) //Izquierda a
		hk->dt->left = false;
	if (keycode == 2) //Derecha d
		hk->dt->right =	false;
	if (keycode == 1) //Abajo s 
		hk->dt->down = false;
	if (keycode == 123)
		hk->dt->rotation_left = false;
	if (keycode == 124) //izquirda flecha
		hk->dt->rotation_right = false;
	return (1);
}

int manage_movements(t_hook *hk)
{
	double oldDirX;
	double oldPlaneX;
		
	if (hk->dt->rotation_right)
	{	
		printf ("antes Dirx: %f y diry: %f\n", hk->dt->dirx, hk->dt->diry);
		oldDirX = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(hk->dt->rotspeed) - hk->dt->diry * sin(hk->dt->rotspeed);
		hk->dt->diry = oldDirX * sin(hk->dt->rotspeed) + hk->dt->diry * cos(hk->dt->rotspeed);
		oldPlaneX = hk->dt->planex;
		hk->dt->planex = hk->dt->planex * cos(hk->dt->rotspeed) - hk->dt->planey * sin(hk->dt->rotspeed);
		hk->dt->planey = oldPlaneX * sin(hk->dt->rotspeed) + hk->dt->planey * cos(hk->dt->rotspeed);
//		printf("Coordenada del jugador x %f y %f\n",hk->dt->xo, hk->dt->yo);
//		printf("Coordenada del jugador dirx %f diry %f\n",hk->dt->dirx, hk->dt->diry);
		printf ("despues Dirx: %f y diry: %f\n", hk->dt->dirx, hk->dt->diry);
	}
	if (hk->dt->rotation_left)
	{
		printf ("antes Dirx: %f y diry: %f\n", hk->dt->dirx, hk->dt->diry);
		oldDirX = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(-hk->dt->rotspeed) - hk->dt->diry * sin(-hk->dt->rotspeed);
		hk->dt->diry = oldDirX * sin(-hk->dt->rotspeed) + hk->dt->diry * cos(-hk->dt->rotspeed);
		oldPlaneX = hk->dt->planex;
		hk->dt->planex = hk->dt->planex * cos(-hk->dt->rotspeed) - hk->dt->planey * sin(-hk->dt->rotspeed);
		hk->dt->planey = oldPlaneX * sin(-hk->dt->rotspeed) + hk->dt->planey * cos(-hk->dt->rotspeed);
		printf ("despues Dirx: %f y diry: %f\n", hk->dt->dirx, hk->dt->diry);
	}
	if (hk->dt->down)
	{
		printf ("Dirx: %f y diry: %f\n", hk->dt->dirx, hk->dt->diry);
		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx * hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
			hk->dt->xo -= hk->dt->dirx * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->yo -= hk->dt->diry * hk->dt->movespeed;
		printf("Coordenada del jugador x %f y %f\n",hk->dt->xo, hk->dt->yo);
	}
	if (hk->dt->up)
	{
		printf ("Dirx: %f y diry: %f\n", hk->dt->dirx, hk->dt->diry);
		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx
				* hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
			hk->dt->xo += hk->dt->dirx * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo
				- hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->yo += hk->dt->diry * hk->dt->movespeed;
		int i = 0;
		int u = 0;
		while (hk->dt->map[i])
		{
			u = 0;
			while(hk->dt->map[i][u])
			{
		//		printf("%c", hk->dt->map[i][u]);
				u++;
			}
		//	printf("\n");
			i++;
		}
		// Fin pruebas
		printf("Coordenada del jugador x %f y %f\n",hk->dt->xo, hk->dt->yo);
		//printf("Subir  Xo : %f\nDir x : %f\nCoordenada de mapa : %c\n",hk->dt->xo,hk->dt->dirx,hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx * hk->dt->movespeed)][(int)(hk->dt->yo)]);
	}
	if (hk->dt->left)
	{

/*		hk->dt->xo = hk->dt->xo + sin(angulo) * hk->dt->movespeed;
		hk->dt->yo = hk->dt->yo + cos(angulo) * hk->dt->movespeed;
//		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->diry * hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
			hk->dt->xo += hk->dt->diry * hk->dt->movespeed;



//		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->yo += hk->dt->dirx * hk->dt->movespeed;
*/		
	}
	if (hk->dt->right)
	{
		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx * hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
			hk->dt->xo += hk->dt->dirx * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->yo += hk->dt->diry * hk->dt->movespeed;
	}
	return (1);
}
int game_engine(t_hook *hk)
{	
	//double mouse;
	//int i = 0;
	//int u = 0;

	//mouse = mlx_mouse_get_pos(hk->gr->mlx_win,&i,&u);
	//printf("Mouse %f\n", mouse);
	
	
	//ft_rayc_memset(hk);
	//ft_rayc_memset_2(hk);
	ft_rayc_init(hk);
	manage_movements(hk);
	return (1);
}

int mouse(int x, int y,t_hook *hk)
{
	//double mouse;
	//int y = 0;
	//int x = 0;
	//int x_x;
	//int y_y;
	(void)y;
	double whereis;
	whereis = x - (WIN_WIDTH / 2);
	double mouse;
	mouse  = mlx_mouse_get_pos(hk->gr->mlx_win,&x, &y);
	(void) mouse;
	double old_rot = hk->dt->rotspeed;
	hk->dt->rotspeed = 0.0005;
	if (whereis < 0)
	{
		hk->dt->rotation_left = true;
		hk->dt->rotation_right = false;
		//if (mouse < mlx_mouse_get_pos(hk->gr->mlx_win, &x, &y))
		//	hk->dt->rotation_left = false;
	}
	if (whereis > 0)
	{
		hk->dt->rotation_right = true;
		hk->dt->rotation_left = false;
		//if (mouse < mlx_mouse_get_pos(hk->gr->mlx_win, &x, &y))
		//	hk->dt->rotation_right = false;
	}
	if (whereis == 0)
	{
		hk->dt->rotation_left = false;
		hk->dt->rotation_right = false;
	}
	mlx_mouse_move(hk->gr->mlx_win, WIN_WIDTH / 2, WIN_HEIGHT / 2);
	hk->dt->rotspeed = old_rot;
	return (1);
}

int	ft_draw_map(t_hook *hk)
{
	int res = 99;
	int res2 = WIN_WIDTH;//1000;
	int res3 = 150;
	hk->gr->mouse_x = 0;
	hk->gr->mouse_y = 0;

	ft_rayc_memset(hk);
	ft_rayc_memset_2(hk);
	//ESPACIO EXTRA HUD
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, WIN_WIDTH, WIN_HEIGHT + 100,"Cub3d");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel, &hk->gr->line_length, &hk->gr->endian);

	//COMENTAR PARA INHABILITAR EL HUD Y ARMA
	hk->gr->hud = mlx_xpm_file_to_image(hk->gr->mlx,"./pics/hud.xpm",&res2,&res);
	mlx_put_image_to_window(hk->gr->mlx,hk->gr->mlx_win,hk->gr->hud,0,WIN_HEIGHT);
	hk->gr->gun = mlx_xpm_file_to_image(hk->gr->mlx,"./pics/gun.xpm",&res3,&res3);
	//FIN INHABILITAR EL HUD
	
	mlx_hook(hk->gr->mlx_win, 2, (1L << 0) , &set, hk);
	printf ("El mapx: %d y mapy: %d\n", hk->dt->mapx, hk->dt->mapy);
	printf ("El x0: %f y y0: %f\n", hk->dt->xo, hk->dt->yo);
//	ft_rayc_init(hk);//poner cuando anulemos el loop del gameengine
	manage_movements(hk);
	mlx_loop_hook(hk->gr->mlx, &game_engine,hk);
	mlx_hook(hk->gr->mlx_win, 3,(1 << 0), &unset, hk);
	mlx_hook(hk->gr->mlx_win, 17, 17L << 0 , close_button, 0);
//	mlx_hook(hk->gr->mlx_win, 6, 1L << 0, mouse, hk);
	mlx_mouse_hook(hk->gr->mlx_win,mouse, hk);
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
