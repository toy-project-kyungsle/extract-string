CC		= gcc
RM		= rm -f
LIBC	= ar rc
LIBR	= ranlib
NAME	= extract_string.a
SRCS	= main.c get_next_line.c get_next_line_utils.c
OBJS	= $(SRCS:.c=.o)
PROGRAM	= extract_string
RESULT	= result.txt

%.o:%.c
	$(CC) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)
	$(LIBR) $(NAME)
	$(CC) -o $(PROGRAM) $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME) $(PROGRAM) $(RESULT)

re: fclean all

.PHONY: all clean fclean re