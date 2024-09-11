CC      		= cc
CFLAGS			= -Wall -Werror -Wextra $(INC)
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
FILES			= $(FDF_UTILS) $(VECTOR_UTILS) $(TEST_UTILS)
FILES			=	test/3planes\
					test/has_cylinder\
					test/shared1\
					test/shared2\
					test/debug_print1\
					test/debug_print2\
					state\
					collect_garbage\
					camera\
					shapes/sphere\
					shapes/plane\
					shapes/cylinder1\
					shapes/cylinder2\
					shapes/utils\
					trace\
					ray_utils\
					light_source\
					main\
					vector/vec1\
					vector/vec2\
					colors\
					parse/parse\
					parse/parse2
MINILIBX		= mlx/libmlx.a
LIBFT			= libft/libft.a
NAME			= miniRT
SRC_PATH		= ./src/
SRC				= $(patsubst %, $(SRC_PATH)%.c, $(FILES))
OBJ_PATH 		= ./obj/
OBJS			= $(patsubst %, $(OBJ_PATH)%.o, $(FILES))
INC				=	-I ./includes/\
					-I ./libft/\
					-I ./mlx/

all: $(OBJ_PATH) $(NAME) 

# Objects directory rule
$(OBJ_PATH):
	mkdir -p $(OBJ_PATH)
	mkdir -p $(OBJ_PATH)test
	mkdir -p $(OBJ_PATH)shapes
	mkdir -p $(OBJ_PATH)vector
	mkdir -p $(OBJ_PATH)parse

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS)  -O3 -c $< -o $@

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MINILIBX) $(LIBFT) -o $(NAME)

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
	rm -rf $(OBJ_PATH)

fclean: clean
	make clean -C mlx
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(MINILIBX)

re: fclean all

.PHONY: all clean bonus re fclean minilibx libft
