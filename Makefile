# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kotadashirui <kotadashirui@student.42.f    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/08/16 20:39:38 by kotadashiru       #+#    #+#              #
#    Updated: 2025/10/22 16:15:24 by kotadashiru      ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = $(wildcard *.c libft/*.c)
OBJ = $(SRC:.c=.o)

CC = cc
CFLAGS = -Wall -Wextra -Werror -I/opt/homebrew/opt/readline/include
CFLAGS += -g -O0 -fsanitize=address,undefined -fno-omit-frame-pointer
LDFLAGS += -fsanitize=address,undefined
LDFLAGS = -L/opt/homebrew/opt/readline/lib -lreadline

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
