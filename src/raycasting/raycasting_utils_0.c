#include "../../include/cub3d.h"

//LE HE PUESTO A LA X=0 EN VEZ DE -1 PARA HACERLO SIMETRICO!!!
////funcion inicial del raycasting
int	ft_rayc_init(t_hook *hk)
{
	int	x;

	x = -1;//CAMBIO, antes tenia -1, de esta forma no dibuja el primer pixel
	while (++x < hk->dt->mapw)
	{
		ft_rayc_memset_2(hk);
		hk->dt->camerax = (2 * x) / hk->dt->mapw - 1;
		hk->dt->raydirx = hk->dt->dirx + (hk->dt->planex * hk->dt->camerax);
		hk->dt->raydiry = hk->dt->diry + (hk->dt->planey * hk->dt->camerax);
		hk->dt->deltadistx = fabs(1 / hk->dt->raydirx);
		hk->dt->deltadisty = fabs(1 / hk->dt->raydiry);
		ft_calcul_step(hk);
		ft_dda_algorithm(hk);
		hk->dt->lineheight = (int)(hk->dt->maph / hk->dt->perpwalldist);
		hk->dt->drawstart = -hk->dt->lineheight / 2 + hk->dt->maph / 2;
		if (hk->dt->drawstart < 0)
			hk->dt->drawstart = 0;
		hk->dt->drawend = hk->dt->lineheight / 2 + hk->dt->maph / 2;
		if (hk->dt->drawend >= hk->dt->maph)
			hk->dt->drawend = hk->dt->maph - 1;
//		ft_draw_line(hk, x);//dibuja por colores
		ft_draw_texture(hk, x);
	}
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win, hk->gr->img, 0, 0);
	mlx_put_image_to_window(hk->gr->mlx, hk->gr->mlx_win, hk->gr->gun, 438, 400);
	return (0);
}

//dibujo de la textura
int	ft_draw_texture(t_hook *hk, int x)
{
	hk->dt->texnum = ft_cal_texnum(hk);
	if (hk->dt->side == 0)
		hk->dt->wallx = hk->dt->yo + (hk->dt->perpwalldist * hk->dt->raydiry);
	else if (hk->dt->side == 1)
		hk->dt->wallx = hk->dt->xo + (hk->dt->perpwalldist * hk->dt->raydirx);
	hk->dt->wallx -= floor((hk->dt->wallx));
	hk->dt->texx = (int)(hk->dt->wallx * (double)hk->dt->texwidth);
	if (hk->dt->side == 0 && hk->dt->raydirx > 0)
		hk->dt->texx = hk->dt->texwidth - hk->dt->texx - 1;
	if (hk->dt->side == 1 && hk->dt->raydiry < 0)
		hk->dt->texx = hk->dt->texwidth - hk->dt->texx - 1;
	hk->dt->step = 1.0 * hk->dt->texheight / hk->dt->lineheight;
	hk->dt->texpos = ((hk->dt->drawstart - hk->dt->maph / 2) + (hk->dt->lineheight / 2)) * hk->dt->step;
	ft_print_tex(hk, x);
	return (0);
}

//calculo el numero de textura en funcion de donde pegue
int	ft_cal_texnum(t_hook *hk)
{
	int	texnum;

	texnum = 0;
	if (hk->dt->side == 0)
	{
		if (hk->dt->raydirx > 0)
			texnum = 3;
		else
			texnum = 2;
	}
	else if (hk->dt->side == 1)
	{
		if (hk->dt->raydiry > 0)
			texnum = 1;
		else
			texnum = 0;
	}
	hk->dt->texwidth = hk->dt->texture[texnum].w;
	hk->dt->texheight = hk->dt->texture[texnum].h;
	return (texnum);
}

//dibuja en la imagen la textura con los datos
void	ft_print_tex(t_hook *hk, int x)
{
	int	y;
	int	color_c;
	int	color_f;

	y = 0;
	color_c = ft_color_converter(hk->dt, 0);
	color_f = ft_color_converter(hk->dt, 1);
	while (y < hk->dt->drawstart)
		my_mlx_pixel_put(hk, x, y++, color_c);
	y = hk->dt->drawstart;
	while (y < hk->dt->drawend)
	{
		hk->dt->texy = (int)hk->dt->texpos & (int)(hk->dt->texheight - 1);
		hk->dt->texpos += hk->dt->step;
		hk->dt->colo = get_mlx_pixel_color(&hk->dt->texture[hk->dt->texnum], hk->dt->texx, hk->dt->texy);
		my_mlx_pixel_put(hk, x, y, hk->dt->colo);
		y++;
	}
	while (y < hk->dt->maph)
	{
		my_mlx_pixel_put(hk, x, y, color_f);
		y++;
	}
}

