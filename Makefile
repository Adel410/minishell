# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nicjousl <nicjousl@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 17:50:59 by nicjousl          #+#    #+#              #
#    Updated: 2024/09/04 13:16:45 by nicjousl         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###	NAME ###

NAME	= minishell

### SOURCES	###

FILES	=	srcs/main.c \
			srcs/prompt/ft_prompt.c \
			srcs/prompt/ft_history.c \
			srcs/signal/ft_signal.c \
			srcs/error/ft_error.c \
			srcs/builtin/ft_builtin.c \
			srcs/debug/ft_debug.c \
			srcs/lexer/ft_lexer.c \
			srcs/parsing/ft_meta_tab_utils.c \
			srcs/parsing/ft_option_tab.c \
			srcs/parsing/ft_nice_tab.c \
			srcs/parsing/ft_meta_tab.c \
			srcs/parsing/ft_string_tab.c \
			srcs/utils/ft_free.c \
			srcs/utils/ft_strdup.c \
			srcs/utils/ft_strjoin.c \
			srcs/utils/ft_tools.c \
			srcs/utils/ft_split.c \
			srcs/utils/ft_split2.c \
			srcs/utils/ft_colors.c \
			srcs/utils/ft_init.c \

INCLUDES	= includes/minishell.h \

### MACROS ###

CC	= cc

LDFLAGS = -lreadline

CFLAGS	= -g -Wall -Werror -Wextra

OBJ	= $(FILES:.c=.o)

### RULES ###

all	: $(NAME)

$(NAME)	: $(OBJ) $(INCLUDES)
		$(CC) $(OBJ) $(LDFLAGS) -o  $(NAME) 

clean:
		rm $(OBJ)

fclean:
		rm $(NAME) $(OBJ)

re: fclean all

.PHONY:	clean fclean re