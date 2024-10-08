CC      		= cc
CFLAGS			= -Wall -Werror -Wextra $(INC)
HEADERS			= -I./libft -I./vector -I./fdf_utils -I. -I./mlx
LIBFT_FLAGS		= -Llibft
MLX_FLAGS		= -Lmlx -lmlx -framework OpenGL -framework AppKit
LFLAGS			= $(MLX_FLAGS) $(LIBFT_FLAGS)
RM      		= rm -rf
WIN_WIDTH		= 1024
FILES			=	test/debug_print1\
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
					vector/vec3\
					colors\
					parse/parse\
					parse/parse2\
					parse/parse3\
					translate\
					rotate\
					mlx_utils
MINILIBX		= mlx/libmlx.a
LIBFT			= libft/libft.a
NAME			= miniRT
SRC_PATH		= ./src/
SRC				= $(patsubst %, $(SRC_PATH)%.c, $(FILES))
OBJ_PATH 		= ./obj/
BONUS_OBJ_PATH 	= ./bonus-obj/
OBJS			= $(patsubst %, $(OBJ_PATH)%.o, $(FILES))
BONUS_OBJS		= $(patsubst %, $(BONUS_OBJ_PATH)%.o, $(FILES))
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
	
# Objects directory rule
$(BONUS_OBJ_PATH):
	mkdir -p $(BONUS_OBJ_PATH)
	mkdir -p $(BONUS_OBJ_PATH)test
	mkdir -p $(BONUS_OBJ_PATH)shapes
	mkdir -p $(BONUS_OBJ_PATH)vector
	mkdir -p $(BONUS_OBJ_PATH)parse

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS)  -O3 -c $< -o $@ -D WIN_WIDTH=$(WIN_WIDTH) -D BONUS=0

$(BONUS_OBJ_PATH)%.o: $(SRC_PATH)%.c
	$(CC) $(CFLAGS) -O3 -c $< -o $@ -D WIN_WIDTH=$(WIN_WIDTH) -D BONUS=1

$(NAME): $(OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(OBJS) $(MINILIBX) $(LIBFT) -o $(NAME)

bonus: $(BONUS_OBJ_PATH) $(BONUS_OBJS) $(MINILIBX) $(LIBFT)
	$(CC) $(CFLAGS) $(LFLAGS) $(BONUS_OBJS) $(MINILIBX) $(LIBFT) -o $(NAME)

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
	rm -rf $(BONUS_OBJ_PATH)

fclean: clean
	make clean -C mlx
	make fclean -C libft
	rm -rf $(NAME)
	rm -rf $(MINILIBX)

re: fclean all

.PHONY: all clean bonus re fclean minilibx libft
