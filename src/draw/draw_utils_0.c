#include "../../include/cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa

int set(int keycode, t_hook *hk)
{	
	//printf("Keycode %d\n",keycode);
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
		oldDirX = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(hk->dt->rotspeed) - hk->dt->diry * sin(hk->dt->rotspeed);
		hk->dt->diry = oldDirX * sin(hk->dt->rotspeed) + hk->dt->diry * cos(hk->dt->rotspeed);
		oldPlaneX = hk->dt->planex;
		hk->dt->planex = hk->dt->planex * cos(hk->dt->rotspeed) - hk->dt->planey * sin(hk->dt->rotspeed);
		hk->dt->planey = oldPlaneX * sin(hk->dt->rotspeed) + hk->dt->planey * cos(hk->dt->rotspeed);
	}
	if (hk->dt->rotation_left)
	{
		oldDirX = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(-hk->dt->rotspeed) - hk->dt->diry * sin(-hk->dt->rotspeed);
		hk->dt->diry = oldDirX * sin(-hk->dt->rotspeed) + hk->dt->diry * cos(-hk->dt->rotspeed);
		oldPlaneX = hk->dt->planex;
		hk->dt->planex = hk->dt->planex * cos(-hk->dt->rotspeed) - hk->dt->planey * sin(-hk->dt->rotspeed);
		hk->dt->planey = oldPlaneX * sin(-hk->dt->rotspeed) + hk->dt->planey * cos(-hk->dt->rotspeed);
	}
	if (hk->dt->down)
	{
		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx * hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
		{
			hk->dt->xo -= hk->dt->dirx * hk->dt->movespeed;
		}
		
		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)] != '1')
		{
			hk->dt->yo -= hk->dt->diry * hk->dt->movespeed;
			printf("Coordenada abajo DIRY : %c\n", hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)]);
		}
	}
	if (hk->dt->up)
	{
		printf("Coordenada del jugador x %f y %f\n",hk->dt->xo, hk->dt->yo);
		printf("Subir  Xo : %f\nDir x : %f\nCoordenada de mapa : %c\n",hk->dt->xo,hk->dt->dirx,hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx * hk->dt->movespeed)][(int)(hk->dt->yo)]);
		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx * hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
			hk->dt->xo += hk->dt->dirx * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->yo += hk->dt->diry * hk->dt->movespeed;
	}
	if (hk->dt->left)
	{
		/*
		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->diry * hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
			hk->dt->xo += hk->dt->diry * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->yo += hk->dt->diry * hk->dt->movespeed;
		*/
	}
	if (hk->dt->right)
	{
		/*
		if (hk->dt->map[(int)(hk->dt->xo + hk->dt->dirx * hk->dt->movespeed)][(int)(hk->dt->yo)] != '1')
			hk->dt->xo += hk->dt->dirx * hk->dt->movespeed;
		if (hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo + hk->dt->diry * hk->dt->movespeed)] != '1')
			hk->dt->yo += hk->dt->diry * hk->dt->movespeed;

		*/
	}
	return (1);
}
int game_engine(t_hook *hk)
{
	ft_rayc_memset_2(hk);
	ft_rayc_init(hk);
	manage_movements(hk);
	return (1);
}

int	ft_draw_map(t_hook *hk)
{
	ft_rayc_memset(hk);
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, hk->dt->mapw, hk->dt->maph,"Cub3d");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel, &hk->gr->line_length, &hk->gr->endian);
	ft_rayc_init(hk);
	mlx_hook(hk->gr->mlx_win, 2,0, &set, hk);
	mlx_loop_hook(hk->gr->mlx, &game_engine,hk);
	mlx_hook(hk->gr->mlx_win, 3,0, &unset, hk);
	mlx_hook(hk->gr->mlx_win, 17, 0, close_button, hk);
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
