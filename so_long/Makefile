NAME = so_long

CFLAGS = -O3 -Wall -Wextra -Werror

MLX = ./minilibx_opengl

LXFLAGS = -l mlx -framework OpenGL -framework AppKit 

HEADER = so_long.h \
	get_next_line.h

CC = gcc

SRCS =	get_next_line.c \
	get_next_line_utils.c \
	so_long.c

FIL = $(addprefix ./, $(SRCS))

OBJ = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(FIL)
	$(CC)   -L $(MLX) $(LXFLAGS) $(FIL) -o $(NAME) 

run:
	./$(NAME) map.cub

save:
	./$(NAME) map.cub --save

clean:
	@rm -rf $(OBJ)
	@rm -f bitmap.bmp

fclean: clean
	rm -f $(NAME)

re: fclean all

me:
	@echo $(NAME)
	@echo "#    #  ####   ####  #####   #    #  ####   ####  #####  "
	@echo "##   # #    # #    # #    #  ##   # #    # #    # #    # "
	@echo "# #  # #    # #    # #####   # #  # #    # #    # #####  "
	@echo "#  # # #    # #    # #    #  #  # # #    # #    # #    # "
	@echo "#   ## #    # #    # #    #  #   ## #    # #    # #    # "
	@echo "#    #  ####   ####  #####   #    #  ####   ####  #####  "

norm:
	norminette $(FIL) $(addprefix ./inc/, $(HEADER))

leaks:
	leaks $(NAME) > leak