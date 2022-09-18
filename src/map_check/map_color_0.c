#include "../../include/cub3d.h"

//funcion inicial para crear los valores de los colores
int	ft_create_color(t_hook *hk)
{
	if (ft_count_col(hk->dt->info) != 2)
	{
		printf ("Error\nError in number of valid colors - ");
		return (-1);
	}
	if (ft_create_text_col(hk->dt) == -1)
		return (-1);
	return (0);
}

//cuento las lineas de color
int	ft_count_col(char **info)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (info[i])
	{
		if (ft_check_line_two (info[i]) == 0)
			n++;
		i++;
	}
	return (n);
}

//busco en la linea las lineas de los colores
int	ft_check_line_two(char *line)
{
	int	i;

	if (!line)
		return (1);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if ((line[i] == 'F' || line[i] == 'C') && line [i + 1] == ' ')
		return (0);
	return (1);
}

//creo la bidimensional de int de los colores
int	ft_create_text_col(t_in *dt)
{
	int		i;
	int		j;

	dt->color = (int **)malloc(sizeof(int *) * 2);
	dt->color[0] = (int *)malloc(sizeof(int) * 3);
	dt->color[1] = (int *)malloc(sizeof(int) * 3);
	if (!dt->color)
		return (-1);
	i = 0;
	j = -1;
	while (dt->info[i])
	{
		if (ft_check_line_two (dt->info[i]) == 0)
		{
			++j;
			if (ft_dup_atoi(dt, dt->info[i], j) == 1)
			{
				printf ("Error\nBad imput in colors - ");
				return (-1);
			}
		}
		i++;
	}
//	printf ("Color 0: <%d / %d / %d>\n", dt->color[0][0], dt->color[0][1], dt->color[0][2]);
//	printf ("Color 1: <%d / %d / %d>\n", dt->color[1][0], dt->color[1][1], dt->color[1][2]);
	return (0);
}

//funcion que devuelve una cadena de enteros de la linea F o C de color
int	ft_dup_atoi(t_in *dt, char *line, int n)
{
	char	**num;
	int		i;
	int		j;

	num = (char **)malloc(sizeof(char *) * 5);
	if (!num || !line)
		return (1);
	i = 0;
	j = -1;
//con esta parte recorro la cabecera de la linea, hasta los numeros
	while (line[i] && line[i] == ' ')
		i++;
	if (line[i] != 'F' && line[i] != 'C' && line[i + 1] != ' ')
			return (1);
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!(line[i] > 47) && !(line[i] < 58))
		return (1);
//recorro la parte de numeros
	while (++j < 5 && line[i])
	{
		i = ft_line (line, num, i, j);
		if (i == -1)
			return (1);
	}
	if (j != 3)//caso de que me metan mas o menos de 3 numeros
	{
		while (--j >= 0)
			free (num[j]);
		free(num);
		return (1);
	}
	num[j] = NULL;
	ft_atoi_bid(dt, num, n);
	return (0);
}

//aux de la funcion anterior que retorna la i
int	ft_line(char *line, char ** num, int i, int j)
{
	int k;

	line = ft_trim(line, i);
	if (!line)
		return (-1);
	num[j] = (char *)malloc(sizeof(char) * 50);
	if (!num[j])
		return (1);
	k = -1;
	while(line[i] && line[i] > 47 && line[i] < 58)
	{
		num[j][++k] = line[i];
		i++;
	}
	num[j][++k] = 00;
	if (line[i] == ',' && j != 2)
	{
		i++;
		if (!(line[i] > 47) && !(line[i] < 58))
			return (-1);
	}
	else if (line[i] == 00 && j == 2)
		return (i);
	else
		return (-1);
	return (i);
}

//quito todos los espacios que no estén entre numeros
char *ft_trim(char *line, int i)
{
	int	j;

	j = 0;
	while (line[i])
	{
		if (line[i] == ' ')
		{
			if (line[i - 1] > 47 && line[i - 1] < 58)
			{
				j = i;
				while (line[j] == ' ')
					j++;
				if (line[j] > 47 && line[j] < 58)
					return (NULL);
			}
			j = i;
			while (line[j])
			{
				line[j] = line[j + 1];
				j++;
			}

		}
		if (line[i] && line[i] != ' ')
			i++;
	}
	return (line);
}

//hago el itoa de una bidimensional de chars
int	ft_atoi_bid(t_in *dt, char **num, int n)
{
	int	i;
	int	k;

	i = -1;
	while (num[++i])
	{
		k = 0;
		while (num[i][k])
			k++;
		if (k > 3)//comprobacion por si me meten un numero con mas de 3 cifras
			return (1);
		dt->color[n][i] = 0;
		k = -1;
		while (num[i][++k])
			dt->color[n][i] = (num[i][k] - '0') + (dt->color[n][i] * 10);
		if (dt->color[n][i] > 255)
			return (1);
		free(num[i]);
	}
	free(num);
	return (0);
}
