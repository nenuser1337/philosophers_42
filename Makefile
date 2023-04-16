NAME=philosophers

FILES = philosophers threads check_errors utils actions

OBJ=$(FILES:=.o)


all: $(NAME)

$(NAME): $(OBJ)
	gcc -Wall -Wextra -Werror $(OBJ) -o  $(NAME)
		

clean: 
	rm -rf $(OBJ) $(NAME)
fclean: clean

re :fclean all