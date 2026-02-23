# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: gwen <gwen@student.42.fr>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/02/11 15:53:54 by gwen              #+#    #+#              #
#    Updated: 2026/02/20 10:56:56 by gwen             ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = cc
FLAGS = -Wall -Wextra -Werror

RM = rm -rf

INC = -I includes

LIB_DIR = libft/
LIB_A = libft.a
LIB = $(LIB_DIR)$(LIB_A)

SRC_DIR = src/
SRC = main.c \
	Lexing/create_tokens.c \
	Lexing/lexing.c \
	Lexing/quote.c \
	parsing/create_cmd.c \
	parsing/parsing.c \
	parsing/parsing_utils.c \
	Interpret/append_file_process.c \
	Interpret/here_doc_process.c \
	Interpret/interpret.c \
	Interpret/pipe_process.c \
	Signal/signal.c \
	Path/path_finding.c \
	Path/path_split.c \
	Utils/utils.c \
	Utils/init.c \
	Utils/error.c \
	Utils/free.c

SRCS = $(addprefix $(SRC_DIR), $(SRC))

OBJ_DIR = obj/
OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_DIR), $(OBJ))

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	@echo "minishell compiled"
	@$(CC) $(FLAGS) $(INC) $(OBJS) -L $(LIB_DIR) -lft -lreadline -o $(NAME)

$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) -c $< -o $@ $(INC)

$(LIB):
	@echo "Making Libft..."
	@make -sC $(LIB_DIR)

clean:
	@echo "Cleaned."
	@$(RM) $(OBJ_DIR)
	@make -sC $(LIB_DIR) clean

fclean: clean
	@echo "Full cleaned."
	@$(RM) $(NAME)
	@make -sC $(LIB_DIR) fclean

re: fclean all

.PHONY: re clean fclean all
