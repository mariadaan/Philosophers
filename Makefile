NAME =			philo
VPATH =			./src/ ./obj/
SRCS = 			philo.c \
				check_input.c \
				ft_atoi.c \
				ft_itoa.c \
				ft_strcmp.c

OBJS			= $(SRCS:.c=.o)
OBJ_DIR			= ./obj/
INCL_DIR		= ./includes/
CFLAGS			= -Wall -Wextra -I${INCL_DIR}
CC				= gcc

all:	$(NAME)

$(NAME): $(OBJS)
	mkdir -p $(OBJ_DIR)
	mv *.o $(OBJ_DIR)
	${CC} ${CFLAGS} -o ${NAME} $(addprefix $(OBJ_DIR), $(OBJS))

clean:
	make clean -C libft
	rm -f $(addprefix $(OBJ_DIR), $(OBJS))

fclean:	clean
	rm -f $(NAME) $(LIBFT)
	rm -rf $(OBJ_DIR)

debug:	all
	./philo 3 200 400 150 3

re:	fclean $(NAME)

.PHONY: all clean fclean re
