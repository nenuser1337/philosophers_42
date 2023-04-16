NAME = philo
BONUS_NAME = philo_bonus
SRCS_DIR = philo
BONUS_SRCS_DIR = philo_bonus
SRCS = $(addprefix $(SRCS_DIR)/, actions.c   check_errors.c  philosophers.c threads.c      utils.c)
OBJS = $(SRCS:.c=.o)
BONUS_SRCS = $(addprefix $(BONUS_SRCS_DIR)/,  philo_process.c processes.c   states.c    utils.c)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)
CC = gcc
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

bonus: $(BONUS_OBJS)
	$(CC) $(CFLAGS) $(BONUS_OBJS) -o $(BONUS_NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	$(RM) $(OBJS) $(BONUS_OBJS)

fclean: clean
	$(RM) $(NAME) $(BONUS_NAME)

re: fclean all
