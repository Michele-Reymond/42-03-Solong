SRCS = so_long.c
CFLAGS = -Wall -Werror -Wextra -Imlx
MLXFLAGS = -Lmlx -lmlx -framework OpenGL -framework AppKit
CC = gcc
NAME = so_long
OBJS = ${SRCS:.c=.o}
AR = ar rc
RM = rm -f

all: ${NAME}

$(NAME):	$(OBJS)
			$(CC) $(SRCS) $(CFLAGS) $(MLXFLAGS) -o $(NAME)

%o:			%.c
			$(CC) $(CFLAGS) -Imlx -c $< -o $@

run:		all
			./$(NAME)

clean: 
	${RM} ${OBJS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re