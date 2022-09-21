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
			if (dt->map[i][j] != '1' && dt->map[i][j] != '0' && dt->map[i][j] != 'N')
				return (-1);
		}
	}
	return (0);
}
