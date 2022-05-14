NAME				=	cube3d

SRC_INPUT_MANAGMENT	=	src/prep/initialize_struct.c\
						src/engine/game_start.c\
						#src/input_management.c

SRC_TESTING			=	testing/draw_line.c
						

MAIN_SRC = src/main.c

LIB = libft.a

LIB_PATH = Libft

GNL = get_next_line.a

GNL_PATH = get_next_line

#FLAGS = -Wall -Werror -Wextra

SPECIAL_FLAG = -Iincludes -g -Lmlx -lmlx -framework OpenGL -framework AppKit

all: $(NAME)

%.o: %.c
	$(CC) -Imlx -c $< -o $@

$(NAME): $(LIB) $(GNL)
	@gcc $(FLAGS) $(MAIN_SRC) $(SRC_TESTING) $(SRC_INPUT_MANAGMENT) $(LIB_PATH)/$(LIB) $(GNL_PATH)/$(GNL) $(SPECIAL_FLAG) -o $(NAME)
	@echo "\033[92mCUBE3D successfully compiled!\033[0m"


$(GNL):
	@$(MAKE) 50 -C $(GNL_PATH)

$(LIB):
	@$(MAKE) -C $(LIB_PATH)

clean:
	@$(MAKE) clean -C $(LIB_PATH)
	@$(MAKE) clean -C $(GNL_PATH)

	
fclean:
	@$(MAKE) fclean -C $(LIB_PATH)
	@$(MAKE) fclean -C $(GNL_PATH)
	@rm -f $(NAME) $(LIB_PATH)/$(LIB)
	@echo "\033[91mCUBE3D successfully cleaned!\033[91m"

re: fclean all

# test:$(LIB_PATH)/$(LIB)
# 	gcc $(FLAGS) $(SRC_TESTING) $(SRC_INPUT_MANAGMENT) $(LIB_PATH)/$(LIB)  $(SPECIAL_FLAG) -o $(NAME)
