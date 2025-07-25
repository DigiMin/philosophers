CC = cc
CFLAGS = -Wall -Wextra -Werror -g -pthread
NAME = philo
SRC_DIR = ./philo/src/
OBJ_DIR = ./philo/obj/
BIN_DIR = ./philo/bin/
INC_DIR = ./philo/inc/
OBJ = $(patsubst %.c, %.o, $(SRC))
INC = philo.h
SRC = \
	helpers.c \
	philo_act.c \
	philo_init.c \
	philo.c \
	print.c \
	table_destroy.c \
	table_init.c \
	time.c \
	waitress_act.c


.PHONY: all re clean fclean bonus $(NAME)

all: $(BIN_DIR)$(NAME)

$(OBJ_DIR)%.o : $(addprefix $(SRC_DIR), %.c)
	@if [ ! -d $(OBJ_DIR) ]; then mkdir $(OBJ_DIR); fi
	@$(CC) $(CFLAGS) -o $@ -c $<

$(BIN_DIR)$(NAME): $(addprefix $(OBJ_DIR), $(OBJ)) $(INC_DIR)$(INC)
	@if [ ! -d $(BIN_DIR) ]; then mkdir $(BIN_DIR); fi
	@$(CC) $(CFLAGS) -o $(BIN_DIR)$(NAME) $(addprefix $(OBJ_DIR), $(OBJ)) -I $(INC_DIR)$(INC)

re: fclean all
	@echo "MAKING RE"

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -rf $(BIN_DIR)