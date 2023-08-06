# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/18 19:36:01 by fbosch            #+#    #+#              #
#    Updated: 2023/08/06 21:15:51 by fbosch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

GREEN=\033[1;32m
RED=\033[1;31m
BLUE=\033[1;34m
YELLOW=\x1b[33;01m
END=\033[0m
CL_LINE=\033[K

NAME			=	fdf
BONUS_NAME		=	fdf_bonus

LIBFT			=	libft.a
LIBFT_DIR		=	libft/

SRC				=	main.c events.c events_utils.c utils.c map_load.c draw.c \
					bresenham.c map_load_utils.c draw_utils.c menu.c \
					events_utils_2.c matrix.c cube.c rotation_sphere.c\
					cohen_sutherland.c\

BONUS_SRC		=

SRC_DIR			=	src/

INCLUDE_DIR		=	include/
BUILD_DIR		=	.build/

MLX				=	libmlx.a
MLX_DIR			=	minilibx_macos/

SRC_FILES		=	$(addprefix $(SRC_DIR),$(SRC))
BONUS_FILES		=	$(addprefix $(SRC_DIR),$(BONUS_SRC))

OBJ				=	$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(SRC_FILES))
BONUS_OBJ		=	$(patsubst $(SRC_DIR)%.c,$(BUILD_DIR)%.o,$(BONUS_FILES))

DEP				=	$(OBJ:%.o=%.d) $(BONUS_OBJ:%.o=%.d)

CC				=	cc #-fsanitize=address
CFLAGS			=	#-Wall -Wextra -Werror
DEPFLAGS		=	-I $(INCLUDE_DIR) -I $(MLX_DIR) -MMD -MP
MLXFLGS			=	-L$(MLX_DIR) -lmlx -framework OpenGL -framework AppKit
DIR_DUP			=	mkdir -p $(@D)

EXECUTABLES		=	*.out *.exe

RM				=	/bin/rm -f

all: make_libs $(NAME)

make_libs:
	@printf "$(YELLOW)COMPILING LIBFT...\n$(END)"
	@$(MAKE) -C $(LIBFT_DIR)
	@printf "$(YELLOW)COMPILING MINILIBX...\n$(END)"
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJ) $(LIBFT_DIR)$(LIBFT)
		@$(CC) $(CFLAGS) $(OBJ) $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX) $(MLXFLGS) -o $(NAME)
		@printf "\n$(GREEN)$(NAME) COMPILED!\n$(END)"

bonus: make_libs make_minilibx .bonus

.bonus: $(BONUS_OBJ) $(LIBFT_DIR)$(LIBFT)
	@$(CC) $(CFLAGS) $(BONUS_OBJ) $(LIBFT_DIR)$(LIBFT) -o $(BONUS_NAME)
	@printf "\n$(GREEN)$(BONUS_NAME) COMPILED!\n$(END)"
	@touch .bonus

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(LIBFT_DIR)$(LIBFT) $(MLX_DIR)$(MLX)
	@printf "\r$(CL_LINE)$(YELLOW)Compiling... $(END)$(patsubst $(BUILD_DIR)%,%,$@)"
	@$(DIR_DUP)
	
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

norm:
	norminette
	
clean:
	@$(MAKE) -C $(LIBFT_DIR) clean
	@$(MAKE) -C $(MLX_DIR) clean
	@$(RM) $(OBJ) $(OBJ_BONUS) $(DEP) $(EXECUTABLES)
	@printf "$(RED)$(NAME) OBJECTS DELETED\n$(END)"

fclean: clean
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@$(MAKE) -C $(MLX_DIR) fclean
	@$(RM) $(NAME) $(BONUS_NAME)
	@$(RM) -r $(BUILD_DIR)
	@printf "$(RED)$(NAME) DELETED\n$(END)"

re: fclean all

.PHONY: all clean fclean re bonus
	
-include $(DEP)