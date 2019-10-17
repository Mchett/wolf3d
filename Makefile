NAME = wolf3d
FILES = cast_ray.c cast_ray2.c controls.c controls2.c ft_init.c get_next_line.c image.c key.c main.c map_read.c map_read2.c map_valid.c menu.c xpm_read.c 


SRC = $(addprefix srcs/, $(FILES))
FILESO = $(addprefix objectives/, $(FILES:.c=.o))
FLAGS = -Wall -Wextra -Werror
LIBA = -L ./libs/libft -lft
MIN = -L ./libs/minilibx_macos -lmlx
ADD = -framework OpenGL -framework AppKit
INCL = -I ./libs/libft -I ./libs/minilibx_macos -I .

all: $(NAME)

$(NAME): $(FILESO)
	make -C ./libs/libft/
	make -C ./libs/minilibx_macos/
	gcc $(FLAGS) -o $(NAME) $(SRC) $(INCL) $(LIBA) $(MIN) $(ADD)

objectives/%.o: srcs/%.c | objectives
	gcc $(FLAGS) $(INCL) -o $@ -c $<

clean:
	rm -rf objectives/
	make clean -C ./libs/libft/
	make clean -C ./libs/minilibx_macos/

fclean: clean
	rm -f $(NAME)
	make fclean -C ./libs/libft/

objectives:
	mkdir objectives/

re: fclean all
