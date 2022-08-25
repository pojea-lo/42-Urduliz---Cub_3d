#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>

typedef struct  s_in//estructura con datos iniciales
{
    char    **map;//array bidimensional con el map
    int     maxy;//cantidad de filas del mapa
    int     maxx;//cantidad de columnas del mapa
}t_in;

//main.c files
int		ft_traspas(int fd, char *map, t_in *dt);
void    ft_memset(t_in *dt);
void	ft_free(t_in *dt);

//map_utils_0.c files
//Funciones para crear la bidimensional
int     ft_create_bid (int fd, t_in *dt, char *map);
int     ft_count_fd (int fd, int n);
int     ft_check_line(char *line, int n);
int     ft_data_map(t_in *dt);

//map_utils_1.c files
//Funciones para el control del mapa
int     ft_ch_map(t_in *dt);
int     ft_ch_chars(t_in *dt);
int     ft_ch_chars_aux(int n);
int     ft_ch_personage(t_in *dt);
int     ft_ch_personage_out(int i, int j, t_in *dt);
int		ft_ch(int i, int j, t_in *dt, int n);

//map_utils_2.c files
//Funciones para encontrar espacios erroneos en el mapa
int     ft_ch_spaces(t_in *dt);
int     ft_ch_spaces_aux(int i, int j, int max, t_in *dt);
int     ft_ch_sp_aux_frow(int i, int j, int max, t_in *dt);
int     ft_ch_sp_aux_lrow(int i, int j, int max, t_in *dt);
int     ft_ch_sp_aux_irow(int i, int j, int max, t_in *dt);

//map_utils_3.c files
//Funciones para encontrar mapas abiertos
int     ft_ch_close(t_in *dt);
int     ft_ch_close_aux(int i, int j, int max, t_in *dt);
int     ft_ch_cl_aux_frow(int i, int j, int max, t_in *dt);
int     ft_ch_cl_aux_lrow(int i, int j, int max, t_in *dt);
int     ft_ch_cl_aux_irow(int i, int j, int max, t_in *dt);

//gnl.c files
char    *ft_gnl(int fd);
int     ft_check(char *str);
char    *ft_copy(char *buf, char *rest);
int     ft_strlen(char *str);
char    *ft_dup(char *oldstr);
char    *ft_update_rest(char *rest);

#endif
