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

#programme
NAME= ft_ping

# command compile
CC=cc
CFLAGS=-Wall -Wextra -Werror -g3 -O1

# dependence
LIBFT= incl/dep/libft/libft.a 
INCLUDES = -Iincl -Iincl/dep/libft

# code soure

OBJS_DIR= obj

FILE_C = main.c

SRC= src/main.c

OBJ = $(FILE_C:%.c=$(OBJS_DIR)/%.o)

$(OBJS_DIR)/%.o: $(SRC)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

all: $(LIBFT) $(NAME) header

$(LIBFT):
	@$(MAKE) -C ./incl/dep/libft/

header:
	@echo "$(BLUE)$$HEADER$(RESET)"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME)

show:
	@printf "NAME  		:$(NAME)\n"
	@printf "CC		:$(CC)\n"
	@printf "CFLAGS		:$(CFLAGS)\n"
	@printf "SRC		:$(SRC)\n"
	@printf "OBJ		:$(OBJ)\n"

clean:
	rm -rf $(OBJ) $(OBJS_DIR) incl/dep/libft/obj/*.o incl/dep/libft/obj

fclean: clean
	rm -rf $(NAME) $(LIBFT)

re: fclean all

.PHONY: all show clean fclean header re