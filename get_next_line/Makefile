# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cerdelen <cerdelen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/22 17:13:17 by Cerdelen          #+#    #+#              #
#    Updated: 2022/05/12 19:30:21 by cerdelen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wextra -Wall -Werror

AR = ar rcs

NAME = get_next_line.a

SRCS = 	get_next_line.c get_next_line_utils.c

OBJS = $(SRCS:.c=.o)

all: 
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=42 -c $(SRCS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[92mGNL successfully compiled!\033[0m"

10:
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=10 -c $(SRCS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[92mGNL successfully compiled!\033[0m"

25:
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=25 -c $(SRCS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[92mGNL successfully compiled!\033[0m"

50:
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=50 -c $(SRCS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[92mGNL successfully compiled!\033[0m"

100:
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=100 -c $(SRCS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[92mGNL successfully compiled!\033[0m"

250:
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=150 -c $(SRCS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[92mGNL successfully compiled!\033[0m"

500:
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=200 -c $(SRCS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[92mGNL successfully compiled!\033[0m"

1000:
	@$(CC) $(CFLAGS) -D BUFFER_SIZE=200 -c $(SRCS)
	@$(AR) $(NAME) $(OBJS)
	@echo "\033[92mGNL successfully compiled!\033[0m"

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re: fclean all
