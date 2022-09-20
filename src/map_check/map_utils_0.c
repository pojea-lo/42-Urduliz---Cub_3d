#include "../../include/cub3d.h"

//crea a partir del archivo la bidimensional con el mapa
int ft_create_bid (t_in *dt)
{
    int		i;
	int     j;

    dt->map = (char **) malloc (sizeof(char *) * (ft_count_fd (dt->info, 2) + 1));
    if (!dt->map)
        return (-1);
    i = -1;
	j = -1;
    while (dt->info[++i])
    {
       if (ft_check_line (dt->info[i], 2) == 0)
	   {
            dt->map[++j] = ft_dup(dt->info[i]);
	   		printf ("<%s>\n", dt->map[j]);
	   }
    }
	dt->map[++j] = NULL;
    if (ft_data_map(dt) == -1)
        return (-1);
    return (0);
}

//cuenta la cantidad de lineas, o de datos (1) o de mapa (2)
int ft_count_fd (char **info, int n)
{
    int     i;
	int		r;

	i = 0;
	r = 0;
    while (info[i])
    {
        if (ft_check_line (info[i], n) == 0)
            r++;
		i++;
    }
    return (r);
}

//chequeo si la linea vale para datos (n = 1) o para mapa (n = 2)
int ft_check_line(char *line, int n)
{
    int     i;

    if (!line)
        return (1);
    i = 0;
    while (line[i] && line[i] == ' ')//avanzo los espacios en blanco
        i++;
    if (n == 1 && line[i] && line[i + 1])//control de datos de texturas
    {
        if ((((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O') || (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W' && line [i + 1] == 'E')) && line[i + 2] == ' ')
            return (0);
    }
	else if (n == 2 && line[i])//control de mapas
    {
        if (((line[i] == 'N' || line[i] == 'S') && line[i + 1] == 'O') || (line[i] == 'E' && line[i + 1] == 'A') || (line[i] == 'W' && line [i + 1] == 'E'))
            return (1);
		if ((line[i] == 'F' || line[i] == 'C') && (line[i + 1] == ' '))
			return (1);
		else
			return (0);
    }
    return (1);
}

//funcion que guarda el numero de filas y columnas del mapa.
//Si no son > 4 da error de dimension
int ft_data_map(t_in *dt)
{
    int j;

    dt->maxy = 0;
    dt->maxx = 0;
	while (dt->map[dt->maxy])
    {
        j = ft_strlen(dt->map[dt->maxy]);
        if (j > dt->maxx)
            dt->maxx = j;
		dt->maxy++;
    }
    if (dt->maxy < 4 || dt->maxx < 4)
    {
        printf ("Error\nBad map dimension - Error map\n");
        return (-1);
    }
    return (0);
}
