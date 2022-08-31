#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"

//estructura con datos iniciales
typedef struct  s_in
{
    char    **map;//array bidimensional con el map
	double	mapw;//anchura del mapa
	double	maph;//altura del mapa
    int     maxx;//cantidad de columnas del mapa
    int     maxy;//cantidad de filas del mapa
    int		xo;//posicion del personaje en x
    int		yo;//posicion del personaje en y
	char	dir;//guardo la dirección del personaje
	double	dirx;//direccion x del personaje
	double	diry;//direccion y del personaje
	double	fov;//angulo de vision del personaje
	double	planex;//vector plano de pantalla x
	double	planey;//vector plano de pantalla y
	double	camerax;//coordenada x en el espacio de la camara
	double	raydirx;//x del vector rayo
	double	raydiry;//y del vector rayo
	//variables del algoritmo DDA
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;//longitud del rayo
	int		stepx;//avance del rayo hacia la izq (-1) o la der (1)
	int		stepy;//avance del rayo hacia arriba (-1) o hacia a bajo (1)
	int		hit;//buleano para salir del bucle del DDA
	int		side;//si se golpeo lado x (0) o y (1)
	int		lineheight;//altura de la linea
	int		drawstart;//pixel inicial en altura
	int		drawend;//pixel final en altura

	//hasta aqui el DDA


}	t_in;

//estructura de la mlx
typedef struct	s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_mlx;

//estructura para el final con los hk
typedef struct	s_hook
{
	t_in	*dt;
	t_mlx	*gr;
}	t_hook;


//main.c files
int		ft_traspas(int fd, char *argv, t_in *dt);
t_hook	*ft_memset(t_in *dt);
void	ft_free(t_in *dt);
void	ft_free_hk(t_hook *hk);

//draw_utils_0.c files
//Funciones que dibujan el mapa
int		ft_draw_map(t_hook *hk);
int		ft_draw_line(t_hook *hk, int x);
int		ft_draw_all(t_hook *hk);

//hook_utils_0.c
int		close_button(t_hook *hk);

//raycast_utils_0.c
//Funciones para el calculo numerico del raycasting
int		ft_rayc_init(t_hook *hk);
int		ft_rayc_memset(t_hook *hk);
int		ft_rayc_memset_2(t_hook *hk);
int		ft_get_dir(t_hook *hk);
int		ft_get_plane(t_hook *hk);
void	ft_calcul_step(t_hook *hk);
void	ft_dda_algorithm(t_hook *hk);


//map_utils_0.c files
//Funciones para crear la bidimensional
int     ft_create_bid (int fd, t_in *dt, char *argv);
int     ft_count_fd (int fd, int n);
int     ft_check_line(char *line, int n);
int     ft_data_map(t_in *dt);

//map_utils_1.c files
//Funciones para el control del mapa
int     ft_ch_map(t_in *dt);
int     ft_ch_chars(t_in *dt);
int     ft_ch_chars_aux(int i, int j, int n, t_in *dt);
char    **ft_add_columns(t_in *dt);
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
int     ft_ch_cl_aux_irow(int i, int j, int max, t_in *dt);

//gnl.c files
char    *ft_gnl(int fd);
int     ft_check(char *str);
char    *ft_copy(char *buf, char *rest);
int     ft_strlen(char *str);
char    *ft_dup(char *oldstr);
char    *ft_update_rest(char *rest);

#endif
