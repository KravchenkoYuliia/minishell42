# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 09:39:53 by yukravch          #+#    #+#              #
#    Updated: 2025/07/24 15:39:03 by yukravch         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
CFLAGS = -Wall -Werror -Wextra $(INC_DIR) -g3
LIBFT = libft42/libft.a

all: $(LIBFT) $(NAME)
	mkdir -p ../temp
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

FILES = 	main.c	input_and_init.c \
			env/copy_env.c env/env_for_execve.c \
			free_handler_a.c  free_handler_b.c signals.c \
			lexer/lexer_main.c lexer/lexer_err_handler.c \
			parser/parser_main.c parser/parsing_a.c parser/parsing_b.c \
			parser/parsing_utils.c parser/parser_err_handler.c \
			expander/expander_main.c expander/expander_utils.c \
			expander/expander_split.c \
			execution/execution.c \
			execution/utils.c execution/init.c execution/init_utils.c \
		       	execution/fill_struct.c execution/fill_struct_utils.c \
			execution/parent_process.c execution/heredoc.c execution/heredoc_utils.c\
			execution/redirection_list.c \
			execution/echo.c execution/cd.c execution/pwd.c \
			execution/export.c execution/export_utils.c execution/export_utils_utils.c \
			execution/unset.c execution/env.c \
			execution/cmd_exit.c \
			execution/simple_cmd.c execution/built_in.c execution/child_loop.c \
			execution/exit_status.c \
			execution/get_abs_path.c \
			execution/redirections.c \
			execution/quotes.c execution/expand.c \
			execution/errors.c 
		

		 
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
