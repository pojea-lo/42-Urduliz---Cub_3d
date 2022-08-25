#include "cub3d.h"

//chequeo el mapa por si esta cerrado
//Realizo un chequeo buscando 0 y estos 0 solo pueden estar rodeados de otros 0s o de 1s
int ft_ch_close(t_in *dt)
{
    int i;
    int j;
	int max;//valor de posicion máximo de x en cada fila

    i = -1;
    while (dt->map[++i])
    {
		j = 0;
		while (dt->map[i][j])
			j++;
		max = j - 1;
        j = -1;
        while (dt->map[i][++j])
        {
            if (dt->map[i][j] == '0')
			{
				if (ft_ch_close_aux(i, j, max, dt) == -1)
				{
					printf ("No closed map - ");
            		return (-1);
				}
			}
		}
    }
    return (0);
}

//chequeo los espacios que estan entre 1
int ft_ch_close_aux(int i, int j, int max, t_in *dt)
{
	if (i == 0)
		return (-1);
	else if (i == dt->maxy - 1) 
		return (-1);
	else
	{
		if (ft_ch_cl_aux_irow(i, j, max, dt) == -1)
			return (-1);
	}
	return (0);
}

//chequeo 0s en filas intermedias
int ft_ch_cl_aux_irow(int i, int j, int max, t_in *dt)
{
    if (j == 0)//esquina izq
    {
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j + 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i + 1][j + 1] != '1') || ft_ch(i, j + 1, dt, 1) == -1 || ft_ch(i - 1, j, dt, 1) == -1 || ft_ch(i - 1, j + 1, dt, 1) == -1 || ft_ch(i + 1, j, dt, 1) == -1 || ft_ch(i + 1, j + 1, dt, 1) == -1)
            return (-1);
    }
	else if (j == max)//esquina der
	{
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i - 1][j - 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i + 1][j - 1] != '1') || ft_ch(i, j - 1, dt, 1) == -1 || ft_ch(i - 1, j, dt, 1) == -1 || ft_ch(i - 1, j - 1, dt, 1) == -1 || ft_ch(i + 1, j, dt, 1) == -1 || ft_ch(i + 1, j - 1, dt, 1) == -1)
            return (-1);
    }
	else
	{
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i - 1][j - 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i + 1][j - 1] != '1') || (dt->map[i - 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j + 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i + 1][j + 1] != '1') || ft_ch(i, j - 1, dt, 1) == -1 || ft_ch(i, j + 1, dt, 1) == -1 || ft_ch(i - 1, j, dt, 1) == -1 || ft_ch(i - 1, j - 1, dt, 1) == -1 || ft_ch(i - 1, j + 1, dt, 1) == -1 || ft_ch(i + 1, j, dt, 1) == -1 || ft_ch(i + 1, j - 1, dt, 1) == -1 || ft_ch(i + 1, j + 1, dt, 1) == -1)
            return (-1);
    }
	return (0);
}
