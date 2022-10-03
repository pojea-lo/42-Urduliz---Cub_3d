/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsmith < jsmith@student.42urduliz.com >    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/30 10:41:57 by pojea-lo          #+#    #+#             */
/*   Updated: 2022/10/03 10:58:36 by jsmith           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <math.h>
# include "mlx/mlx.h"
# include <stdbool.h>

# define WIN_HEIGHT 600
# define WIN_WIDTH 1000

typedef struct s_mlx
{
	void	*mlx;
	void	*mlx_win;
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
	int		w;
	int		h;
	void	*hud;
	void	*gn;
	void	*fired;
	void	*bullet;
	void	*face;
	int		mouse_x;
	int		mouse_y;
	int		bullet_nbr;
}	t_mlx;

typedef struct s_in
{
	int		i;
	char	**info;
	char	**map;
	char	**tex;
	int		**color;
	double	mapw;
	double	maph;
	int		maxx;
	int		maxy;
	double	xo;
	double	yo;
	char	dir;
	double	dirx;
	double	diry;
	double	fov;
	double	planex;
	double	planey;
	double	camerax;
	double	raydirx;
	double	raydiry;
	double	movespeed;
	double	rotspeed;
	bool	rotation_right;
	bool	rotation_left;
	bool	up;
	bool	down;
	bool	left;
	bool	right;
	int		mapx;
	int		mapy;
	double	sidedistx;
	double	sidedisty;
	double	deltadistx;
	double	deltadisty;
	double	perpwalldist;
	int		stepx;
	int		stepy;
	int		hit;
	int		side;
	int		lineheight;
	int		drawstart;
	int		drawend;
	t_mlx	texture[4];
	double	texwidth;
	double	texheight;
	int		texnum;
	double	wallx;
	int		texx;
	int		texy;
	double	step;
	double	texpos;
	int		colo;	

}	t_in;

typedef struct s_hook
{
	t_in	*dt;
	t_mlx	*gr;
}	t_hook;

//Bonus
void			init_hook_threads(t_hook *hk);
int				unset(int keycode, t_hook *hk);
int				set(int keycode, t_hook *hk);
int				game_engine(t_hook *hk);
int				manage_movements(t_hook *hk);
void			manage_rotation(t_hook *hk);
void			manage_x_axys(t_hook *hk);
void			manage_y_axys(t_hook *hk);
int				mouse(int x, int y, t_hook *hk);
int				click(int key, int x, int y, t_hook *hk);
void			load_bullets(t_hook *hk);
void			load_hud_images(t_hook *hk);

//main.c files
int				ft_ch_arg(char *argv);
int				ft_traspas(int fd, char *argv, t_in *dt);

//draw_utils_0.c files
int				ft_draw_map(t_hook *hk);
int				ft_draw_line(t_hook *hk, int x);
int				ft_draw_all(t_hook *hk);
void			my_mlx_pixel_put(t_hook *hk, int x, int y, int color);
unsigned int	get_mlx_pixel_color(t_mlx *img, int x, int y);

//free_0.c files
void			ft_free_structur(t_hook *hk);
void			ft_free(t_in *dt);
void			ft_free_aux(t_in *dt);
void			ft_free_hk(t_hook *hk);
void			ft_free_hk_aux(t_hook *hk);

//free_1.c files
void			ft_free_bidim(char **str);

//hook_utils_0.c
int				close_button(t_hook *hk);
int				manage_key_hook_options(int keycode, t_hook *hk);
int				manage_mouse_hook_options(t_hook *hk);
//int			mouse(int x, int y,t_hook *hk);

//map_info.c files
char			**ft_get_info(int fd, char *argv, t_in *dt);
int				ft_count_info(int fd);

//map_bidimensional.c files
int				ft_create_bid(t_in *dt);
int				ft_ch_line_first(char **info);
int				ft_count_fd(char **info, int n);
int				ft_check_line(char *line, int n);
int				ft_data_map(t_in *dt);

//map_check.c files
int				ft_ch_map(t_in *dt);
int				ft_ch_chars(t_in *dt);
int				ft_ch_chars_aux(t_in *dt, int n);
int				ft_ch_personage(t_in *dt);
int				ft_ch_personage_aux(int i, int j, t_in *dt);

//map_utils_0.c files
int				ft_ch(int i, int j, t_in *dt, int n);
char			**ft_add_columns(t_in *dt);

//map_ch_spaces.c files
int				ft_ch_spaces(t_in *dt);
int				ft_ch_spaces_aux(int i, int j, int max, t_in *dt);
int				ft_ch_sp_aux_frow(int i, int j, int max, t_in *dt);
int				ft_ch_sp_aux_lrow(int i, int j, int max, t_in *dt);
int				ft_ch_sp_aux_irow(int i, int j, int max, t_in *dt);

//map_ch_close.c files
int				ft_ch_close(t_in *dt);
int				ft_ch_close_aux(int i, int j, int max, t_in *dt);
int				ft_ch_cl_aux_irow(int i, int j, int max, t_in *dt);

//map_text_0.c files
int				ft_create_text(t_hook *hk);
int				ft_count_tex(char **info);
int				ft_count_tex_aux(char *info);
int				ft_count_tex_aux_bi(int *n);
int				ft_create_text_tex(t_in *dt);
char			*ft_regen_tex(char *old);
char			*ft_regen_tex_aux(char *old, char *new, int i);
int				ft_ch_extension(char *new);
t_mlx			ft_charge_tex(t_hook *hk, int i);

//map_color_0.c files
int				ft_create_color(t_hook *hk);
int				ft_count_col(char **info);
int				ft_count_col_aux(char *info);
int				ft_create_text_col(t_in *dt);
int				ft_ch_line_two(char *line);
int				ft_dup_atoi(t_in *dt, char *line, int n);
int				ft_restore_i(char *line, int j);
char			*ft_trim(char *line, int i);
int				ft_trim_aux(char *line, int i);
char			*ft_line(char *line, char **num, int i, int j);
int				ft_atoi_bid(t_in *dt, char **num, int n);

//memset.c files
t_hook			*ft_memset(t_in *dt);
int				ft_rayc_memset(t_hook *hk);
int				ft_rayc_memset_2(t_hook *hk);

//print.c
int				ft_draw_texture(t_hook *hk, int x);
int				ft_cal_texnum(t_hook *hk);
void			ft_print_tex(t_hook *hk, int x);
int				ft_color_converter(t_in *dt, int i);
int				ft_ch_sky(t_in *dt);

//raycast.c
int				ft_rayc_init(t_hook *hk);
int				ft_get_dir(t_hook *hk);
int				ft_get_plane(t_hook *hk);
void			ft_calcul_step(t_hook *hk);
void			ft_dda_algorithm(t_hook *hk);

//gnl.c files
char			*ft_gnl(int fd);
int				ft_check(char *str);
char			*ft_copy(char *buf, char *rest);
int				ft_strlen(char *str);
char			*ft_dup(char *oldstr);
char			*ft_update_rest(char *rest);

#endif
