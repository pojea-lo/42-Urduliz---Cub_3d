#include "cub3d.h"

//chequeo que no haya caracteres raros ni en el mapa ni en los datos
int	ft_ch_data (int	fd)
{
    int		j;
	char	*line;

	line = ft_gnl(fd);
    j = -1;
    while (line)
    {
        if (ft_check_line (line, 2) == 1 && line)
		{
			free (line);
            return (-1);
		}
        free (line);
        line = ft_gnl(fd);
    }
	return (0);
}

//crea a partir del archivo la bidimensional con el mapa
int ft_create_bid (int fd, t_in *dt, char *map)
{
    int     j;
    char    *line;

    dt->map = (char **) malloc (sizeof(char *) * (ft_count_fd (fd, 2) + 1));
    if (!dt->map)
    {
        perror ("Malloc error\n");
        return (-1);
    }
    fd = open(map, O_RDWR);
    line = ft_gnl(fd);
    j = -1;
    while (line)
    {
        if (ft_check_line (line, 2) == 0 && line)
            dt->map[++j] = ft_dup(line);
        free (line);
        line = ft_gnl(fd);
    }
	close (fd);
	dt->map[++j] = NULL;
    if (ft_data_map(dt) == -1)
        return (-1);
    return (0);
}

//cuenta la cantidad de lineas, o de datos (1) o de mapa (2)
int ft_count_fd (int fd, int n)
{
    int     i;
    char    *line;

    i = 0;
    line = ft_gnl(fd);
    while (line)
    {
        if (ft_check_line (line, n) == 0 && line)
            i++;
		free (line);
        line = ft_gnl(fd);
    }
    return (i);
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
    if (n == 2)//control de mapas
    {
        if (line[i] == '1' || line[i] == '0')
            return (0);
        if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'O') && line[i + 1] != 'O')
            return (0);
    }
    else if (n == 1)//contro de datos de color y texturas
    {
        if ((line[i] == 'N' || line[i] == 'S' || line[i] == 'E' || line[i] == 'O') && line [n + 1] == 'O')
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
        printf ("Bad map dimension - Error map\n");
        return (-1);
    }
    return (0);
}
