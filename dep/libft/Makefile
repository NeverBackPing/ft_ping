# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sjossain <sjossain@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/03/25 12:41:17 by sjossain          #+#    #+#              #
#    Updated: 2024/04/16 15:04:51 by sjossain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################# COMPILATION ###########################

CC =  cc
CFLAGS = -Wall -Werror -Wextra

################# COMMANDS ##############################

RM = rm -rf

################# FILES #################################

PATH_LIB = ../../lib
NAME = libft.a
HEAD = libft.h

LIBC = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c\
	ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strlcat.c ft_strlcpy.c\
	ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_strnstr.c ft_toupper.c\
	ft_memcmp.c ft_tolower.c ft_atoi.c ft_calloc.c ft_strdup.c ft_strcmp.c

ADDITIONAL = ft_substr.c ft_strjoin.c ft_strtrim.c ft_itoa.c ft_strmapi.c ft_striteri.c\
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c ft_split.c

#########################################################

FILE_C = ${LIBC} ${ADDITIONAL}

SRC = src/%.c

OBJS_DIR= ../../build/obj/libft

OBJS = $(FILE_C:%.c=$(OBJS_DIR)/%.o)

$(OBJS_DIR)/%.o: $(SRC)
	@mkdir -p $(OBJS_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


#########################################################

all: $(NAME)

$(NAME): $(OBJS) $(HEAD)
	ar rcs $(PATH_LIB)/$(NAME) $(OBJS) $(HEAD)

clean:
	$(RM) $(OBJS) $(OBJS_DIR)

fclean: clean
	$(RM) $(PATH_LIB)/$(NAME)

re: fclean all

.PHONY: all clean fclean re