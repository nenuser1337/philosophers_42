NAME=philosophers
BNAME=bonus_philo

OBJECTSDIR=philo
BOBJECTSDIR=philo_bonus

SRC=$(addprefix $(OBJECTSDIR)/, actions.c check_errors.c philosophers.c threads.c utils.c)
OBJ=$(SRC:.c=.o)

BSRC=$(addprefix $(BOBJECTSDIR)/, philo_process.c processes.c states.c utils.c)
BOBJ=$(BSRC:.c=.o)

CC=gcc
CFLAGS=-Wall -Wextra -Werror
RM=rm -f

.PHONY: all clean fclean re bonus

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)



bonus : $(BOBJ)
	$(CC) $(CFLAGS) $(BOBJ) -o $(BNAME)


clean:
	$(RM) $(OBJ) $(BOBJ)

fclean: clean
	$(RM) $(NAME) $(BNAME)

re: fclean all
