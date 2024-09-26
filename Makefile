NAME = philo

SRC = main.c utils.c init.c monitoring.c exit.c
OBJS = ${SRC:.c=.o}

CFLAGS = -g -Wall -Wextra -Werror -I include
# CFLAGS += -fsanitize=thread
CFLAGS += -fsanitize=address

%.o: %.c
		cc ${CFLAGS} -c $< -o $@

${NAME}: ${OBJS}
			ar rcs philo.a ${OBJS}
			cc ${CFLAGS} philo.a -o ${NAME}

all: ${NAME}		

clean:
		rm -f ${OBJS}

fclean: clean
		rm -f philo.a philo

re: fclean all

valgrind: re
	@valgrind -s --leak-check=full --show-leak-kinds=all ./philo ${ARGS}

.SILENT:
