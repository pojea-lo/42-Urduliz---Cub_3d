#include "../../include/cub3d.h"

//funcion que abre la ventana y arranca el dibujo del mapa

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
	//if (keycode == 126) //Arriba flecha
	if (keycode == 123)
		hk->dt->rotation_left = false;
	if (keycode == 124) //izquirda flecha
		hk->dt->rotation_right = false;
	 //Abajo flecha
	return (1);
}

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
		printf("change");
	return (1);
}

#define ROTATION 0.25

int manage_movements(t_hook *hk)
{
	double	old_dir_x;
	double	old_plane_x;

	if (hk->dt->rotation_left)
	{
		
		old_dir_x = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(ROTATION) - hk->dt->diry * sin(ROTATION);
		hk->dt->diry = old_dir_x * sin(ROTATION) + hk->dt->diry * cos(-ROTATION);
		old_plane_x = hk->dt->planex;
		hk->dt->dirx = hk->dt->planex * cos(ROTATION) - hk->dt->planey * sin(ROTATION);
		hk->dt->planey = old_plane_x * sin(ROTATION) + hk->dt->planey * cos(ROTATION);
	}
	if (hk->dt->rotation_right)
	{
		old_dir_x = hk->dt->dirx;
		hk->dt->dirx = hk->dt->dirx * cos(-ROTATION) - hk->dt->diry * sin(-ROTATION);
		hk->dt->diry = old_dir_x * sin(-ROTATION) + hk->dt->diry * cos(-ROTATION);
		old_plane_x = hk->dt->planex;
		hk->dt->dirx = hk->dt->planex * cos(-ROTATION) - hk->dt->planey * sin(-ROTATION);
		hk->dt->planey = old_plane_x * sin(-ROTATION) + hk->dt->planey * cos(-ROTATION);
	}
	if (hk->dt->down)
	{
		if(hk->dt->map[(int)(hk->dt->xo - hk->dt->dirx * 0.25)][(int)(hk->dt->yo)] == false)
		{
			hk->dt->xo -= hk->dt->dirx * 0.25;
		} 
      	if(hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo - hk->dt->diry * 0.25)] == false) 
			hk->dt->yo -= hk->dt->diry * 0.25;
	}
	if (hk->dt->up)
	{
		if(hk->dt->map[(int)(hk->dt->xo - hk->dt->dirx * 0.25)][(int)(hk->dt->yo)] == false) 
			hk->dt->xo += hk->dt->dirx * 0.25;
      	if(hk->dt->map[(int)(hk->dt->xo)][(int)(hk->dt->yo - hk->dt->diry * 0.25)] == false)
			hk->dt->yo += hk->dt->diry * 0.25;
	}
		

	return (1);
}
int game_engine(t_hook *hk)
{
	ft_rayc_init(hk);
	manage_movements(hk);
	return (1);
}

int	ft_draw_map(t_hook *hk)
{
	ft_rayc_memset(hk);
	hk->gr->mlx_win = mlx_new_window(hk->gr->mlx, hk->dt->mapw, hk->dt->maph,"");
	hk->gr->img = mlx_new_image(hk->gr->mlx, hk->dt->mapw, hk->dt->maph);
	hk->gr->addr = mlx_get_data_addr(hk->gr->img, &hk->gr->bits_per_pixel, &hk->gr->line_length, &hk->gr->endian);
	ft_rayc_init(hk);
//	mlx_mouse_hook(hk->gr->mlx_win,&manage_mouse_hook_options, hk);
	mlx_hook(hk->gr->mlx_win, 2, 1L << 0, &set, hk);
	mlx_hook(hk->gr->mlx_win, 3, 1L << 1, &unset, hk);
	mlx_loop_hook(hk->gr->mlx, &game_engine,hk);
	//mlx_key_hook(hk->gr->mlx_win, &manage_key_hook_options,hk);
	mlx_hook(hk->gr->mlx_win, 17, 0, close_button, hk);
//	mlx_hook(hk->gr->mlx_win, 2, 1L << 0, keyw, hk);
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
