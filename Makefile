NAME = scop

CC = clang -Wall -Wextra -Werror
LIBS = -L./minilibix/ -lmlx -framework OPENGL -framework AppKit

SRC_DIR = srcs

SRC := $(wildcard $(SRC_DIR)/*.c)
OBJ = $(SRC:.c=.o)

%.o: %.c
		$(CC) -o $@ -fPIC -c $<

all: $(NAME)

$(NAME):$(OBJ)
		$(CC) $(LIBS) -o $@ $^
		@echo "\033[0;32m$(NAME) : Compilation successful !! \033[0;32m"

clean:
		@rm $(OBJ)

fclean: clean
		@rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
