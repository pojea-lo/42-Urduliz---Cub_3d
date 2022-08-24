#include "cub3d.h"

//funcion que chequea si el mapa es valido
int ft_ch_map(t_in *dt)
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
