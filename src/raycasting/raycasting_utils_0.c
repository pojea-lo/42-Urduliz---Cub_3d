#include "../../include/cub3d.h"

//funcion inicial del raycasting
int	ft_rayc_init(t_hook *hk)
{
	int	x;

	x = -1;
	ft_rayc_memset(hk);
	while (1)//comienza el gameloop
	{
		while (++x < hk->dt->mapw)
		{
			hk->dt->camerax = ((2 * x) / hk->dt->mapw) - 1;
			hk->dt->raydirx = hk->dt->dirx + (hk->dt->planex * hk->dt->camerax);
			hk->dt->raydiry = hk->dt->diry + (hk->dt->planey * hk->dt->camerax);



		}
	}


	return (0);
}

//inicialización de las variables del rayc y calculo de algunas
int	ft_rayc_memset(t_hook *hk)
{
	hk->dt->mapw = 640;//dimensiones del mapa
	hk->dt->maph = 480;
	ft_get_dir(hk);
//	printf ("El vector direccion:\nX: %f\nY: %f\n", hk->dt->dirx, hk->dt->diry);
	hk->dt->fov = 1.152;//fijo el fov en 66 grados
//	printf ("El FOV: %f\n", (hk->dt->fov * 360) / (2 * 3.1416));
	ft_get_plane(hk);
//	printf ("El vector plano:\nX: %f\nY: %f\n", hk->dt->planex, hk->dt->planey);
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
