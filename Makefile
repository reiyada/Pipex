# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ryada <ryada@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/02/13 12:12:41 by ryada             #+#    #+#              #
#    Updated: 2025/02/19 13:22:59 by ryada            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Executable Name
NAME = pipex

# Compiler and Flags
CC = gcc
CFLAGS = -Werror -Wall -Wextra -fsanitize=address -no-pie

# Remove Command
RM = rm -rf

# Directories
SRC_DIR = srcs
BONUS_DIR = srcs_bonus
LIBFT_DIR = libft
GNL_DIR = gnl
INCLUDES = -Iincludes

# Source Files (Mandatory)
SRCS = $(SRC_DIR)/pipex.c \
       $(SRC_DIR)/utils.c

# Source Files (Bonus)
SRCS_BONUS = $(BONUS_DIR)/pipex_bonus.c \
             $(BONUS_DIR)/utils_bonus.c \
			 $(GNL_DIR)/get_next_line.c \
			 $(GNL_DIR)/get_next_line_utils.c \

# Object Files (Mandatory)
OBJS = $(SRCS:.c=.o)

# Object Files (Bonus)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

# Libft
LIBFT = $(LIBFT_DIR)/libft.a

# Default Rule - Compile Pipex (Mandatory with Clean First)
all: clean $(LIBFT) $(NAME)

# Compile Pipex (Mandatory)
$(NAME): $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_DIR) -lft
	@echo "✅ Pipex (Mandatory) compiled successfully!"

# Compile Object Files (Mandatory)
$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile Object Files (Bonus)
$(BONUS_DIR)/%.o: $(BONUS_DIR)/%.c
	@$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

# Compile Pipex Bonus
bonus: fclean $(LIBFT) $(OBJS_BONUS) 
	@$(CC) $(CFLAGS) $(OBJS_BONUS) -o $(NAME) -L$(LIBFT_DIR) -lft
	@echo "🚀 Pipex (Bonus) compiled successfully!"

# Compile Libft
$(LIBFT):
	@make -C $(LIBFT_DIR) --silent

# Clean Object Files
clean:
	@$(RM) $(OBJS) $(OBJS_BONUS)
	@make clean -C $(LIBFT_DIR) --silent
	@echo "🧹 Cleaned object files!"

# Full Clean (Remove Everything)
fclean: clean
	@$(RM) $(NAME)
	@make fclean -C $(LIBFT_DIR) --silent
	@echo "🗑️  Removed all compiled files!"

# Recompile Everything
re: fclean all

# Phony Rules
.PHONY: all clean fclean re bonus
