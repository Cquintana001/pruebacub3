
NAME = libgnl.a

MANDATORY_SRC := $(shell find . \( -name '*.c' -a -not -name '*bonus.c' \))
MANDATORY_OBJ = $(MANDATORY_SRC:.c=.o)

BONUS_SRC := $(shell find . \( -name '*bonus.c' \))
BONUS_OBJ = $(BONUS_SRC:.c=.o)

CFLAGS = -Wall -Wextra -Werror
CC = gcc

BUFFER_SIZE = 1024

./%.o: ./%.c
	$(CC) -c $(FLAGS) -D BUFFER_SIZE=${BUFFER_SIZE} -o $@ $^

all: $(NAME)

$(NAME): $(MANDATORY_OBJ)

re: fclean $(NAME)

clean:
	rm -f *.o

fclean: clean
	rm -f $(NAME)

norminette:
	norminette -R CheckForbiddenSourceHeader | grep Error

bonus: $(BONUS_OBJ)
	ar rcs $(NAME) $(BONUS_OBJ)

testme:
	rm -f $(BONUS_OBJ)
	rm -f $(NAME)
	gcc -g $(BONUS_SRC)

.PHONY: all clean fclean re bonus

