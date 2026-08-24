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

# Path and target
PATH_LIB = lib
BUILD_DIR= build
SRC= src/%.c

# dependence
LIBFT= $(PATH_LIB)/libft.a 
INCLUDES = -Iinclude -Idep/libft

# File projet
FILE_C = main.c ping.c manage.c dns.c 

# Build
OBJS_DIR= $(BUILD_DIR)/obj

OBJ = $(FILE_C:%.c=$(OBJS_DIR)/%.o)

$(OBJS_DIR)/%.o: $(SRC)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@



# compilation rules
all: $(LIBFT) $(NAME) header

$(LIBFT):
	@mkdir -p $(PATH_LIB)
	@$(MAKE) -C dep/libft/

header:
	@printf "$(BLUE)$$HEADER$(RESET)"

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INCLUDES) $(OBJ) $(LIBFT) -o $(NAME) -lm

show:
	@printf "NAME  		:$(NAME)\n"
	@printf "CC		:$(CC)\n"
	@printf "CFLAGS		:$(CFLAGS)\n"
	@printf "SRC		:$(SRC)\n"
	@printf "OBJ		:$(OBJ)\n"

clean_not_all:
	rm -rf $(OBJ)

clean:
	rm -rf $(OBJ) $(OBJS_DIR) $(BUILD_DIR)

fclean: clean
	rm -rf $(NAME) $(LIBFT) $(PATH_LIB)

re: fclean all

.PHONY: all show clean_not_all clean fclean header re