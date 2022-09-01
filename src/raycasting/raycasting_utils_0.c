#include "../../include/cub3d.h"

//LE HE PUESTO A LA X=0 EN VEZ DE -1 PARA HACERLO SIMETRICO!!!I
////funcion inicial del raycasting
int	ft_rayc_init(t_hook *hk)
{
	int	x;

	x = -1;

//	ft_rayc_memset(hk);
//	while (1)//comienza el gameloop
	{
		while (++x < hk->dt->mapw)
		{
			ft_rayc_memset_2(hk);
			hk->dt->camerax = ((2 * x) / hk->dt->mapw - 1);
//			printf ("La camerax: %f\n", hk->dt->camerax);
			hk->dt->raydirx = hk->dt->dirx + (hk->dt->planex * hk->dt->camerax) * (-1);//multiplico por -1 pq me lo dibujaba simetrico
			hk->dt->raydiry = hk->dt->diry + (hk->dt->planey * hk->dt->camerax);
//			printf ("Los raydir:\nX: %f\nY: %f\n", hk->dt->raydirx, hk->dt->raydiry);
			hk->dt->deltadistx = fabs(1 / hk->dt->raydirx);
			hk->dt->deltadisty = fabs(1 / hk->dt->raydiry);
//			printf ("Las deltadist:\nX: %f\nY: %f\n", hk->dt->deltadistx, hk->dt->deltadisty);
			ft_calcul_step(hk);
			ft_dda_algorithm(hk);
			hk->dt->lineheight = (int)(hk->dt->maph / hk->dt->perpwalldist);
			hk->dt->drawstart = (int)(-hk->dt->lineheight / 2 + hk->dt->maph / 2);
			if (hk->dt->drawstart < 0)
				hk->dt->drawstart = 0;
			hk->dt->drawend = (int)(hk->dt->lineheight / 2 + hk->dt->maph / 2);
			if (hk->dt->drawend >= hk->dt->maph)
				hk->dt->drawend = hk->dt->maph - 1;
//			printf ("La linea empieza: %d y termina %d\n", hk->dt->drawstart, hk->dt->drawend);
//			ft_draw_line(hk, x);
//			ft_draw_texture(hk, x);
		}
	}


	return (0);
}

//dibujo de la textura
int	ft_draw_texture(t_hook *hk, int x)
{
	int	y;

	hk->dt->texnum = hk->dt->map[hk->dt->mapy][hk->dt->mapx];
	if (hk->dt->side == 0)
		hk->dt->wallx = hk->dt->yo + (hk->dt->perpwalldist * hk->dt->raydiry);
	else if (hk->dt->side == 1)
		hk->dt->wallx = hk->dt->xo + (hk->dt->perpwalldist * hk->dt->raydirx);
	hk->dt->texx = (int)(hk->dt->wallx * hk->dt->texwidth);//(*)
	if((hk->dt->side == 0 && hk->dt->raydirx > 0) || (hk->dt->side == 1 && hk->dt->raydiry < 0))
		hk->dt->texx = hk->dt->texwidth - hk->dt->texx - 1;
	hk->dt->step = 1.0 * hk->dt->texheight / hk->dt->lineheight;
	hk->dt->texpos = (hk->dt->drawstart - hk->dt->maph / 2 + hk->dt->lineheight / 2) * hk->dt->step;
	y = hk->dt->drawstart;
	while (y++ < hk->dt->drawend)
	{
		hk->dt->texy = (int)hk->dt->texpos;
		if (hk->dt->texy > hk->dt->texheight)
			hk->dt->texy = hk->dt->texheight - 1;
		hk->dt->texpos += hk->dt->step;
/*		Uint32 color = texture[texNum][texHeight * texY + texX];
		if (hk->dt->side == 1)
			color = (color >> 1) & 8355711;
		buffer[y][x] = color;
*/		if (x == 1e30)
			printf ("x: %d\n", x);
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
//			printf ("choca en:\nx: %d\ny: %d\nvalor: %c\n", hk->dt->mapx, hk->dt->mapy, hk->dt->map[hk->dt->mapy][hk->dt->mapx]);
		}
//		printf ("avanzo:\nx: %d\ny: %d\n", hk->dt->mapx, hk->dt->mapy);
		if (hk->dt->hit == 1)//calculo la distancia al punto de choque
		{
			if (hk->dt->side == 0)
				hk->dt->perpwalldist = (hk->dt->sidedistx - hk->dt->deltadistx);
			else if (hk->dt->side == 1)
				hk->dt->perpwalldist = (hk->dt->sidedisty - hk->dt->deltadisty);
//			printf ("la dist: %f\n", hk->dt->perpwalldist);
		}
	}
}

