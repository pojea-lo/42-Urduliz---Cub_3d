NAME = cub3d
MINIPATH = include/mlx

SRC = 	src/main.c\
		src/draw/draw_utils_0.c\
		src/hooks/hook_utils_0.c\
		src/map_check/map_utils_0.c\
		src/map_check/map_utils_1.c\
		src/map_check/map_utils_2.c\
		src/map_check/map_utils_3.c\
		include/gnl.c

OBJ = $(SRC: .c=.o)  

CC = gcc
FLAGS = -Wall -Werror -Wextra
SAN = -g3 -fsanitize=address
MLX = -L $(MINIPATH) -lmlx -framework OpenGL -framework Appkit

RM = rm -r -f

.SILENT:

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	make -C $(MINIPATH)
	$(CC) $(FLAGS) $^ -o $@ $(MLX) $(SAN)

clean:
	$(RM) $(OBJS)
	make clean -C $(MINIPATH)
fclean: clean
	$(RM) $(NAME)
	$(RM) *.dSYM

re:	fclean all

.phony: name, all, clean, fclean, re, bonus 

