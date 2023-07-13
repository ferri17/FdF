# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:36:01 by fbosch            #+#    #+#              #
#    Updated: 2023/07/13 12:31:01 by fbosch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[1;32m
COLOUR_RED=\033[1;31m
COLOUR_BLUE=\033[1;34m
COLOUR_YELLOW=\x1b[33;01m
COLOUR_END=\033[0m

NAME = fdf
BONUS_NAME = fdf_bonus

LIBFT = libft.a
LIBFT_DIR = libft/

SRC = main.c events.c errors.c utils.c map_load.c draw.c bresenham.c

BONUS_SRC =

SRC_DIR = src/

INCLUDE_DIR = include/
BUILD_DIR = .build/

MLX = libmlx.a
MLX_DIR = minilibx_macos/

SRC_FILES = $(addprefix $(SRC_DIR),$(SRC))
BONUS_FILES = $(addprefix $(SRC_DIR),$(BONUS_SRC))

OBJ = $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC_FILES))
BONUS_OBJ = $(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(BONUS_FILES))

DEP = $(OBJ:%.o=%.d) $(BONUS_OBJ:%.o=%.d)

CC = cc
CFLAGS = #-Wall -Wextra -Werror
DEPFLAGS = -I $(INCLUDE_DIR) -I $(MLX_DIR) -MMD -MP
MLXFLGS = -L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
DIR_DUP = mkdir -p $(@D)

EXECUTABLES = *.out *.exe

RM = /bin/rm -f

all: make_libs $(NAME)

make_libs:
	@printf "$(COLOUR_YELLOW)Compiling libft... \xE2\x8C\x9B\n$(COLOUR_END)"
	$(MAKE) -C $(LIBFT_DIR)
	@printf "$(COLOUR_YELLOW)Compiling minilibx... \xE2\x8C\x9B\n$(COLOUR_END)"
	$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT_DIR)$(LIBFT)
		@printf "$(COLOUR_GREEN)Linking... $(COLOUR_END)"
		$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) $(MLXFLGS) -o $(NAME)
		@printf "$(COLOUR_GREEN)Compilation done!\xE2\x9C\x85\n$(COLOUR_END)"

bonus: make_libs make_minilibx .bonus

.bonus: $(BONUS_OBJ) $(LIBFT_DIR)$(LIBFT)
	@printf "$(COLOUR_GREEN)Linking... $(COLOUR_END)"
	$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT_DIR)$(LIBFT) -o $(BONUS_NAME)
	@printf "$(COLOUR_GREEN)Compilation done!\xE2\x9C\x85\n$(COLOUR_END)"
	@touch .bonus

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX)
	@printf "$(COLOUR_YELLOW)Compiling... $(COLOUR_END)$(patsubst $(BUILD_DIR)%,%,$@)\n"
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

norm:
	norminette
	
clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	$(MAKE) -C $(MLX_DIR) clean
	@printf "$(COLOUR_RED)Deleting...\xE2\x9D\x97\\xE2\x9D\x97\\xE2\x9D\x97\n$(COLOUR_END)"
	$(RM) $(OBJ) $(OBJ_BONUS) $(DEP) $(EXECUTABLES)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	$(MAKE) -C $(MLX_DIR) fclean
	@printf "$(COLOUR_RED)Deleting...\xE2\x9D\x97\\xE2\x9D\x97\\xE2\x9D\x97\n$(COLOUR_END)"
	$(RM) $(NAME) $(BONUS_NAME)
	$(RM) -r $(BUILD_DIR)

re: fclean all

.PHONY: all clean fclean re bonus
	
-include $(DEP)