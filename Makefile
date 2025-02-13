# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryada <ryada@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 12:12:41 by ryada             #+#    #+#              #
#    Updated: 2025/02/13 12:27:47 by ryada            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Compiler
CC = cc
CFLAGS = -Wall -Wextra -Werror

# Executable name
NAME = pipex

# Directories
SRC_DIR = srcs
LIBFT_DIR = libft
INCLUDES = -Iincludes

# Source files (inside srcs/)
SRC = $(SRC_DIR)/pipex.c $(SRC_DIR)/utils.c
OBJ = $(SRC:.c=.o)

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Commands
RM = rm -f

# Default rule - Compile Pipex
all: $(LIBFT) $(NAME)

# Compile Libft
$(LIBFT):
	make -C $(LIBFT_DIR)

# Compile Pipex
$(NAME): $(OBJ) $(LIBFT)
	$(CC) $(CFLAGS) $(INCLUDES) -o $(NAME) $(OBJ) -L$(LIBFT_DIR) -lft

# Compile .o files (ensure srcs/ is used)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Clean object files
clean:
	$(RM) $(OBJ)
	make -C $(LIBFT_DIR) clean

# Remove executable and object files
fclean: clean
	$(RM) $(NAME)
	make -C $(LIBFT_DIR) fclean

# Recompile everything
re: fclean all

# Phony rules
.PHONY: all clean fclean re
