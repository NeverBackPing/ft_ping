# ascii art
BLUE	=	\033[0;34m
GREEN	=	\033[0;32m
RED		=	\033[31m
RESET	=	\033[0m
YELLOW	=	\033[0;33m

define HEADER
████████╗ ██████╗██████╗   ██╗██╗██████╗ 
╚══██╔══╝██╔════╝██╔══██╗ ██╔╝██║██╔══██╗
   ██║   ██║     ██████╔╝██╔╝ ██║██████╔╝
   ██║   ██║     ██╔═══╝██╔╝  ██║██╔═══╝ 
   ██║   ╚██████╗██║   ██╔╝   ██║██║     
   ╚═╝    ╚═════╝╚═╝   ╚═╝    ╚═╝╚═╝
© sjossain - ft_ping 
endef
export HEADER

# command compile
CC=cc
CFLAGS=-Wall -Wextra -Werror -g3 -O1

# dependence

# code soure
SRC= src/main.c

OBJ = $(SRC:.c=.o)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

TARGET: ft_ping

all: $(TARGET) header
	@$(MAKE) -C ./incl/dep/libft/

header:
	@echo "$(BLUE)$$HEADER$(RESET)"

$(TARGET): $(OBJ)
	$(CC) $(CFLAGS)  $(OBJ) -o $(NAME)

.PHONY: all clean fclean re

clean:
	rm -f $(OBJ) $(LIBFT_OBJ)

fclean: clean
	rm -f $(TARGET)

re: fclean all

