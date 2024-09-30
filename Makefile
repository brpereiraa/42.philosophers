# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bruno <bruno@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/29 17:27:17 by marvin            #+#    #+#              #
#    Updated: 2024/09/30 10:16:03 by bruno            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

CFLAGS = -Wall -Wextra -Werror

# CFLAGS += -fsanitize=thread
# CFLAGS += -fsanitize=address

SRC =  ./actions.c ./main.c ./utils.c ./checker.c ./init.c ./exit.c
OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME) 

re: fclean all

clean: 
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

.SILENT:

.PHONY: all re clean fclean