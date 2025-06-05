# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 09:39:53 by yukravch          #+#    #+#              #
#    Updated: 2025/06/05 20:23:37 by yukravch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra -I $(INC_DIR) -g3
LIBFT = libft42/libft.a

all: $(LIBFT) $(NAME)
	@echo "                      "
	@echo "✨✨✨✨✨✨✨✨✨✨✨🔥​🔥​🔥​🔥​🔥​🔥​🔥​🔥​🔥​🔥​🔥​"
	@echo "✨                  ✨🔥​                  🔥​"
	@echo "✨    ./\___/\.     ✨🔥​                  🔥​"
	@echo "✨                  ✨🔥​      /      \    🔥​"
	@echo "✨    ( >^ -^<)     ✨🔥​     | 👁️   ​👁️ |    🔥​"
	@echo "✨                  ✨🔥​      \  👄​  /    🔥​"
	@echo "✨    / ⊃ 🌸/       ✨🔥​   🤘​         👍​  🔥​"
	@echo "✨                  ✨🔥​                  🔥​"
	@echo "✨✨✨✨✨✨✨✨✨✨✨🔥​🔥​🔥​🔥​🔥​🔥​🔥​🔥​🔥​🔥​🔥​"

SRC_DIR = sources
OBJ_DIR = objects
INC_DIR = includes

FILES = 	main.c	env/copy_env.c \
			free_handler.c \
			lexer/lexing_a.c lexer/lexing_b.c lexer/lexer_err_handler.c \
			parser/parsing_main.c parser/parsing_a.c parser/parsing_b.c \
			parser/parsing_utils.c parser/parser_err_handler.c \
			execution/execution.c \
			execution/utils.c execution/init.c \
			execution/exit.c \
			execution/env.c
			#execution/exit_msg.c \
			execution/built_in_1.c \
			execution/child_process.c \
		 
SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
O_DIRS = $(sort $(dir $(OBJ)))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(O_DIRS) $(OBJ)
	cc $(CFLAGS) $(OBJ) $(LIBFT) -lreadline -lhistory -o $(NAME)

$(O_DIRS):
	mkdir -p $@

$(LIBFT):
	make -C libft42

clean:
	make fclean -C libft42
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -rf $(NAME)
re: fclean all
