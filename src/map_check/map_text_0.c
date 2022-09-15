#include "../../include/cub3d.h"

int	ft_create_text(t_hook *hk)
{
	int	i;
	int	fd;

	if (ft_count_tex(hk->dt->info) == -1)
	{
		printf ("Error\nError in number of valid textures - ");
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
			printf ("Error\nTexture file does not exist - ");
			return (-1);
		}
		close (fd);
		hk->dt->texture[i] = ft_charge_tex(hk, i);
	}
	if (ft_count_col(hk->dt->info) != 2)
	{
		printf ("Error\nError in number of valid colors - ");
		return (-1);
	}
	if (ft_create_text_col(hk->dt) == -1)
		return (-1);
	return (0);
}

//cuento las lineas de texturas y que sean solo una de cada
int	ft_count_tex(char **info)
{
	int		i;
	int		j;
	int		n[4];

	i = -1;
	while (++i < 4)
		n[i] = 0;
	i = -1;
	while (info[++i])
	{
		if (ft_check_line (info[i], 1) == 0)
		{
			j = ft_count_tex_aux(info[i]);
			if (j == -1)
				return (-1);
			else
				n[j] += 1;
		}
	}
	i = -1;
	while (++i < 4)
	{
		if (n[i] != 1)
			return (-1);
	}
	return (0);
}

int	ft_count_tex_aux(char *info)
{
	int	j;

	j = 0;
	while (info[j] == ' ')
		j++;
	if (info[j] == 'N')
		return (0);
	else if (info[j] == 'S')
		return (1);
	else if (info[j] == 'E')
		return (2);
	else if (info[j] == 'W')
		return (3);
	return (-1);
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

