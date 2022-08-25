#include "cub3d.h"

int main(int argc, char* argv[])
{
    int 	fd;
    t_in    dt;//inicio estructura de datos inicial

    if (argc != 2)
    {
        printf("Error in arguments\n");
        return (0);
    }
    fd = open(argv[1], O_RDWR);
    if (fd == -1)
    {
        perror("Open error\n");
        return (0);
    }
    ft_traspas(fd, argv[1], &dt);
    close(fd);
	ft_free(&dt);
//	system("leaks cub");
    return (0);
}

//funcion inicial que empieza a analizar el mapa
int ft_traspas(int fd, char *map, t_in *dt)
{
    ft_memset(dt);
    if (ft_create_bid(fd, dt, map) == -1)
        return (-1);
    if (ft_ch_map(dt) == -1)
    {
        printf ("Map error\n");
        return (-1);
    }
    return (0);
}

void    ft_memset(t_in *dt)//resetea los valores iniciales
{
    dt->map = NULL;
}

void	ft_free(t_in *dt)
{
	int	i;

	if (dt->map)
	{
		i = -1;
		while (dt->map[++i])
			free (dt->map[i]);
		free (dt->map);
	}
}

