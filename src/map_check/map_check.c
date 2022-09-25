#include "../../include/cub3d.h"

//funcion que chequea si el mapa es valido
int	ft_ch_map(t_in *dt)
{
	if (ft_ch_chars(dt) == -1)
		return (-1);
	dt->map = ft_add_columns(dt);
	if (ft_ch_personage(dt) == -1)
		return (-1);
	dt->map[(int)dt->yo][(int)dt->xo] = '0';//sustituyo el personaje por 0
	if (ft_ch_spaces(dt) == -1)
		return (-1);
	if (ft_ch_close(dt) == -1)
		return (-1);
	int i = -1;
	while (dt->map[++i])
		printf ("El map %d: <%s>\n", i, dt->map[i]);
//	dt->map = ft_matrix_symetric(dt);
	if (!dt->map)
		return (-1);
	i = -1;
	while (dt->map[++i])
		printf ("El map %d: <%s>\n", i, dt->map[i]);
	return (0);
}

//chequeo el mapa por si tiene chars prohibidos o permitidos duplicados
int ft_ch_chars(t_in *dt)
{
	int i;
	int j;
	int n;

	i = -1;
	n = 0;
	while (dt->map[++i])
	{
		j = -1;
		while (dt->map[i][++j])
		{
			if (dt->map[i][j] != '0' && dt->map[i][j] != '1' && dt->map[i][j] != ' ')
			{
				if (dt->map[i][j] != 'N' && dt->map[i][j] != 'S' && dt->map[i][j] != 'E' && dt->map[i][j] != 'W')
				{
					printf ("Error\nBad char in map - ");//chequeada la salida y SL
					return (-1);
				}
				n++;
			}
		}
	}
	if (ft_ch_chars_aux(dt, n) == -1)
		return (-1);
	return (0);
}

//funcion que guarda la posición del personaje en la estructura
int	ft_ch_chars_aux(t_in *dt, int n)
{
	int	i;
	int	j;

	if (n != 1)
		return (printf ("Error\nIncorrect personage number - "), -1);//salida chequeada y SL
	else
	{
		i = -1;
		while (dt->map[++i])
		{
			j = -1;
			while (dt->map[i][++j])
			{
				if (dt->map[i][j] != '0' && dt->map[i][j] != '1' && dt->map[i][j] != ' ')
				{
					dt->xo = j + 0.5;
					dt->yo = i + 0.5;
				}
			}
		}
	}
//	printf ("El personaje esta en:\ni: %d\nj: %d\n", dt->yo, dt->xo);
	return (0);
}

//chequeo si el personage esta en los limites del mapa, tocando algun espacio o rodeado de 1
int ft_ch_personage(t_in *dt)
{
    int i;
    int j;
    int n;

    i = -1;
    while (dt->map[++i])
    {
        j = -1;
        while (dt->map[i][++j])
        {
            if (dt->map[i][j] == 'N' || dt->map[i][j] == 'S' || dt->map[i][j] == 'E' || dt->map[i][j] == 'W')
            {
                n = ft_ch_personage_aux(i, j, dt);
                if (n == 1)
                    printf ("Error\nPersonage inside limits - ");
                else if (n == 2)
                    printf ("Error\nPersonage in the air - ");
                else if (n == 3)
                    printf ("Error\nEncapsulated personage - ");
                if (n != 0)
                    return (-1);
            }
        }
    }
    return (0);
}

//aux de ft_ch_personage
int     ft_ch_personage_aux(int i, int j, t_in *dt)
{
	dt->dir = dt->map[i][j];//guardo la direccion del personaje
    if (i == 0 || i == (dt->maxy - 1) || j == 0 || j == (dt->maxx - 1))
        return (1);//caso del personage en los limites del mapa
    else if (dt->map[i][j - 1] == ' ' || dt->map[i][j + 1] == ' ' || dt->map[i - 1][j] == ' ' || dt->map[i + 1][j] == ' ')
        return (2);
    else if (dt->map[i][j - 1] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j] == '1' && dt->map[i + 1][j] == '1')
        return (3);
    return (0);
}
