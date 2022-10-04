NAME = cub3d
MINIPATH = include/mlx/.
MINIPATH2 = ../include/mlx/.

SRC = 	include/gnl.c\
	 	include/gnl_aux.c\
		src/main.c\
		src/map_check/map_bidimensional.c\
		src/map_check/map_ch_close.c\
		src/map_check/map_ch_spaces.c\
		src/map_check/map_check.c\
		src/map_check/map_color_0.c\
		src/map_check/map_color_1.c\
		src/map_check/map_color_2.c\
		src/map_check/map_info.c\
		src/map_check/map_text_0.c\
		src/map_check/map_text_1.c\
		src/map_check/map_utils.c\
		src/memory/free_0.c\
		src/memory/free_1.c\
		src/memory/memset.c\
		src/raycasting/raycasting.c\
		src/raycasting/print.c\
		src/draw/draw_utils_0.c\
		src/hooks/hook_utils_0.c\
		src/hooks/hooks.c \
		src/draw/draw.c

SRC_BONUS = include/gnl.c\
	 	include/gnl_aux.c\
		src/main.c\
		src/map_check/map_bidimensional.c\
		src/map_check/map_ch_close.c\
		src/map_check/map_ch_spaces.c\
		src/map_check/map_check.c\
		src/map_check/map_color_0.c\
		src/map_check/map_color_1.c\
		src/map_check/map_color_2.c\
		src/map_check/map_info.c\
		src/map_check/map_text_0.c\
		src/map_check/map_text_1.c\
		src/map_check/map_utils.c\
		src/memory/free_0.c\
		src/memory/free_1.c\
		src/memory/memset.c\
		src/raycasting/print.c\
		src/draw/draw_utils_0.c\
		src_bonus/raycasting_bonus.c\
		src_bonus/hook_utils_bonus.c\
		src_bonus/hook_bonus.c\
		src_bonus/draw_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o) 

CC = gcc
FLAGS = -Wall -Werror -Wextra -g
SAN = -fsanitize=address
MLX = -L $(MINIPATH) -lmlx -framework OpenGL -framework Appkit -I include/cub3d.h
BONUS_NAME = cub3d_bonus
RM = rm -r -f

all: $(NAME)
bonus: $(BONUS_NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(BONUS_NAME) : $(OBJ_BONUS)
	make -C $(MINIPATH)
	$(CC) $(FLAGS) $^ -o $@ $(MLX) $(SAN)

$(NAME): $(OBJ)
	make -C $(MINIPATH)
	$(CC) $(FLAGS) $^ -o $@ $(MLX) $(SAN)

clean:
	$(RM) $(OBJ) $(OBJ_BONUS)
	make clean -C $(MINIPATH)

fclean: clean
	$(RM) $(NAME)
	$(RM) cub3d_bonus
	$(RM) *.dSYM

re:	fclean all
rebonus: fclean bonus
.phony: name, all, clean, fclean, re, bonus, rebonus

