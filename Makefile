CC 		=	gcc
CFLAGS	=	#-Wall -Wextra -Werror -g -fsanitize=address
debug	=	-g -fsanitize=address
NAME	=	cub
SRCS	=	./src/main.c \
			./src/init.c \
			./src/parsing.c \
			./src/raycast.c \
			./src/mlx_utils.c \
			./src/math.c \
			./src/raycasting.c \
			


OBJS	= $(SRCS:.c=.o)

LIBS	=	-framework OpenGL -framework AppKit
MLXDIR	=	./mlx/
MLXLIB	=	libmlx.a
GNL_A	=	get_next_line/get_next_line.a
LIBFT_A	=	Libft/libft.a

all: LIBFT GNL cub

submodule:
	@git submodule init 
	@git submodule update

%.o : %.c
# @echo "$(B_BLUE)Compiling: $(BLUE)$(notdir $<) 🔨$(NC)"
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[0;35m•\033[0m\c"

banner:
# @echo "\n${PURPLE}======== Cub3d ========$(NC)"

mlx:
# @echo "\n${BLUE}======== MLX ========${NC}"
# @$(MAKE) -C $(MLXDIR)

LIBFT:
	@$(MAKE) -C Libft

GNL:
	@$(MAKE) -C get_next_line

$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(debug) $(OBJS) $(GNL_A) $(LIBFT_A) $(MLXDIR)$(MLXLIB) $(FSAN) $(LIBS) -o $(NAME)

clean:
	@rm -f $(OBJS)
#	@$(MAKE) -C Libft clean
#	@$(MAKE) -C get_next_line clean

fclean: clean
	@rm -f $(NAME)
#	@$(MAKE) -C Libft fclean
#	@$(MAKE) -C get_next_line fclean

re: fclean all

run: all
	./$(NAME) maps/valid_map.cub