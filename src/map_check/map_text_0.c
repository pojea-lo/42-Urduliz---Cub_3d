#include "../../include/cub3d.h"

int	ft_create_text(t_in *dt, char *argv)
{
	if (ft_count_tex(argv) != 4)
	{
		printf ("Error in number of textures - ");
		return (-1);
	}
	if (ft_create_text_tex(dt, argv) == -1)
		return (-1);
	if (ft_count_col(argv) != 2)
	{
		printf ("Error in number of colors - ");
		return (-1);
	}
	if (ft_create_text_col(dt, argv) == -1)
		return (-1);
	return (0);
}

//creo la bidimensional de int de los colores
int	ft_create_text_col(t_in *dt, char *argv)
{
	int		i;
	int		fd;
	char	*line;

	fd = open (argv, O_RDWR);
	dt->color = (int **)malloc(sizeof(int *) * 2);
	dt->color[0] = (int *)malloc(sizeof(int) * 3);
	dt->color[1] = (int *)malloc(sizeof(int) * 3);
	if (!dt->color)
		return (-1);
	line = ft_gnl(fd);
	i = 0;
	while (line)
	{
		if (ft_check_line_two (line) == 0 && line)
		{
			if (ft_dup_atoi(dt, line, i) == 1)
			{
				printf ("Bad imput of colors - ");
				return (-1);
			}
			i++;
		}
		free(line);
		line = ft_gnl(fd);
	}
	close(fd);
//	printf ("Numeros 0: %d / %d / %d\n", dt->color[0][0], dt->color[0][1], dt->color[0][2]);
//	printf ("Numeros 1: %d / %d / %d\n", dt->color[1][0], dt->color[1][1], dt->color[1][2]);
	return (0);
}

//funcion que devuelve una cadena de enteros de la linea F o C de color
int	ft_dup_atoi(t_in *dt, char *line, int n)
{
	char	**num;
	int		i;
	int		j;
	int		k;

	num = (char **)malloc(sizeof(char *) * 10);
	if (!num || !line)
		return (1);
	i = 0;
	j = -1;
	while (line[i])
	{
		if (!(line[i] > 47 && line[i] < 58) && line[i] != 44)
		{
			if (line[i] != 'F' && line[i] != 'C' && line[i] != ' ')
				return (1);
		}
		else if (line[i] > 47 && line[i] < 58)
		{
			num[++j] = (char *)malloc(sizeof(char) * 50);
			if (!num[j])
				return (1);
			k = -1;
			while(line[i] && line[i] > 47 && line[i] < 58)
			{
				num[j][++k] = line[i];
				i++;
			}
			num[j][++k] = 00;
			if (line[i] != ',' && line[i] != 00)
				return (1);
		}
		if(line[i])
			i++;
	}
	num[++j] = NULL;
	ft_atoi_bid(dt, num, n);
	return (0);
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
		if (k > 3)//comprobacion por si me meten mas de 3 numeros
			return (1);
		dt->color[n][i] = 0;
		k = -1;
		while (num[i][++k])
			dt->color[n][i] = (num[i][k] - '0') + (dt->color[n][i] * 10);
		if (dt->color[n][i] > 255)
			return (1);
	}
	return (0);
}

//creo la bidimensional de las texturas
int ft_create_text_tex(t_in *dt, char *argv)
{
	int		j;
	int		fd;
	char	*line;

	fd = open (argv, O_RDWR);
	dt->tex = (char **)malloc(sizeof(char *) * 5);
	if (!dt->tex)
		return (-1);
	line = ft_gnl(fd);
	j = -1;
	while (line)
	{
		if (ft_check_line (line, 1) == 0 && line)
		{
			dt->tex[++j] = ft_dup(line);
			dt->tex[j] = ft_regen_tex(dt->tex[j]);
		}
		free(line);
		if (dt->tex[j] == NULL)
		{
			printf ("Bad imput of textures - ");
			return (-1);
		}
		line = ft_gnl(fd);
	}
	close(fd);
	dt->tex[++j] = NULL;
	return (0);
}

//funcion que purga la bidimensional text quedandose solo con la ruta
char	*ft_regen_tex(char *old)
{
	char	*new;
	int		i;
	int		j;

	if (!old)
		return (NULL);
	i = 0;
	j = ft_strlen(old);
	while (old[i] && (old[i] == 'N' || old[i] == 'S' || old[i] == 'E' || old[i] == 'W' || old[i] == 'O' || old[i] == 'A' || old[i] == ' '))
		i++;
	new = (char *)malloc(sizeof(char) * (j - i + 1));
	if (!new)
		return (NULL);
	j = 0;
	while (old[i])
	{
		if (old[i] != ' ')
			new[j] = old[i];
		else
			return (NULL);
		i++;
		j++;
	}
	new[j] = 00;
	free(old);
	return (new);
}

//cuento las lineas de texturas
int	ft_count_tex(char *argv)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(argv, O_RDWR);
	line = ft_gnl(fd);
	while (line)
	{
		if (ft_check_line (line, 1) == 0 && line)
			i++;
		free(line);
		line = ft_gnl(fd);
	}
	close(fd);
	return (i);
}

//cuento las lineas de color
int	ft_count_col(char *argv)
{
	int		fd;
	int		i;
	char	*line;

	i = 0;
	fd = open(argv, O_RDWR);
	line = ft_gnl(fd);
	while (line)
	{
		if (ft_check_line_two (line) == 0 && line)
			i++;
		free(line);
		line = ft_gnl(fd);
	}
	close(fd);
	return (i);
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
