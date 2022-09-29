#include "../../include/cub3d.h"

//obtengo del descriptor la bidimensional con toda la info para poder trabajar con ella posteriormente y no tener que andar abriendo y cerrando descriptores
char	**ft_get_info(int fd, char *argv, t_in *dt)
{
	int		i;
	int		j;
	char	*line;

	i = ft_count_info (fd);
	if (i == 0) //archivo de mapa vacio. salida comprobada SL
		return (NULL);
	dt->info = (char **) malloc (sizeof(char *) * (i + 1));
	if (!dt->info)
		return (NULL);
	fd = open(argv, O_RDWR);
	line = ft_gnl(fd);
	j = -1;
	while (line)
	{
		i = 0;
		while (line[i] == ' ' && line[i])
			i++;
		if (line[i] != 00)
			dt->info[++j] = ft_dup(line);
		free (line);
		line = ft_gnl(fd);
	}
	dt->info[++j] = NULL;
	return (close(fd), dt->info);
}

//cuento las lineas que no estén vacias, sean de mapa o de datos, del archivo datos
int	ft_count_info(int fd)
{
	int		i;
	int		n;
	char	*line;

	n = 0;
	line = ft_gnl(fd);
	while (line)
	{
		i = -1;
		while (line[++i] == ' ' && line[i])
			i++;
		if (line[i] != 00)
			n++;
		free (line);
		line = ft_gnl(fd);
	}
	close(fd); //cierro el descriptor abierto en el main al ppio
	return (n);
}
