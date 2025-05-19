# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yukravch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/20 17:48:22 by yukravch          #+#    #+#              #
#    Updated: 2025/04/25 16:30:48 by yukravch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
CC = cc

all: $(NAME) 

SRC_DIR = sources
FILES  = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c \
			ft_memset.c ft_bzero.c ft_memcpy.c ft_memmove.c ft_strcpy.c ft_strlcpy.c ft_strlcat.c \
			ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
			ft_memcmp.c ft_strstr.c ft_strnstr.c ft_atoi.c ft_atol.c ft_calloc.c ft_strdup.c ft_substr.c \
			ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c \
			ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_lstnew.c ft_lstadd_front.c ft_lstsize.c ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_print_list.c  ft_print_bits.c \
			\
                        ft_printf.c ft_print_hexa_printf.c ft_putchar_printf.c ft_putnbr_printf.c \
                        ft_putstr_printf.c \
                        \
                        get_next_line.c get_next_line_utils.c \

SRC = $(addprefix $(SRC_DIR)/, $(FILES))
INC = includes/
OBJ_DIR = objects

OBJECTS = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
CFLAGS = -Wall -Wextra -Werror -I $(INC)

$(NAME): $(OBJ_DIR) $(OBJECTS)
	ar rcs $(NAME) $(OBJECTS)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) -c $(CFLAGS) -o $@ $<

clean:
	rm -rf $(OBJ_DIR)
fclean: clean
	rm -f $(NAME)

re: fclean all
