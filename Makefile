NAME	= cub3D
CC	  = clang
CFLAGS  = -Ofast -march=native -Wall -Wextra -Werror -MMD
MLX	 = -lXext -lX11 -lm #-lmlx 

DIR_SRC = src
DIR_OBJ = obj

SRC	 = 	main.c	parse.c utils.c init_map.c check_map.c free.c utils2.c
OBJ	 = $(SRC:%.c=$(DIR_OBJ)/%.o)
DEP	 = $(SRC:%.c=$(DIR_OBJ)/%.d)

all: $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(MLX) -o $(NAME)

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)
	
clean:
	rm -rf $(DIR_OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test: all
	./cub3D maps/map1.cub

-include $(DEP)

.PHONY: all clean fclean re