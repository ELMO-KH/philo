NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -g -O0 -pthread

SRCS = main.c utils.c utils01.c routine.c Hawk_eye.c ft_atoi.c

OBJS = $(SRCS:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
.SECONDARY: ${OBJS}