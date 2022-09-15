#include "../../include/cub3d.h"

//libero la estructura hk y la gr
void	ft_free_structur (t_hook *hk)
{
	if (hk->gr)
	{
		free(hk->gr);
		hk->gr = NULL;
	}
	if (hk)
	{
		free(hk);
		hk = NULL;
	}
}

//frees saliendo por normal, con errores en mapa,...
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

//frees saliendo por hooks
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
