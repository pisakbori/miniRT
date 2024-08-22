CC				= cc 
CFLAGS			= -Wall -Werror -Wextra -I./mlx -I./libft
LIBFT_FLAGS		= -Llibft
MLX_FLAGS		=  -framework AppKit
CFLAGS			= -Wall -Werror -Wextra -I./ -I./libft -I./mlx_linux -lXext -lX11 -lm -lz
# CFLAGS_LINUX			= -Wall -Werror -Wextra -I./mlx -I./libft -I./mlx_linux
LIBFT_FLAGS		= -Llibft
MLX_FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_LINUX_FLAGS	= -Lmlx_linux $(MINILIBX_LINUX) -Imlx_linux 
MINILIBX_LINUX	= mlx_linux/libmlx.a
LFLAGS			= $(MLX_LINUX_FLAGS) $(LIBFT_FLAGS)
LFLAGS			= $(MLX_FLAGS) $(LIBFT_FLAGS)
RM				= rm -rf
SRC				= fdf.c map_parsing_utils.c utils.c rotate_utils.c shift_utils.c\
				colors.c pts_utils.c line.c events.c window_utils.c\
				collect_garbage.c color_utils.c
OBJS			= $(patsubst %.c, ./src/%.o, $(SRC))
MINILIBX		= mlx/libmlx.a
LIBFT			= libft/libft.a
NAME			= fdf	

all: $(NAME)

bonus: $(NAME)

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(MINILIBX) $(LIBFT)


all_tests: $(NAME)
	./fdf ./test_maps/100-6.fdf 
	./fdf ./test_maps/42.fdf 
	./fdf ./test_maps/basictest.fdf 
	./fdf ./test_maps/elem-fract.fdf 
	./fdf ./test_maps/elem2.fdf 
	./fdf ./test_maps/mars.fdf 
	./fdf ./test_maps/plat.fdf 
	./fdf ./test_maps/pylone.fdf 
	./fdf ./test_maps/pyramide.fdf 
	./fdf ./test_maps/t2.fdf 
	./fdf ./test_maps/10-70.fdf 
	./fdf ./test_maps/20-60.fdf 
	./fdf ./test_maps/50-4.fdf 
	./fdf ./test_maps/elem-col.fdf 
	./fdf ./test_maps/elem.fdf 
	./fdf ./test_maps/julia.fdf 
	./fdf ./test_maps/pentenegpos.fdf 
	./fdf ./test_maps/pnp_flat.fdf 
	./fdf ./test_maps/pyra.fdf
	./fdf ./test_maps/t1.fdf

no_color : $(NAME)
	./fdf ./test_maps/42.fdf
	./fdf ./test_maps/basictest.fdf

plat : $(NAME)
	./fdf ./test_maps/plat.fdf

minilibx: $(MINILIBX)

libft: $(LIBFT)

$(LIBFT):
	make -C libft

$(MINILIBX):
	@make -C mlx

clean:
	make clean -C mlx
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make clean -C mlx
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(MINILIBX)

re: fclean all

.PHONY: all clean bonus re fclean color no_color
