NAME = so_long

CFLAGS = -O3 -Wall -Wextra -Werror

MLX = ./minilibx_opengl

LXFLAGS = -l mlx -framework OpenGL -framework AppKit 

HEADER = so_long.h \
	get_next_line.h

CC = gcc

SRCS =	get_next_line.c \
	so_long.c \
	check.c \
	draw.c \
	pars.c \
	texter.c \
	tools.c \
	tools2.c \
	tools3.c

FIL = $(addprefix ./srcs/, $(SRCS))

OBJ = $(SRCS:.c=.o)


all: $(NAME)

$(NAME): $(FIL)
	$(CC)   -L $(MLX) $(LXFLAGS) $(FIL) -o $(NAME) -g

run:
	./$(NAME) map/map.ber


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
	norminette $(FIL) $(HEADER)

leaks:
	leaks $(NAME) > leak