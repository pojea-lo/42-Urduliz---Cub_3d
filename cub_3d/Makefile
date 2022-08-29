NAME = cub

SRC = 	main.c\
		draw_utils_0.c\
		hook_utils_0.c\
		map_utils_0.c\
		map_utils_1.c\
		map_utils_2.c\
		map_utils_3.c\
		gnl.c

OBJ = $(SRC: .c=.o)  

CC = gcc
FLAGS = -Wall -Werror -Wextra
SAN = -g3 -fsanitize=address
MLX = -L mlx -lmlx -framework OpenGL -framework Appkit

RM = rm -r -f

all: $(NAME)

%.o: %.c
	$(CC) -c $< -o $@

$(NAME): $(OBJ)
	make -C mlx/
	$(CC) $(FLAGS) $^ -o $@ $(MLX) $(SAN)

clean:
	$(RM) $(OBJS)
	make clean -C mlx/

fclean: clean
	$(RM) $(NAME)
	$(RM) *.dSYM

re:	fclean all

.phony: name, all, clean, fclean, re, bonus 

