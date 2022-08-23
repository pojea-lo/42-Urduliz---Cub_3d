#include "cub3d.h"

int ft_create_bid (int fd, t_in *dt, char *map)//crea a partir del archivo la bidimensional con el mapa
{
    int     i;
    int     j;
    char    *line;

    i = ft_count_fd (fd, 2);
    dt->map = (char **) malloc (sizeof(char *) * (i + 1));
    if (!dt->map)
    {
        perror ("Malloc error\n");
        return (-1);
    }
    fd = open(map, O_RDWR);
    j = -1;
    while (j < i && line)
    {
        line = ft_gnl(fd);
        if (ft_check_line (line, 2) == 0 && line)
            dt->map[++j] = ft_dup(line);
        free (line);
    }
    if (ft_data_map(dt) == -1)
        return (-1);
    return (0);
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
		printf ("%s da j: %d\n", dt->map[dt->maxy], j);
        if (j > dt->maxx)
            dt->maxx = j;
		dt->maxy++;
    }
//    printf ("filas: %d\ncolumnas: %d\n", dt->maxy, dt->maxx);
    if (dt->maxy < 4 || dt->maxx < 4)
    {
        printf ("Bad map dimension - Error map\n");
        return (-1);
    }
    return (0);
}

//cuenta la cantidad de lineas, o de datos (1) o de mapa (2)
int ft_count_fd (int fd, int n)
{
    int     i;
    char    *line;

    i = 0;
    line = "kk";
    while (line)
    {
        line = ft_gnl(fd);
        if (ft_check_line (line, n) == 0 && line)
            i++;
        free (line);
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

//funcion que chequea si el mapa es valido
int ft_check_map(t_in *dt)
{
    int i;

    if (ft_ch_chars(dt) == -1)
        return (-1);
    dt->map = ft_add_columns(dt);
    if (ft_ch_spaces(dt) == -1)
        return (-1);
    if (ft_ch_close(dt) == -1)
        return (-1);
    if (ft_ch_personage(dt) == -1)
        return (-1);
    i = -1;
    while (dt->map[++i])
        printf ("El map %d: <%s>\n", i, dt->map[i]);
    return (0);
}

//chequeo si el personage esta tocando algun espacio o rodeado de 1
int     ft_ch_personage(t_in *dt)
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
            if (dt->map[i][j] == 'N' || dt->map[i][j] == 'S' || dt->map[i][j] == 'E' || dt->map[i][j] == 'O')
            {
                n = ft_ch_personage_out(i, j, dt);
                if (n == 1)
                    printf ("Personage inside limits - ");
                else if (n == 2)
                    printf ("Personage in the air - ");
                else if (n == 3)
                    printf ("Encapsulated personage - ");
                if (n != 0)
                    return (-1);
            }
        }
    }
    return (0);
}

//aux de ft_ch_personage
int     ft_ch_personage_out(int i, int j, t_in *dt)
{
    if (i == 0 || i == (dt->maxy - 1) || j == 0 || j == (dt->maxx - 1))
        return (1);//caso del personage en los limites del mapa
    else if (dt->map[i][j - 1] == ' ' || dt->map[i][j + 1] == ' ' || dt->map[i - 1][j] == ' ' || dt->map[i + 1][j] == ' ')
        return (2);
    else if (dt->map[i - 1][j] == '!' || dt->map[i + 1][j] == '!')
        return (2);
    else if (dt->map[i][j - 1] == '1' && dt->map[i][j + 1] == '1' && dt->map[i - 1][j] == '1' && dt->map[i + 1][j] == '1')
        return (3);
    return (0);
}

//chequeo si el mapa no esta cerrado. Lo comprueba si existen = tocando espacios en blanco
int ft_ch_close(t_in *dt)
{
    int i;
    int j;
    int bo;//buleano por si aparece lo primero un 0

    i = -1;
    while (dt->map[++i])
    {
        bo = 0;
        j = -1;
        while (dt->map[i][++j])
        {
            if (dt->map[i][j] == '1')
                bo = 1;
            if (dt->map[i][j] == '0')
            {
                if (bo == 0 || ft_ch_close_out(i, j, dt) == -1)
                {
                    printf ("No closed map - ");
                    return (-1);
                }
            }
        }
    }
    return (0);
}

