NAME = philo

SRC =	utils.c \
		philo.c \
		parser.c \
		main.c

CC = gcc
FLAGS = -Wall -Wextra -Werror -fsanitize=thread
RM = rm -f
OBJ = $(SRC:.c=.o)
# INCLUDE = -I include/

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -lpthread
	@echo "Compilation done"

%.o: %.c
	@$(CC) $(FLAGS) -c -o $@ $<

clean: 
	@$(RM) $(OBJ) > /dev/null 2>&1
	@echo "Clean done"

fclean: clean
	@$(RM) $(NAME) > /dev/null 2>&1
	@echo "Fclean done"

re: fclean all

.PHONY: clean all re fclean

