#include "../../include/cub3d.h"

//funcion inicial del raycasting
int	ft_rayc_init(t_hook *hk)
{
	int	x;

	x = -1;
	ft_rayc_memset(hk);
//	while (1)//comienza el gameloop
	{
		while (++x < hk->dt->mapw)
		{
			hk->dt->camerax = ((2 * x) / hk->dt->mapw - 1);
//			printf ("La camerax: %f\n", hk->dt->camerax);
			hk->dt->raydirx = hk->dt->dirx + (hk->dt->planex * hk->dt->camerax);
			hk->dt->raydiry = hk->dt->diry + (hk->dt->planey * hk->dt->camerax);
//			printf ("Los raydir:\nX: %f\nY: %f\n", hk->dt->raydirx, hk->dt->raydiry);
			if (hk->dt->raydirx == 0)//evitar dividir por 0
				hk->dt->raydirx = 1e30;
			hk->dt->deltadistx = fabs(1 / hk->dt->raydirx);
			if (hk->dt->raydiry == 0)//evitar dividir por 0
				hk->dt->raydiry = 1e30;
			hk->dt->deltadisty = fabs(1 / hk->dt->raydiry);
//			printf ("Las deltadist:\nX: %f\nY: %f\n", hk->dt->deltadistx, hk->dt->deltadisty);
			ft_calcul_step(hk);
			ft_dda_algorithm(hk);


		}
	}


	return (0);
}

//algoritmo DDA
void	ft_dda_algorithm(t_hook *hk)
{
	while (hk->dt->hit == 0)
	{
		if (hk->dt->sidedistx < hk->dt->sidedisty)
		{
			hk->dt->sidedistx += hk->dt->deltadistx;
			hk->dt->mapx += hk->dt->stepx;
			hk->dt->side = 0;
		}
		else
		{
			hk->dt->sidedisty += hk->dt->deltadisty;
			hk->dt->mapy += hk->dt->stepy;
			hk->dt->side = 1;
		}
		if (hk->dt->map[hk->dt->mapy][hk->dt->mapx] == '1')
		{
			hk->dt->hit = 1;
			printf ("choca en:\nx: %d\ny: %d\nvalor: %c\n", hk->dt->mapx, hk->dt->mapy, hk->dt->map[hk->dt->mapy][hk->dt->mapx]);
		}
	}
}

//calculo los steps y las sidedist
void	ft_calcul_step(t_hook *hk)
{
	if (hk->dt->raydirx < 0)//valor de los steps y sededist
	{
		hk->dt->stepx = -1;
		hk->dt->sidedistx = (hk->dt->xo - hk->dt->mapx) * hk->dt->deltadistx;
	}
	else
	{
		hk->dt->stepx = 1;
		hk->dt->sidedistx = (hk->dt->mapx + 1 - hk->dt->xo) * hk->dt->deltadistx;
	}
	if (hk->dt->raydiry < 0)//valor del stepy
	{
		hk->dt->stepy = -1;
		hk->dt->sidedisty = (hk->dt->yo - hk->dt->mapy) * hk->dt->deltadisty;
	}
	else
	{
		hk->dt->stepy = 1;
		hk->dt->sidedisty = (hk->dt->mapy + 1 - hk->dt->yo) * hk->dt->deltadisty;
	}
}

//inicialización de las variables del rayc y calculo de algunas
int	ft_rayc_memset(t_hook *hk)
{
	hk->dt->mapw = 640;//dimensiones del mapa
	hk->dt->maph = 480;
	ft_get_dir(hk);
//	printf ("El vector direccion:\nX: %f\nY: %f\n", hk->dt->dirx, hk->dt->diry);
//	hk->dt->fov = 1.152;//fijo el fov en 66 grados
	hk->dt->fov = 0.7854;//fijo el fov en 90 grados
//	printf ("El FOV: %f\n", (hk->dt->fov * 360) / (2 * 3.1416));
	ft_get_plane(hk);
//	printf ("El vector plano:\nX: %f\nY: %f\n", hk->dt->planex, hk->dt->planey);
	hk->dt->mapx = hk->dt->xo;
	hk->dt->mapy = hk->dt->yo;
	hk->dt->sidedistx = 0;
	hk->dt->sidedisty = 0;
	hk->dt->deltadistx = 0;
	hk->dt->deltadisty = 0;
	hk->dt->stepx = 0;
	hk->dt->stepy = 0;
	hk->dt->hit = 0;
	hk->dt->side = -1;//de primeras no golpea muro tampoco
	return (0);
}

//obtengo el vector plano de pantall
int	ft_get_plane(t_hook *hk)
{
	if (hk->dt->dir == 'N' || hk->dt->dir == 'S')
	{
		hk->dt->planey = 0;
		if (hk->dt->diry < 0)
			hk->dt->diry *= -1;
		hk->dt->planex = hk->dt->diry * tan(hk->dt->fov / 2);
	}
	else if (hk->dt->dir == 'E' || hk->dt->dir == 'O')
	{
		hk->dt->planex = 0;
		if (hk->dt->dirx < 0)
			hk->dt->dirx *= -1;
		hk->dt->planey = hk->dt->dirx * tan(hk->dt->fov / 2);
	}
	return (0);
}


//obtengo el valor vextor direccion
int	ft_get_dir(t_hook *hk)
{
	if (hk->dt->dir == 'N')
	{
		hk->dt->dirx = 0;
		hk->dt->diry = -1;
	}
	else if (hk->dt->dir == 'S')
	{
		hk->dt->dirx = 0;
		hk->dt->diry = 1;
	}
	else if (hk->dt->dir == 'E')
	{
		hk->dt->dirx = 1;
		hk->dt->diry = 0;
	}
	else if (hk->dt->dir == 'O')
	{
		hk->dt->dirx = -1;
		hk->dt->diry = 0;
	}
	return (0);
}