//funcion auxiliar del ft_close
int ft_ch_close_out(int i, int j, t_in *dt)
{
    if (i == 0)
    {
        if (dt->map[i + 1][j] == '!' || dt->map[i + 1][j] == ' ')
            return (-1);
    }
    else if (i == dt->maxy - 1)
    {
        if (dt->map[i - 1][j] == '!' || dt->map[i - 1][j] == ' ')
            return (-1);
    }
    else if (i > 0 && i < dt->maxy - 1)
    {
        if (dt->map[i + 1][j] == '!' || dt->map[i - 1][j] == '!' || dt->map[i + 1][j] == ' ' || dt->map[i - 1][j] == ' ')
            return (-1);
    }
    return (0);
}

//chequeo el mapa por si tiene huecos vacios y no 0 entre paredes
int ft_ch_spaces(t_in *dt)
{
    int i;
    int j;

    i = -1;
    while (dt->map[++i])
    {
        j = 0;
        while (dt->map[i][j] == ' ')
            j++;
        while (dt->map[i][j])
        {
            if (dt->map[i][j] == '1' || dt->map[i][j] == ' ')
            {
                while (dt->map[i][j] == '1' && dt->map[i][j])
                    j++;
                if (dt->map[i][j] == '0')
                {
                    while (dt->map[i][j] != '1' && dt->map[i][j])
                    {
                        if (dt->map[i][j] == ' ')
                        {
                            printf ("Bad space in map - ");
                            return (-1);
                        }
                        j++;
                    }
                }
                if (dt->map[i][j] == ' ')
                {
                    if (ft_ch_spaces_out(i, j, dt) == -1)
                        return (-1);
                }
            }
            if (dt->map[i][j])
                j++;
        }
    }
    return (0);
}

//chequeo los espacios que estan entre 1
int ft_ch_spaces_out(int i, int j, t_in *dt)
{
    if (i == 0)
    {
        if (dt->map[i + 1][j] == '0')
        {
            printf ("Bad space in map - ");
            return (-1);
        }
    }
    else if (i == dt->maxy - 1)
    {
        if (dt->map[i - 1][j] == '0')
        {
            printf ("Bad space in map - ");
            return (-1);
        }
    }
    else if (i > 0 && i < dt->maxy - 1)
    {
        if (dt->map[i + 1][j] == '0' || dt->map[i - 1][j] == '0' || dt->map[i][j + 1] == '0')
        {
            printf ("Bad space in map - ");
            return (-1);
        }
    }
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
                if (dt->map[i][j] != 'N' && dt->map[i][j] != 'S' && dt->map[i][j] != 'E' && dt->map[i][j] != 'O')
                {
                    printf ("Bad char in map - ");
                    return (-1);
                }
                n++;
            }
        }
    }
    if (n != 1)
    {
        if (n == 0)
            printf ("No personage in map - ");
        else
            printf ("More than one personage in map - ");
        return (-1);
    }
    return (0);
} 

//cambia el map añadiendo ! en los huecos vacios a la derecha
char    **ft_add_columns(t_in *dt)
{
    char    **aux;
    int     i;
    int     j;

    aux = (char **) malloc (sizeof(char *) * (dt->maxy + 1));
    if (!aux)
        return (NULL);
    i = 0;
    while (dt->map[i])
    {
        aux[i] = (char *) malloc (sizeof(char) * (dt->maxx + 1));
        j = -1;
        while (dt->map[i][++j])
            aux[i][j] = dt->map[i][j];
        while (j < dt->maxx)
            aux[i][j++] = '!';
        aux[i][j] = 00;
        free (dt->map[i++]);
    }
    aux[i] = NULL;
    free (dt->map);
    return (aux);
}
