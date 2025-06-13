# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yukravch <yukravch@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 09:39:53 by yukravch          #+#    #+#              #
#    Updated: 2025/06/13 18:24:04 by yukravch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra $(INC_DIR) -g3
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
INC_DIR = -I includes -I libft42/includes

FILES = 	main.c	env/copy_env.c \
			free_handler.c \
			lexer/lexer_main.c lexer/lexer_err_handler.c \
			parser/parser_main.c parser/parsing_a.c parser/parsing_b.c \
			parser/parsing_utils.c parser/parser_err_handler.c \
			expander/expander_main.c \
			execution/execution.c \
			execution/utils.c execution/init.c \
			execution/parent_process.c execution/exit.c\
			execution/cmd_exit.c execution/export.c\
			execution/unset.c \
			execution/simple_cmd.c execution/get_abs_path.c \
			execution/redirections.c \
			execution/built_in.c execution/built_in_utils.c \
			execution/built_in_1.c execution/built_in_utils_1.c
		 
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
