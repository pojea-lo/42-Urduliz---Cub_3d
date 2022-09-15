#include "../../include/cub3d.h"

//resetea los valores iniciales
t_hook	*ft_memset(t_in *dt)
{
	t_mlx	*gr;//creo la libreria grafica
	t_hook	*hk;//creo la estructura unica para trabajar con las funciones de la mlx

	dt->info = NULL;
	dt->map = NULL;
	dt->tex = NULL;
	dt->color = NULL;
	dt->xo = 0;
	dt->yo = 0;
	gr = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	hk = (t_hook *)malloc(sizeof(t_hook) * 1);
	if (!gr || !hk)
		return (NULL);
	hk->dt = dt;
	hk->gr = gr;
	gr->mlx = mlx_init();//inicio la libreria gráfica
	return (hk);
}

//inicialización de las variables del rayc y calculo de algunas
int	ft_rayc_memset(t_hook *hk)
{
	hk->dt->i = 0;//buleano para la direccion QUITAR
	hk->dt->mapw = 920;//dimensiones del mapa
	hk->dt->maph = 720;
//	hk->dt->fov = 1.152;//fijo el fov en 66 grados
	hk->dt->fov = 1.5708;//fijo el fov en 90 grados
	hk->dt->movespeed = 0.25;
	hk->dt->rotspeed = 0.2;
	ft_get_dir(hk);
//	printf ("El vector direccion:\nX: %f\nY: %f\n", hk->dt->dirx, hk->dt->diry);
//	printf ("El FOV: %f\n", (hk->dt->fov * 360) / (2 * 3.1416));
	ft_get_plane(hk);
//	printf ("El vector plano:\nX: %f\nY: %f\n", hk->dt->planex, hk->dt->planey);
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
