#include "../../include/cub3d.h"

//chequeo el mapa por si tiene huecos vacios y abiertos
//Realizo un chequeo buscando espacios en blanco y estos espacios solo pueden estar rodeados de otro espacio en blanco o de 1s
int ft_ch_spaces(t_in *dt)
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
            if (dt->map[i][j] == ' ')
			{
				if (ft_ch_spaces_aux(i, j, max, dt) == -1)
				{
					printf ("Falla con sp\nx: %d\ny: %d\nchar: %c\n", j, i, dt->map[i][j]);
					printf ("Bad space in map - ");
            		return (-1);
				}
			}
		}
    }
    return (0);
}

//chequeo los espacios que estan entre 1
int ft_ch_spaces_aux(int i, int j, int max, t_in *dt)
{
	if (i == 0)
	{
		if (ft_ch_sp_aux_frow(i, j, max, dt) == -1)
			return (-1);
	}
	else if (i == dt->maxy - 1) 
	{
		if (ft_ch_sp_aux_lrow(i, j, max, dt) == -1)
			return (-1);
	}
	else
	{
		if (ft_ch_sp_aux_irow(i, j, max, dt) == -1)
			return (-1);
	}
	return (0);
}

//chequeo espacios en la primera fila
int ft_ch_sp_aux_frow(int i, int j, int max, t_in *dt)
{
    if (j == 0)//esquina sup izq
    {
        if ((dt->map[i + 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i + 1][j + 1] != '1') || ft_ch(i + 1, j, dt, 0) == -1 || ft_ch(i + 1, j + 1, dt, 0) == -1 || ft_ch(i, j + 1, dt, 0) == -1)  
            return (-1);
    }
	else if (j == max)//esquina sup der
	{
        if ((dt->map[i + 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i + 1][j - 1] != '1') || ft_ch(i + 1, j, dt, 0) == -1 || ft_ch(i + 1, j - 1, dt, 0) == -1 || ft_ch(i, j - 1, dt, 0) == -1)  
            return (-1);
    }
	else//fila superior sin esquinas
	{
        if ((dt->map[i + 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i + 1][j - 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i + 1][j + 1] != '1') || (ft_ch(i, j - 1, dt, 0) == -1 || ft_ch(i, j + 1, dt, 0) == -1 || ft_ch(i + 1, j, dt, 0) == -1 || ft_ch(i + 1, j - 1, dt, 0) == -1 || ft_ch(i + 1, j + 1, dt, 0) == -1))
            return (-1);
    }
	return (0);
}

//chequeo espacios en la ultima fila
int ft_ch_sp_aux_lrow(int i, int j, int max, t_in *dt)
{
    if (j == 0)//esquina inf izq
    {
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j + 1] != '1') || ft_ch(i - 1, j, dt, 0) == -1 || ft_ch(i - 1, j + 1, dt, 0) == -1 || ft_ch(i, j + 1, dt, 0) == -1)
            return (-1);
    }
	else if (j == max)//esquina inf der
	{
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i - 1][j - 1] != '1') || ft_ch(i - 1, j, dt, 0) == -1 || ft_ch(i - 1, j - 1, dt, 0) == -1 || ft_ch(i, j - 1, dt, 0) == -1)
            return (-1);
    }
	else
	{
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i - 1][j - 1] != '1') || (dt->map[i - 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j + 1] != '1') || (ft_ch(i, j - 1, dt, 0) == -1 || ft_ch(i, j + 1, dt, 0) == -1 || ft_ch(i - 1, j, dt, 0) == -1 || ft_ch(i - 1, j - 1, dt, 0) == -1 || ft_ch(i - 1, j + 1, dt, 0) == -1))
            return (-1);
    }
	return (0);
}

//chequeo espacios en filas intermedias
int ft_ch_sp_aux_irow(int i, int j, int max, t_in *dt)
{
    if (j == 0)//esquina izq
    {
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j + 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i + 1][j + 1] != '1') || ft_ch(i, j + 1, dt, 0) == -1 || ft_ch(i - 1, j, dt, 0) == -1 || ft_ch(i - 1, j + 1, dt, 0) == -1 || ft_ch(i + 1, j, dt, 0) == -1 || ft_ch(i + 1, j + 1, dt, 0) == -1)
            return (-1);
    }
	else if (j == max)//esquina der
	{
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i - 1][j - 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i + 1][j - 1] != '1') || ft_ch(i, j - 1, dt, 0) == -1 || ft_ch(i - 1, j, dt, 0) == -1 || ft_ch(i - 1, j - 1, dt, 0) == -1 || ft_ch(i + 1, j, dt, 0) == -1 || ft_ch(i + 1, j - 1, dt, 0) == -1)
            return (-1);
    }
	else
	{
        if ((dt->map[i - 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i - 1][j - 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j - 1] == '1' && dt->map[i + 1][j - 1] != '1') || (dt->map[i - 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j + 1] != '1') || (dt->map[i + 1][j] == '1' && dt->map[i][j + 1] == '1' && dt->map[i + 1][j + 1] != '1') || ft_ch(i, j - 1, dt, 0) == -1 || ft_ch(i, j + 1, dt, 0) == -1 || ft_ch(i - 1, j, dt, 0) == -1 || ft_ch(i - 1, j - 1, dt, 0) == -1 || ft_ch(i - 1, j + 1, dt, 0) == -1 || ft_ch(i + 1, j, dt, 0) == -1 || ft_ch(i + 1, j - 1, dt, 0) == -1 || ft_ch(i + 1, j + 1, dt, 0) == -1)
            return (-1);
    }
	return (0);
}
