#include "../../include/cub3d.h"

//funcion inicial para crear los valores de los colores
int	ft_create_color(t_hook *hk)
{
	if (ft_count_col(hk->dt->info) == -1)
	{
		printf ("Error\nError in number of valid colors - ");//salida chequeada y SL
		return (-1);
	}
	if (ft_create_text_col(hk->dt) == -1)
		return (-1);
	return (0);
}

//cuento las lineas de color
int	ft_count_col(char **info)
{
	int	i;
	int	j;
	int	n[2];

	i = -1;
	while (++i < 2)
		n[i] = 0;
	i = -1;
	while (info[++i])
	{
		j = ft_count_col_aux(info[i]);
		if (j == 0 || j == 1)
			n[j] += 1;
	}
	i = -1;
	while (++i < 2)
	{
		if (n[i] != 1)
			return (-1);
	}
	return (0);
}

int	ft_count_col_aux(char *info)
{
	int	j;

	j = 0;
	while (info[j] == ' ')
		j++;
	if (info[j] == 'C')
	{
		if(info[++j] && info[j] == ' ')
			return (0);
	}
	else if (info[j] == 'F')
	{
		if (info[++j] && info[j] == ' ')
			return (1);
	}
	return (-1);
}

//creo la bidimensional de int de los colores
int	ft_create_text_col(t_in *dt)
{
	int		i;
	int		j;

	dt->color = (int **)malloc(sizeof(int *) * 2);
	dt->color[0] = (int *)malloc(sizeof(int) * 3);
	dt->color[1] = (int *)malloc(sizeof(int) * 3);
	if (!dt->color || !dt->color[0] || !dt->color[1])
		return (-1);
	i = 0;
	j = -1;
	while (dt->info[i])
	{
		if (ft_check_line_two (dt->info[i]) == 0)
		{
			++j;
			if (ft_dup_atoi(dt, dt->info[i], j) == -1)
			{
				printf ("Error\nBad imput in colors - ");
				return (-1);
			}
		}
		else if (ft_check_line_two (dt->info[i]) == -1)
		{
			printf ("Error\nBad imput in colors - ");
			return (-1);
		}
		i++;
	}
	return (0);
}

//busco en la linea las lineas de los colores
int	ft_check_line_two(char *line)
{
	int	i;

	if (!line)
		return (-1);
	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	if ((line[i] == 'F' || line[i] == 'C') && line [i + 1] == ' ')
	{
		while (line[++i])
		{
			if (line[i] != ',' && line[i] != ' ' && !(line[i] > 47 && line[i] < 58))
				return (-1);
		}
		return (0);
	}
	return (1);
}

//funcion que genera una cadena de enteros de la linea F o C de color
int	ft_dup_atoi(t_in *dt, char *line, int n)
{
	char	**num;
	int		i;
	int		j;

	num = (char **)malloc(sizeof(char *) * 5);
	if (!num || !line)
		return (-1);
	j = -1;
	i = 0;
	while (++j < 4 && line[i])//recorro la parte de los numeros
	{
		i = ft_restore_i(line, j);
		if (i == -1)
			break;
		num[j] = ft_line (line, num, i, j);
		printf ("num%d: <%s>\n", j, num[j]);
		if (!num[j])
			return (-1);
	}
	num[j] = NULL;
	if (j != 3)//caso de que me metan mas o menos de 3 numeros
	{
		ft_free_bidim(num);
		return (-1);
	}
	ft_atoi_bid(dt, num, n);
	return (0);
}

//devuelve el valor de i en la linea para seguir copiando los numeros al array num[j] que coresponda
int	ft_restore_i(char *line, int j)
{
	int	i;

	i = ft_linehead_run(line);
	while (--j >= 0)
	{
		while (line[i] && line[i] != ',')
			i++;
		if (!line[i])
			return (-1);
		i++;
	}
	return (i);
}

//funcion que avanza hasta que empiecen los numeros y trimea  de espacios la parte de los numeros
int	ft_linehead_run (char *line)
{
	int i;

	i = 0;
	while (line[i] && line[i] == ' ')
		i++;
	i++;
	while (line[i] && line[i] == ' ')
		i++;
	if (!(line[i] > 47) && !(line[i] < 58))
		return (-1);
	line = ft_trim(line, i);
	if (!line)//si el trim da error retorno -1
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
			j = i;
			if (line[i - 1] > 47 && line[i - 1] < 58)
			{
				while (line[j] == ' ')
					j++;
				if (line[j] > 47 && line[j] < 58)
					return (NULL);
			}
			else if (line[i - 1] == ',')
			{
				while (line[j] == ' ')
					j++;
				if (line[j] == ',')
					return (NULL);
			}
			j = i - 1;
			while (line[++j])
				line[j] = line[j + 1];

		}
		if (line[i] && line[i] != ' ')
			i++;
	}
	return (line);
}

//aux de la funcion anterior que retorna la i
char	*ft_line(char *line, char **num, int i, int j)
{
	int k;

	if (!line)
		return (NULL);
	num[j] = (char *)malloc(sizeof(char) * 100);
	if (!num[j])
		return (NULL);
	k = -1;
	while(line[i] && (line[i] > 47 && line[i] < 58))
	{
		num[j][++k] = line[i];
		i++;
	}
	if (k == -1)
		return (NULL);
	num[j][++k] = 00;
	return (num[j]);
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