//LE HA AÑADIDO AQUI EL +1 A TODO PARA HACERLO SIMETRICO!!!
//calculo los steps y las sidedist
void	ft_calcul_step(t_hook *hk)
{
	if (hk->dt->raydirx < 0)//valor de los steps y sededist
	{
		hk->dt->stepx = -1;
		hk->dt->sidedistx = (hk->dt->xo + 1.0 - hk->dt->mapx) * hk->dt->deltadistx;
	}
	else
	{
		hk->dt->stepx = 1;
		hk->dt->sidedistx = (hk->dt->mapx + 1.0 - hk->dt->xo) * hk->dt->deltadistx;
	}
	if (hk->dt->raydiry < 0)//valor del stepy
	{
		hk->dt->stepy = -1;
		hk->dt->sidedisty = (hk->dt->yo + 1.0 - hk->dt->mapy) * hk->dt->deltadisty;
	}
	else
	{
		hk->dt->stepy = 1;
		hk->dt->sidedisty = (hk->dt->mapy + 1.0 - hk->dt->yo) * hk->dt->deltadisty;
	}
//	printf ("sidedistX: %f\nsidedistY: %f\n", hk->dt->sidedistx, hk->dt->sidedisty);
}

//inicialización de las variables del rayc y calculo de algunas
int	ft_rayc_memset(t_hook *hk)
{
	hk->dt->mapw = 960;//dimensiones del mapa
	hk->dt->maph = 720;
	hk->dt->texwidth = 64;//dimensiones de la textura
	hk->dt->texheight = 64;
	printf("%f\n",hk->dt->fov);
	if (hk->dt->fov != 1.5708)
	{
		printf("Entro aquio");
		ft_get_dir(hk);
	}
	
//	printf ("El vector direccion:\nX: %f\nY: %f\n", hk->dt->dirx, hk->dt->diry);
	//hk->dt->fov = 1.152;//fijo el fov en 66 grados
	hk->dt->fov = 1.5708;//fijo el fov en 90 grados
//	printf ("El FOV: %f\n", (hk->dt->fov * 360) / (2 * 3.1416));
	ft_get_plane(hk);
//	printf ("El vector plano:\nX: %f\nY: %f\n", hk->dt->planex, hk->dt->planey);
	hk->dt->sidedistx = 0;
	hk->dt->sidedisty = 0;
	hk->dt->deltadistx = 0;
	hk->dt->deltadisty = 0;
	hk->dt->stepx = 0;
	hk->dt->stepy = 0;
	hk->dt->side = -1;//ni 0 ni 1
	return (0);
}

int	ft_rayc_memset_2(t_hook *hk)
{
	hk->dt->mapx = hk->dt->xo;
	hk->dt->mapy = hk->dt->yo;
	hk->dt->hit = 0;
	return (0);
}

//obtengo el vector plano de pantall
int	ft_get_plane(t_hook *hk)
{
	if (hk->dt->dir == 'N' || hk->dt->dir == 'S')
	{
		hk->dt->planey = 0;
		hk->dt->planex = hk->dt->diry * tan(hk->dt->fov / 2);
	}
	else if (hk->dt->dir == 'E' || hk->dt->dir == 'O')
	{
		hk->dt->planex = 0;
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
