NAME = philo

CC = cc

CFLAGS = -Wall -Wextra -Werror -pthread -I$(LIBFT_DIR)

SRCS = philo.c routine.c utils.c

OBJS = $(SRCS:.c=.o)

LIBFT_DIR = Libft

LIBFT = $(LIBFT_DIR)/libft.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT) -o $(NAME)

$(LIBFT):
	$(MAKE) -C $(LIBFT_DIR)

clean:
	rm -f $(OBJS)
	$(MAKE) clean -C $(LIBFT_DIR)

fclean: clean
	rm -f $(NAME)
	$(MAKE) fclean -C $(LIBFT_DIR)

re:fclean all

.PHONY: all clean fclean re
