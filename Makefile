# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbosch <fbosch@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:36:01 by fbosch            #+#    #+#              #
#    Updated: 2023/08/10 13:20:26 by fbosch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[1;32m
RED=\033[1;31m
BLUE=\033[1;34m
YELLOW=\x1b[33;01m
END=\033[0m
CL_LINE=\033[K

NAME			=	fdf

LIBFT			=	libft.a
LIBFT_DIR		=	libft/

FILE_MAKE		=	Makefile

SRC				=	main.c events.c events_utils.c utils.c map_load.c draw.c \
					bresenham.c map_load_utils.c draw_utils.c menu.c matrix.c \
					events_utils_2.c  cube.c rotation_sphere.c \
					cohen_sutherland.c \

SRC_DIR			=	src/

INCLUDE_DIR		=	include/
BUILD_DIR		=	.build/

MLX				=	libmlx.a
MLX_DIR			=	minilibx_macos/

SRC_FILES		=	$(addprefix $(SRC_DIR),$(SRC))

OBJ				=	$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC_FILES))

DEP				=	$(OBJ:%.o=%.d) $(BONUS_OBJ:%.o=%.d)

CC				=	cc
CFLAGS			=	-Wall -Wextra -Werror
DEPFLAGS		=	-I $(INCLUDE_DIR) -I $(MLX_DIR) -MMD -MP
MLXFLGS			=	-L$(MLX_DIR) -lmlx -lm -framework OpenGL -framework AppKit
DIR_DUP			=	mkdir -p $(@D)

EXECUTABLES		=	*.out *.exe

RM				=	/bin/rm -f

all: make_libs $(NAME)

make_libs:
	@printf "$(YELLOW)COMPILING LIBFT...\n$(END)"
	@$(MAKE) -C $(LIBFT_DIR) --no-print-directory
	@printf "$(YELLOW)COMPILING MINILIBX...\n$(END)"
	@$(MAKE) -C $(MLX_DIR) --no-print-directory

$(NAME): $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) $(MLXFLGS) -o $(NAME)
		@printf "\n$(GREEN)$(NAME) COMPILED!\n$(END)"

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) $(FILE_MAKE)
	@printf "\r$(CL_LINE)$(YELLOW)Compiling... $(END)$(patsubst $(BUILD_DIR)%,%,$@)"
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

norm:
	norminette
	
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) clean --no-print-directory
	@$(RM) $(OBJ) $(DEP) $(EXECUTABLES)
	@printf "$(RED)$(NAME) OBJECTS DELETED\n$(END)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean --no-print-directory
	@$(MAKE) -C $(MLX_DIR) fclean --no-print-directory
	@$(RM) $(NAME)
	@$(RM) -r $(BUILD_DIR)
	@printf "$(RED)$(NAME) DELETED\n$(END)"

re: fclean all

.PHONY: all clean fclean re bonus
	
-include $(DEP)