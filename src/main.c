#include "../include/cub3d.h"

int	main(int argc, char *argv[])
{
	int		fd;
	t_in	dt;//inicio estructura de datos inicial

	if (argc != 2)
	{
		printf("Error\nError in arguments\n");
		return (0);
	}
	fd = open(argv[1], O_RDWR);//lo cierro en la funcion count info, que es donde primero lo uso
	if (fd == -1)
	{
		printf("Error\nMap does't exist\n");
		return (0);
	}
	ft_traspas(fd, argv[1], &dt);
	ft_free(&dt);
//	system("leaks cub");
	return (0);
}

//funcion inicial que empieza a analizar el mapa
int	ft_traspas(int fd, char *argv, t_in *dt)
{
	t_hook	*hk;

	hk = ft_memset(dt);
	dt->info = ft_get_info(fd, argv, dt);
	if (!dt->info)
	{
		printf ("Data error\n");
		return (-1);
	}
	if (ft_create_text(hk) == -1)
	{
		printf ("Texture error\n");
		return (-1);
	}
	if (ft_create_bid(dt) == -1)
		return (-1);
	if (ft_ch_map(dt) == -1)
	{
		printf ("Map error\n");
		return (-1);
	}
	if (ft_draw_map (hk) == -1)
	{
		printf ("Draw map error\n");
		return (-1);
	}
	free (hk->gr);
	hk->gr = NULL;
	free (hk);
	hk = NULL;
	return (0);
}

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
	gr = NULL;
	hk = NULL;
	gr = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	hk = (t_hook *)malloc(sizeof(t_hook) * 1);
	if (!gr || !hk)
		return (NULL);
	hk->dt = dt;
	hk->gr = gr;
	gr->mlx = mlx_init();//inicio la libreria gráfica 
	return (hk);
}

void	ft_free(t_in *dt)
{
	int	i;

	if (dt->info)
	{
		i = -1;
		while (dt->info[++i])
			free (dt->info[i]);
		free (dt->info);
		dt->info = NULL;
	}
	if (dt->map)
	{
		i = -1;
		while (dt->map[++i])
			free (dt->map[i]);
		free (dt->map);
		dt->map = NULL;
	}
	if (dt->tex)
	{
		i = -1;
		while (dt->tex[++i])
			free (dt->tex[i]);
		free (dt->tex);
		dt->tex = NULL;
	}
	if (dt->color)
	{
		free (dt->color[0]);
		free (dt->color[1]);
		free (dt->color);
		dt->color = NULL;
	}
}

void	ft_free_hk(t_hook *hk)
{
	int	i;

	if (hk->dt->info)
	{
		i = -1;
		while (hk->dt->info[++i])
			free (hk->dt->info[i]);
		free (hk->dt->info);
		hk->dt->info = NULL;
	}
	if (hk->dt->map)
	{
		i = -1;
		while (hk->dt->map[++i])
			free (hk->dt->map[i]);
		free (hk->dt->map);
		hk->dt->map = NULL;
	}
	if (hk->dt->tex)
	{
		i = -1;
		while (hk->dt->tex[++i])
			free (hk->dt->tex[i]);
		free (hk->dt->tex);
		hk->dt->tex = NULL;
	}
	if (hk->dt->color)
	{
		free (hk->dt->color[0]);
		free (hk->dt->color[1]);
		free (hk->dt->color);
		hk->dt->color = NULL;
	}
	free (hk->gr);
	hk->gr = NULL;
	free (hk);
	hk = NULL;
}
