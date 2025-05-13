# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yukravch <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 09:39:53 by yukravch          #+#    #+#              #
#    Updated: 2025/05/13 11:22:31 by yukravch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra -lreadline -lhistory -g3 -I $(INC_DIR)

all: $(NAME)
	@echo "                      "
	@echo "✨✨✨✨✨✨✨✨✨✨✨"
	@echo "✨                  ✨"
	@echo "✨    ./\___/\.     ✨"
	@echo "✨                  ✨"
	@echo "✨    ( >^ -^<)     ✨"
	@echo "✨                  ✨"
	@echo "✨    / ⊃ 🌸/       ✨"
	@echo "✨                  ✨"
	@echo "✨✨✨✨✨✨✨✨✨✨✨"

SRC_DIR = sources
OBJ_DIR = objects
INC_DIR = includes

FILES = minishell.c
SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(OBJ)
	cc $(CFLAGS) $(OBJ) -o $(NAME)


clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
re: fclean all
