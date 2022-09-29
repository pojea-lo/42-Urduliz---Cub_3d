#include "../../include/cub3d.h"

//resetea los valores iniciales
t_hook	*ft_memset(t_in *dt)
{
	t_mlx	*gr; //creo la libreria grafica
	t_hook	*hk; //creo la estructura unica para trabajar con las funciones de la mlx

	dt->info = NULL;
	dt->map = NULL;
	dt->tex = NULL;
	dt->color = NULL;
	dt->xo = 0;
	dt->yo = 0;
	gr = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	hk = (t_hook *)malloc(sizeof(t_hook) * 1);
	dt->color = (int **)malloc(sizeof(int *) * 2);
	dt->color[0] = (int *)malloc(sizeof(int) * 3);
	dt->color[1] = (int *)malloc(sizeof(int) * 3);
	if (!gr || !hk || !dt->color || !dt->color[0] || !dt->color[1])
		return (NULL);
	hk->dt = dt;
	hk->gr = gr;
	gr->mlx = mlx_init(); //inicio la libreria gráfica
	return (hk);
}
