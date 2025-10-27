CC = cc 
CFLAG = -Wall -Wextra -Werror 
H = philosophers.h
NAME = philo 
SRC = dinner/dishes2.c dinner/dishes.c dinner/sit_around.c \
		dinner/handlers.c tools/tools3.c dinner/watching.c main_thread.c \
		tools/tools.c tools/tools2.c dinner/init.c tools/parsing.c
OBJ = $(SRC:.c=.o)
PHILOSOPHERS_BANNER = "\
	   ___  __   _ __                   __              \n\
  / _ \/ /  (_) /__  ___ ___  ___  / /  ___ _______ \n\
 / ___/ _ \/ / / _ \(_-</ _ \/ _ \/ _ \/ -_) __(_-< \n\
/_/  /_//_/_/_/\___/___/\___/ .__/_//_/\__/_/ /___/ \n\
                           /_/ 					  \033[32mMANDATORY\033[0m\n"

all: $(NAME)
	@clear
	@echo $(PHILOSOPHERS_BANNER)
	@echo "\033[32mPhilosophers Program is ready...\033[0m"

$(NAME): $(OBJ)
	$(CC) $(OBJ) $(CFLAG) -o $(NAME)

%.o: %.c $(H)
	$(CC) $(CFLAG) -c  $< -o $@

clean:
	@rm -rf $(OBJ)
	@echo "\033[32mPhilosophers Objects Cleaned...\033[0m"
fclean: clean
		@rm -rf $(NAME)
		@echo "\033[32mAll removed...\033[0m"
re:	fclean all
