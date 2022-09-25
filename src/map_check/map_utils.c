#include "../../include/cub3d.h"

//funcion que comprueba en el char mandado
int	ft_ch(int i, int j, t_in *dt, int n)
{
	if (dt->map[i][j])
	{
		if (n == 0)//compruebo 1 o esp
		{
			if (dt->map[i][j] != '1' && dt->map[i][j] != ' ')
				return (-1);
		}
		if (n == 1)//compruebo 1 o 0
		{
			if (dt->map[i][j] != '1' && dt->map[i][j] != '0')
				return (-1);
		}
	}
	return (0);
}

//hago la simetria del mapa
char	**ft_matrix_symetric(t_in *dt)
{
	char	**new;
	int		i;
	int		j;

	new = (char **)malloc (sizeof(char *) * (dt->maxy + 1));
	if (!new)
		return (NULL);
	i = 0;
	while (i < dt->maxy)
	{
		j = 0;
		new[i] = (char *) malloc (sizeof(char) * (dt->maxx + 1));
		if (!new[i])
			return (NULL);
		while (j < dt->maxx)
		{
			new[i][j] = dt->map[i][dt->maxx - 1 - j];
			j++;
		}
		new[i][j] = 00;
		i++;
	}
	new[i] = NULL;
	ft_matrix_symetric_aux(dt);
	return (new);
}

//cambio la posicion del personaje a su simetrica en x
void	ft_matrix_symetric_aux(t_in *dt)
{
	dt->xo = dt->maxx - dt->xo;
	ft_free_bidim (dt->map);
}
