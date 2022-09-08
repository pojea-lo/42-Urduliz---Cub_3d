#include "../../include/cub3d.h"

int	ft_create_text(t_hook *hk)
{
	int	i;
	int	fd;

	if (ft_count_tex(hk->dt->info) != 4)
	{
		printf ("Error\nError in number of textures - ");
		return (-1);
	}
	if (ft_create_text_tex(hk->dt) == -1)
		return (-1);
	i = -1;
	while (hk->dt->tex[++i])
	{
		fd = open(hk->dt->tex[i], O_RDONLY);//compruebo si existe el archivo
		if (fd == -1)
		{
			printf ("No existe archivo - ");
			return (-1);
		}
		close (fd);
		hk->dt->texture[i] = ft_charge_tex(hk, i);
	}
	if (ft_count_col(hk->dt->info) != 2)
	{
		printf ("Error\nError in number of colors - ");
		return (-1);
	}
	if (ft_create_text_col(hk->dt) == -1)
		return (-1);
	return (0);
}

//cuento las lineas de texturas
int	ft_count_tex(char **info)
{
	int		i;
	int		n;

	i = 0;
	n = 0;
	while (info[i])
	{
		if (ft_check_line (info[i], 1) == 0)
			n++;
		i++;
	}
	return (n);
}

//creo la bidimensional de las texturas
int ft_create_text_tex(t_in *dt)
{
	int		i;
	int		j;

	dt->tex = (char **)malloc(sizeof(char *) * 5);
	if (!dt->tex)
		return (-1);
	i = -1;
	j = -1;
	while (dt->info[++i])
	{
		if (ft_check_line (dt->info[i], 1) == 0)
		{
			dt->tex[++j] = ft_dup(dt->info[i]);
			dt->tex[j] = ft_regen_tex(dt->tex[j]);
//			printf ("Textura %d: <%s>\n", j, dt->tex[j]);
		}
		if (dt->tex[j] == NULL)
		{
			printf ("Error\nBad imput in textures - ");
			return (-1);
		}
	}
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
	while (old[i] && (old[i] == 'N' || old[i] == 'S' || old[i] == 'E' || old[i] == 'W' || old[i] == 'O' || old[i] == 'A' || old[i] == ' ' || old[i] == '.' || old[i] == '/'))
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
		{
			while(old[i] && old[i] == ' ')
				i++;
			if (old[i] != 00)
				return (NULL);
		}
		if (old[i])
		{
			i++;
			j++;
		}
	}
	if (j == 0)//por si alguna linea no tiene textura
		return (NULL);
	new[j] = 00;
	free(old);
	return (new);
}

//cargo las imagenes de las texturas
t_mlx	ft_charge_tex(t_hook *hk, int i)
{
	t_mlx	img;

	img.img = mlx_xpm_file_to_image(hk->gr->mlx, hk->dt->tex[i], &img.w, &img.h);
	img.line_length = 0;
	img.bits_per_pixel = 0;
	img.endian = 0;
	img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.line_length, &img.endian);
	return (img);
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

	dt->color = (int **)malloc(sizeof(int *) * 2);
	dt->color[0] = (int *)malloc(sizeof(int) * 3);
	dt->color[1] = (int *)malloc(sizeof(int) * 3);
	if (!dt->color)
		return (-1);
	i = 0;
	while (dt->info[i])
	{
		if (ft_check_line_two (dt->info[i]) == 0)
		{
			if (ft_dup_atoi(dt, dt->info[i], i) == 1)
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
			if (line[i] != ',' && line[i] != 00 && line[i] != ' ')
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
		free(num[i]);
	}
	free(num);
	return (0);
}
