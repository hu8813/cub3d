NAME	= cub3D
CC	  = clang
CFLAGS  = -Wall -Wextra -Werror -MMD -Ofast -march=native #last 2 are optimization flags
MLX	 = -lmlx -lXext -lX11 -lm
LIBFT		= libft/libft.a

DIR_SRC = src
DIR_OBJ = .obj

SRC	 = 	utils.c utils2.c  positions.c main.c map_check2.c \
		render.c map_check.c  map_read.c map_parse.c put_img.c

OBJ	 = $(SRC:%.c=$(DIR_OBJ)/%.o)
DEP	 = $(SRC:%.c=$(DIR_OBJ)/%.d)

all: $(NAME)

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.c | $(DIR_OBJ)
	$(CC) $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(OBJ) $(MLX) $(LIBFT) -o $(NAME)
	@echo "Usage:\nmake test  OR  ./cub3D maps/map1.cub"

$(LIBFT):
	@make -C libft/

$(DIR_OBJ):
	mkdir -p $(DIR_OBJ)
	
clean:
	rm -rf $(DIR_OBJ)
	@make clean -C libft/

fclean: clean
	rm -rf $(NAME)
	@make fclean -C libft/

re: fclean all

test: all
	./cub3D maps/map_kaya_ehab.cub

-include $(DEP)

.PHONY: all clean fclean re