//coge el color del mapa y lo convierte a hexadecimal
int	ft_color_converter(t_in *dt, int i)
{
	int		res;
	int		j;//posicion en el array de la C

	res = 0;
	j = 0;//si C esta en la primera posicion del color
	if (ft_ch_sky(dt) != 0)
		j = 1;//si el C está en la segunda posicion del color
	if (i == 0)
	{
		res = dt->color[j][0];
		res = (res << 8) | dt->color[j][1];
		res = (res << 8) | dt->color[j][2];
	}
	else if (i != 0)
	{
		if (j == 0)
			j = 1;
		else if (j == 1)
			j = 0;
		res = dt->color[j][0];
		res = (res << 8) | dt->color[j][1];
		res = (res << 8) | dt->color[j][2];
	}
	return (res);
}

//funcion que chequea la posicion de C en el array de info. Si aparece primero que la F devuelve 0 (porque esa será su posicion en el array) y si no 1
int	ft_ch_sky(t_in *dt)
{
	int	i;

	i = -1;
	while (dt->info[++i])
	{
		if (ft_ch_line_two(dt->info[i]) == 0)
			return (0);
		else if (ft_ch_line_two(dt->info[i]) == 1)
			return (1);
	}
	return (-1);
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
			hk->dt->hit = 1;
	}
	if (hk->dt->side == 0)
		hk->dt->perpwalldist = (hk->dt->sidedistx - hk->dt->deltadistx);
	else
		hk->dt->perpwalldist = (hk->dt->sidedisty - hk->dt->deltadisty);
}

//LE HA AÑADIDO AQUI EL +1 A TODO PARA HACERLO SIMETRICO!!!
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
		hk->dt->sidedistx = (hk->dt->mapx + 1.0 - hk->dt->xo) * hk->dt->deltadistx;
	}
	if (hk->dt->raydiry < 0)//valor del stepy
	{
		hk->dt->stepy = -1;
		hk->dt->sidedisty = (hk->dt->yo - hk->dt->mapy) * hk->dt->deltadisty;
	}
	else
	{
		hk->dt->stepy = 1;
		hk->dt->sidedisty = (hk->dt->mapy + 1.0 - hk->dt->yo) * hk->dt->deltadisty;
	}
}

//inicialización de las variables del rayc y calculo de algunas
int	ft_rayc_memset(t_hook *hk)
{
	hk->dt->mapw = WIN_WIDTH;//dimensiones del mapa
	hk->dt->maph = WIN_HEIGHT;
//	hk->dt->fov = 1.152;//fijo el fov en 66 grados
	hk->dt->fov = 1.5708;//fijo el fov en 90 grados
	hk->dt->movespeed = 0.20;
	hk->dt->rotspeed = 0.10;
	ft_get_dir(hk);
	ft_get_plane(hk);
	hk->dt->sidedistx = 0;
	hk->dt->sidedisty = 0;
	hk->dt->deltadistx = 0;
	hk->dt->deltadisty = 0;
	hk->dt->rotation_left = false;
	hk->dt->rotation_right = false;
	hk->dt->up = false;
	hk->dt->down = false;
	hk->dt->right = false;
	hk->dt->left = false;
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
		hk->dt->planex = atan(hk->dt->fov / 2);
		if (hk->dt->dir == 'S')
			hk->dt->planex *= -1;
	}
	else if (hk->dt->dir == 'E' || hk->dt->dir == 'W')
	{
		hk->dt->planex = 0;
		hk->dt->planey = atan(hk->dt->fov / 2);
		if (hk->dt->dir == 'W')
			hk->dt->planey *= -1;
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
	else if (hk->dt->dir == 'W')
	{
		hk->dt->dirx = -1;
		hk->dt->diry = 0;
	}
	return (0);
}
