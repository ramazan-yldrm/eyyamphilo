NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -pthread

SRC = src/core/main.c \
      src/core/parse.c \
      src/core/init.c \
      src/routine/monitor_routine.c \
	  src/routine/philo_eat.c \
      src/routine/philo_routine.c \
	  src/routine/philo_think.c \
	  src/routine/utils.c \
	  src/simulation/create_philos.c \
      src/simulation/simulation.c \
      src/utils/clean_funcs.c \
      src/utils/utils.c \

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
