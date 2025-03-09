NAME = philo

SRC =	routine.c \
		utils.c \
		philo.c \
		parser.c \
		main.c

CC = gcc
FLAGS = -Wall -Wextra -Werror 
#-fsanitize=thread
RM = rm -f

OBJ_DIR = ./obj/
OBJ = $(addprefix $(OBJ_DIR), $(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) -o $(NAME) $(OBJ) -lpthread
	@echo "Compilation done"

$(OBJ_DIR)%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@$(CC) $(FLAGS) -c -o $@ $<

clean: 
	@$(RM) $(OBJ) > /dev/null 2>&1
	@$(RM) -r $(OBJ_DIR) > /dev/null 2>&1
	@echo "Clean done"

fclean: clean
	@$(RM) $(NAME) > /dev/null 2>&1
	@echo "Fclean done"

re: fclean all

.PHONY: clean all re fclean

