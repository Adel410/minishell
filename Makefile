# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/08/01 17:50:59 by nicjousl          #+#    #+#              #
#    Updated: 2024/10/13 16:17:55 by ahadj-ar         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

###	NAME ###

NAME	= minishell

### SOURCES	###

FILES	=	srcs/main.c \
			srcs/prompt/ft_prompt.c \
			srcs/prompt/ft_prompt_utils.c \
			srcs/prompt/ft_history.c \
			srcs/signal/ft_signal.c \
			srcs/error/ft_error.c \
			srcs/builtin/ft_builtin.c \
			srcs/builtin/ft_echo.c \
			srcs/builtin/ft_exit.c \
			srcs/builtin/ft_exit_utils.c \
			srcs/builtin/ft_cd.c \
			srcs/builtin/ft_export.c \
			srcs/builtin/ft_unset.c \
			srcs/builtin/ft_builtin_utils.c \
			srcs/lexer/ft_lexer.c \
			srcs/lexer/ft_lexer_utils.c \
			srcs/parsing/ft_meta_list.c \
			srcs/parsing/ft_nice_list.c \
			srcs/parsing/ft_space_list.c \
			srcs/parsing/ft_string_list.c \
			srcs/parsing/ft_concat_arg.c \
			srcs/parsing/ft_parsing_utils2.c \
			srcs/parsing/ft_parsing_utils.c \
			srcs/parsing/ft_double_redir.c \
			srcs/expand/ft_expand_parsing.c \
			srcs/expand/ft_expand_utils.c \
			srcs/utils/ft_alpha_num.c \
			srcs/utils/ft_strdup.c \
			srcs/utils/ft_strjoin.c \
			srcs/utils/ft_strtol.c \
			srcs/utils/ft_tools.c \
			srcs/utils/ft_tools2.c \
			srcs/utils/ft_tools3.c \
			srcs/utils/ft_gnl.c \
			srcs/utils/ft_is.c \
			srcs/utils/ft_itoa.c \
			srcs/utils/ft_split.c \
			srcs/utils/ft_split2.c \
			srcs/utils/ft_split3.c \
			srcs/utils/ft_split4.c \
			srcs/utils/ft_split_utils.c \
			srcs/utils/ft_colors.c \
			srcs/exec/ft_execution.c \
			srcs/exec/ft_recast.c \
			srcs/exec/ft_recast_files.c \
			srcs/exec/ft_recast_utils.c \
			srcs/exec/ft_redirection.c \
			srcs/exec/ft_output_redirection.c \
			srcs/exec/ft_here_doc.c \
			srcs/exec/ft_here_doc_utils.c \
			srcs/exec/ft_free_exec.c \
			srcs/exec/ft_utils_exec.c \
			srcs/exec/ft_utils_exec2.c \
			srcs/exec/ft_utils_exec3.c \
			srcs/exec/ft_utils_exec4.c \


INCLUDES	= 	includes/minishell.h \

### MACROS ###

CC	= cc

LDFLAGS = -lreadline

CFLAGS	= -g -Wall -Werror -Wextra

OBJ	= $(FILES:.c=.o)

### RULES ###

all	: $(NAME)
		@cat  test.txt

$(NAME)	: $(OBJ) $(INCLUDES)
		$(CC) $(OBJ) $(LDFLAGS) -o  $(NAME) 

clean:
		rm -f $(OBJ)

fclean:
		rm -f $(NAME) $(OBJ)

re: fclean all

.PHONY:	clean fclean re                                  
                  
