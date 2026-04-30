NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror -Iinc -pthread

SRC = src/core/main.c \
      src/core/parse.c \
      src/core/init.c \
      src/core/simulation.c \
      src/core/routine.c \
      src/core/monitor.c\
      src/utils/utils.c \
      src/utils/clean_table.c

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
