NAME = philo
CC = cc -Wall -Wextra -Werror
SOURCE = main.c mutex_things.c time.c start_philo.c utils.c

OBJ = $(SOURCE:.c=.o)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
all: $(NAME)

c: clean
clean:
	@rm -rf *.o

f: fclean
fclean: clean
	@rm -rf $(NAME)

re: fclean all

.PHONY: re fclean clean all f c