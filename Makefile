NAME = cub3d
MINIPATH = include/mlx

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

SRC_BONUS = 	include/gnl.c\
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
		src_bonus/raycasting_bonus.c\
		src/raycasting/print.c\
		src/draw/draw_utils_0.c\
		src_bonus/hook_utils_bonus.c\
		src_bonus/hooks_bonus.c \
		src_bonus/draw_bonus.c

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o) 

CC = gcc
FLAGS = -Wall -Werror -Wextra
SAN = -g3 -fsanitize=address
MLX = -L $(MINIPATH) -lmlx -framework OpenGL -framework Appkit -I include/cub3d.h

RM = rm -r -f

all: $(NAME)

bonus: $(OBJ_BONUS) 
	make -C $(MINIPATH)
	$(CC) $(FLAGS) $^ -o $@ $(MLX) $(SAN)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(MINIPATH)
	$(CC) $(FLAGS) $^ -o $@ $(MLX) $(SAN)



clean:
	$(RM) $(OBJ)
	make clean -C $(MINIPATH)

fclean: clean
	$(RM) $(NAME)
	$(RM) *.dSYM

re:	fclean all

.phony: name, all, clean, fclean, re, bonus 

