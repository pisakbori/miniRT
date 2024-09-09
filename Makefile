CC      		= cc 
CFLAGS			= -Wall -Werror -Wextra  $(INC) -lXext -lX11 -lm -lz
# CFLAGS			= -Wall -Werror -Wextra -I./mlx -I./libft -I./mlx_linux
LIBFT_FLAGS		= -Llibft
MLX_FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
MLX_LINUX_FLAGS	= -Lmlx_linux $(MINILIBX_LINUX) -Imlx_linux 
LFLAGS			= $(MLX_LINUX_FLAGS) $(LIBFT_FLAGS)
# LFLAGS			= $(MLX_FLAGS) $(LIBFT_FLAGS)
RM				= rm -rf
TEST_NAMES		= test/3planes test/has_cylinder test/shared test/debug
FILES			= $(TEST_NAMES)\
					state\
					collect_garbage\
					camera\
					shapes/sphere\
					shapes/plane\
					shapes/cylinder\
					shapes/utils\
					trace\
					light_source\
					main\
					vector/vec1\
					vector/vec2\
					colors
MINILIBX		= mlx/libmlx.a
MINILIBX_LINUX	= mlx_linux/libmlx.a
LIBFT			= libft/libft.a
NAME			= miniRT
SRC_PATH		= ./src/
SRC				= $(patsubst %, $(SRC_PATH)%.c, $(FILES))
OBJ_PATH 		= ./obj/
OBJS			= $(patsubst %, $(OBJ_PATH)%.o, $(FILES))
INC				=	-I ./includes/\
					-I ./libft/\
					-I ./mlx_linux/

# all: $(NAME)

all: $(OBJ_PATH) linux 

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)test
	mkdir -p $(OBJ_PATH)shapes
	mkdir -p $(OBJ_PATH)vector

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS)  -O3 -c $< -o $@

linux: $(OBJS)  $(MINILIBX_LINUX) $(LIBFT) 
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MINILIBX_LINUX) $(LIBFT)  -lXext -lX11 -lm -lz -o $(NAME) && ./miniRT

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
