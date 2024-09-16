CC      		= cc 
CFLAGS			= -Wall -Werror -Wextra  $(HEADERS)
HEADERS			= -I./libft -I./vector -I./fdf_utils -I. -I./mlx
LIBFT_FLAGS		= -Llibft
MLX_FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
LFLAGS			= $(MLX_FLAGS) $(LIBFT_FLAGS)
RM      		= rm -rf
VECTOR_NAMES	= vec1 vec2
VECTOR_UTILS	= $(patsubst %, vector/%, $(VECTOR_NAMES))
FDF_NAMES		= map_parsing_utils utils rotate_utils shift_utils\
				colors pts_utils line events window_utils\
				collect_garbage color_utils
FDF_UTILS		= $(patsubst %, fdf_utils/%, $(FDF_NAMES))
TEST_NAMES		= test
TEST_UTILS		= $(patsubst %, test/%, $(TEST_NAMES))
FILES			= $(FDF_UTILS) $(VECTOR_UTILS) $(TEST_UTILS) state
MINILIBX		= mlx/libmlx.a
LIBFT			= libft/libft.a
NAME			= miniRT
SRC				= $(patsubst %, %.c, $(FILES))
OBJS			= $(patsubst %.c, %.o, $(SRC))

all: $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@

$(NAME): $(OBJS)  $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MINILIBX) $(LIBFT)  -o $(NAME)

minilibx: $(MINILIBX)

$(MINILIBX):
	make -C mlx

libft: $(LIBFT)

$(LIBFT):
	make -C libft

$(MINILIBX):
	make -C mlx

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

.PHONY: all clean bonus re fclean minilibx libft
