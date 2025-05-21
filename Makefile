# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfournie <lfournie@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/05/13 09:39:53 by yukravch          #+#    #+#              #
#    Updated: 2025/05/21 14:10:18 by lfournie         ###   ########.fr        #
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

FILES = main.c lexer/lexing_a.c lexer/lexer_err_handler.c lexer/lexing_b.c execution/execution_Y.c execution/exit_msg.c
SRC = $(addprefix $(SRC_DIR)/, $(FILES))
OBJ = $(addprefix $(OBJ_DIR)/, $(FILES:.c=.o))
O_DIRS = $(sort $(dir $(OBJ)))

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	cc $(CFLAGS) -c $< -o $@

$(NAME): $(O_DIRS) $(OBJ)
	cc $(CFLAGS) -lreadline -lhistory $(OBJ) $(LIBFT) -o $(NAME)

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
