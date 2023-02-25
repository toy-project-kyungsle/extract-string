CC		= gcc
RM		= rm -f
LIBC	= ar rc
LIBR	= ranlib
NAME	= get_next_line.a
SRCS	= main.c
OBJS	= $(SRCS:.c=.o)
GNL		= get_next_line.a
PROGRAM = extract_string.exe
RFILE	= extract_string_result/result.txt

%.o:%.c
	$(CC) -c $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	$(LIBC) $(NAME) $(OBJS)
	$(LIBR) $(NAME)
	$(CC) -o $(PROGRAM) $(NAME)

all: $(NAME)

clean:
	$(RM) $(OBJS) $(RFILE)

fclean: clean
	$(RM) $(PROGRAM) $(RFILE)

re: fclean all

.PHONY: all clean fclean re