#include "cub3d.h"

char *ft_gnl(int fd)
{
    char    *buf;
    char    *rest;
    int     rb;

    rest = NULL;
    buf = (char *) malloc (sizeof (char) * 2);
    if (buf == NULL)
        return (NULL);
    while (ft_check(rest) == 0)//mientras haya \n en el rest sigo leyendo
    {
        rb = read (fd, buf, 1);
        if (rb == 0)//final de archivo
        {
            free (buf);
            return (rest);
        }
        buf[1] = 00;
        rest = ft_copy (buf, rest);//meto el buf al rest
    }
    rest = ft_update_rest (rest);
    return (rest);
}

//funcion que quita el salto de linea de la linea
char    *ft_update_rest (char *rest)
{
    char    *aux;
    int     i;
    int     j;

    i = ft_strlen(rest);
    aux = (char *) malloc (sizeof(char) * (i));
    if (!aux)
        return (NULL);
    j = -1;
    while (++j < (i - 1))
        aux[j] = rest[j];
    aux[j] = 00;
    free (rest);
    return (aux);
}

char    *ft_dup(char *oldstr)
{
    int     sz;
    int     i;
    char    *newstr;

    i = -1;
    sz = ft_strlen(oldstr);
    newstr = (char *)malloc (sizeof(char) * (sz + 1));
    while (++i < sz)
        newstr[i] = oldstr[i];
    newstr[i] = 00;
    return (newstr);
}

char    *ft_copy(char *buf, char *rest)
{
    int     sz;
    int     i;
    char    *aux;

    if (rest == NULL)
        rest = ft_dup(buf);
    else
    {
        sz = ft_strlen(rest);
        aux = (char *) malloc (sizeof(char) * (sz + 1));
        i = -1;
        while (++i < sz)
            aux[i] = rest[i];
        aux[i] = 00;
        free (rest);
        rest = (char *) malloc (sizeof(char) * (sz + 2));
        i = -1;
        while (++i < sz)
            rest[i] = aux[i];
        rest[i] = buf[0];
        rest[i + 1] = 00;        
        free (aux);
    }
//    free (buf);
    return (rest);
}

int ft_strlen(char *str)
{
    int i;

	i = 0;
	if (str)
	{
		i = 0;
    	while (str[i] != 00)
        	i++;
	}
//	printf ("Con <%s> tengo i: %d\n", str, i);
    return (i);
}

int ft_check(char *str)
{
    int i;

    i = 0;
    if (str == NULL)
        return (0);
    while (str[i] != '\n' && str[i] != 00)
        i++;
    if (str[i] == 00)
        return (0);
    return (1);
}
