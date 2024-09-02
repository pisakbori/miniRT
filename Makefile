CC      		= cc 
CFLAGS			= -Wall -Werror -Wextra  $(HEADERS) -lXext -lX11 -lm -lz
HEADERS			= -I./libft -I./vector -I./fdf_utils -I. -I./mlx_linux
# CFLAGS			= -Wall -Werror -Wextra -I./mlx -I./libft -I./mlx_linux
LIBFT_FLAGS		= -Llibft
MLX_FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_LINUX_FLAGS	= -Lmlx_linux $(MINILIBX_LINUX) -Imlx_linux 
LFLAGS			= $(MLX_LINUX_FLAGS) $(LIBFT_FLAGS)
# LFLAGS			= $(MLX_FLAGS) $(LIBFT_FLAGS)
RM      		= rm -rf
VECTOR_NAMES	= vec1 vec2
VECTOR_UTILS	= $(patsubst %, vector/%, $(VECTOR_NAMES))
FDF_NAMES		= colors utils
FDF_UTILS		= $(patsubst %, fdf_utils/%, $(FDF_NAMES))
TEST_NAMES		= test
TEST_UTILS		= $(patsubst %, test/%, $(TEST_NAMES))
FILES			= $(FDF_UTILS) $(VECTOR_UTILS) $(TEST_UTILS) state collect_garbage sphere camera plane
MINILIBX		= mlx/libmlx.a
MINILIBX_LINUX	= mlx_linux/libmlx.a
LIBFT			= libft/libft.a
NAME			= miniRT
SRC				= $(patsubst %, %.c, $(FILES))
OBJS			= $(patsubst %.c, %.o, $(SRC))

# all: $(NAME)

all: linux

%.o: %.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@

linux: $(OBJS)  $(MINILIBX_LINUX) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MINILIBX_LINUX) $(LIBFT)  -lXext -lX11 -lm -lz -o $(NAME)

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) -o $(NAME) $(OBJS) $(MINILIBX) $(LIBFT)

minilibx: $(MINILIBX)

$(MINILIBX_LINUX):
	make -C mlx_linux

libft: $(LIBFT)

$(LIBFT):
	make -C libft

$(MINILIBX):
	make -C mlx

clean:
	make clean -C mlx
	make clean -C mlx_linux
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make clean -C mlx
	make clean -C mlx_linux
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(MINILIBX)
	rm -rf $(MINILIBX_LINUX)

re: fclean all

.PHONY: all clean bonus re fclean minilibx mlx_linux libft
