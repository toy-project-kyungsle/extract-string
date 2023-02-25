CC		= gcc
RM		= rm -f
LIBC	= ar rc
LIBR	= ranlib
NAME	= libftprintf.a
SRCS	= get_next_line.c get_next_line_utils.c
OBJS	= $(SRCS:.c=.o)

%.o:%.c
	$(CC) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)
	$(LIBR) $(NAME)

all: $(NAME)

clean:
	$(RM) ${OBJS}

fclean: clean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re