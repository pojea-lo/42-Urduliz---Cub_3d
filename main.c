#include "cub3d.h"

int main(int argc, char* argv[])
{
    int fd;

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
    if (ft_traspas(fd, argv[1]) == -1)
        return (-1);
    close(fd);
    return (0);
}

int ft_traspas(int fd, char *map)//funcion inicial que empieza a analizar el mapa
{
    t_in    dt;//inicio estructura de datos inicial

    ft_memset(&dt);
    if (ft_create_bid(fd, &dt, map) == -1)
        return (-1);
    if (ft_check_map(&dt) == -1)
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