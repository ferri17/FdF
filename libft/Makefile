# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fbosch <fbosch@student.42barcelona.com>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/05/03 23:08:40 by fbosch            #+#    #+#              #
#    Updated: 2023/07/06 23:47:10 by fbosch           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

COLOUR_GREEN=\033[1;32m
COLOUR_RED=\033[1;31m
COLOUR_BLUE=\033[1;34m
COLOUR_YELLOW=\x1b[33;01m
COLOUR_END=\033[0m

SRC_LIBFT = ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c\
ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c\
ft_memmove.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c\
ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c ft_memcmp.c\
ft_strnstr.c ft_atoi.c ft_calloc.c ft_strdup.c ft_substr.c\
ft_strjoin.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c\
ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
ft_putnbr_fd.c ft_strcmp.c ft_free_malloc_array.c ft_array_len.c\
ft_split_str.c

SRC_LIBFT_BONUS = ft_lstnew_bonus.c ft_lstadd_front_bonus.c\
ft_lstsize_bonus.c ft_lstlast_bonus.c ft_lstadd_back_bonus.c\
ft_lstdelone_bonus.c ft_lstclear_bonus.c ft_lstiter_bonus.c\
ft_lstmap_bonus.c

SRC_PRINTF = ft_printf.c ft_print_text.c ft_print_pointer.c\
ft_print_integer_signed.c ft_print_unsigned.c ft_print_hexa.c

SRC_GNL = get_next_line_bonus.c get_next_line_utils_bonus.c

BUILD_DIR = .build/

OBJ = $(SRC_LIBFT:%.c=$(BUILD_DIR)%.o) $(SRC_LIBFT_BONUS:%.c=$(BUILD_DIR)%.o)\
$(SRC_PRINTF:%.c=$(BUILD_DIR)%.o) $(SRC_GNL:%.c=$(BUILD_DIR)%.o)

INCLUDE_DIR = ../include

DEP = $(OBJ:%.o=%.d)

NAME = libft.a

CC = cc
LIB = ar rc

CFLAGS = -Wall -Wextra -Werror -I$(INCLUDE_DIR)
DEPFLAGS = -MMD -MP
DIR_DUP = mkdir -p $(@D)

EXECUTABLES = *.out *.exe

RM = /bin/rm -f

.PHONY: all clean fclean re bonus

all: $(NAME)

### CREATE LIBRARY ###
$(NAME): $(OBJ)
	@printf "$(COLOUR_GREEN)Linking...\n$(COLOUR_END)"
	@$(LIB) $(NAME) $(OBJ)
	@printf "$(LIB) $(NAME) $(patsubst $(BUILD_DIR)%,%,$(OBJ))\n"
	@printf "$(COLOUR_GREEN)Compilation libft done!\xE2\x9C\x85\n$(COLOUR_END)"

### CREATE ALL OBJECT FILES FROM SOURCE FILES ###
$(BUILD_DIR)%.o: %.c
	@printf "$(COLOUR_YELLOW)Compiling... $(COLOUR_END)$(patsubst $(BUILD_DIR)%,%,$@)\n"
	@$(DIR_DUP)
	@$(CC) $(CFLAGS) $(DEPFLAGS) -c $< -o $@

-include $(DEP)

clean:
	@printf "$(COLOUR_RED)Deleting...\xE2\x9D\x97\\xE2\x9D\x97\\xE2\x9D\x97\n$(COLOUR_END)"
	$(RM) $(OBJ) $(DEP) $(EXECUTABLES)

fclean: clean
	@printf "$(COLOUR_RED)Deleting...\xE2\x9D\x97\\xE2\x9D\x97\\xE2\x9D\x97\n$(COLOUR_END)"
	$(RM) $(NAME)		
	$(RM) -r $(BUILD_DIR)

re: fclean all
