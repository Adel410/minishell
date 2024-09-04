/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:53:19 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/04 14:37:37 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "./builtin.h"
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <termios.h>
# include <unistd.h>
# define RED "\033[31m"
# define GREEN "\033[32m"
# define BLUE "\033[34m"
# define YELLOW "\033[33m"
# define RESET "\033[0m"
# define MAGENTA "\033[35m"
# define CYAN "\033[36m"
# define BIG "\033[1m"
# define ITA "\033[3m"
# define FLASH "\033[5m"
# define LOW "\033[2m"
# define INVERT "\033[7m"
# define BAR "\033[9m"
# define TOKEN "<>|"

typedef struct s_a
{
	char	*input;
	char	**tab_input;
	char	**tab_option_input;
	char	**tab_meta_input;
	char	**tab_string_input;
	char	***tab_cmd;
	char	*str_tmp;
	char	*str_tmp2;

	int		*token_pos;

	int		meta_tab_size;
	int		option_size;
	int		cmd_tab_size;
	int		cmd_size;
	int		meta_size;
	int		token_count;
	int		meta_index;
	int		option_index;
	int		meta_copy;
	int		simple_quotes_count;
	int		doble_quotes_count;

	int		i;
	int		j;
	int		k;
	int		h;
	int		t;
	int		b;
	int		v;

	int		start;
	int		size;
}			t_a;

//## DEBUG ##
void		ft_debug(t_a *a);

//## LEXER ##
void		ft_lexer(t_a *a);
void		ft_parse_to_lex(t_a *a);

//## PARSING ##
//##META TAB UTILS ##
int			ft_meta_char(char c);
int			ft_meta_detect(char *str);
void		ft_meta_tab_size(t_a *a);
//##META TAB ##
void		ft_meta_new_tab(t_a *a);
void		ft_meta_new_tab2(t_a *a);
void		ft_meta_new_tab3(t_a *a);
void		ft_meta_new_tab4(t_a *a);

//##NICE TAB ##
void		ft_meta_tab(t_a *a);
void		ft_nice_tab(t_a *a);
void		ft_option_tab(t_a *a);

//##OPTION TAB ##
void		ft_option_new_tab(t_a *a);
void		ft_option_cut_tab(t_a *a);
void		ft_option_join_tab(t_a *a);
int			ft_option_tab_size(t_a *a);

//##STRING TAB##
void		ft_string_new_tab(t_a *a);
void		ft_string_new_tab2(t_a *a);
void		ft_string_new_tab3(t_a *a);

//## UTILS ##
//## COLORS ##
void		ft_putstr2(char *str);
void		ft_color(char *str, int n, ...);

//## FREE ##
void		ft_free(t_a *a);
void		ft_cleanup(t_a *a);

//## INIT ##
void		ft_init_prompt(t_a *a);
void		ft_init_for_meta_tab(t_a *a);
void		ft_init_for_option_tab(t_a *a);
void		ft_init_for_string_tab(t_a *a);
void		ft_init_for_lexer(t_a *a);

//## SPLIT ##
void		freetab(char **tab, int k);
char		**ft_split(char const *s, char c);
char		**ft_split2(char *str, char *charset);
// static int	ft_word_count(char *s, char c);
// static char	**ft_malloc_word(char **tab, char *s, char c);
// static char	*ft_put_word_in_malloc(char *s, char c, char *tab);

//## STRDUP ##
char		*ft_strdup(char *s);
char		*ft_malloc_copy_char(char c);
char		*ft_strndup(const char *s, int n);
char		*ft_strndup2(const char *s, int n);
char		*ft_master_strndup(char *s, int start, int size);

//## STRJOIN ##
int			ft_size(char const *s1, char const *s2);
char		*ft_strjoin(char const *s1, char const *s2);
char		*ft_join(char *str, char const *s1, char const *s2);

//## TOOLS ##
int			ft_strlen(char *str);
int			ft_strstrlen(char **str);
void		ft_bzero(void *s, size_t n);
void		*ft_calloc(size_t nmemb, size_t size);
int			ft_strncmp(const char *s1, const char *s2, size_t n);

//## BUILTIN ##
void		ft_cd(char *str);
void		ft_env(t_env **built);
void		ft_echo(char *str);
void		ft_pwd(char *str, char **env);
void		ft_which_builtin(t_env **built, t_a *a, char *str, char **env);

//## ERROR ##
void		ft_error(int i, t_a *a);

//## SIGNAL ##
void		ft_handle_sigint(int sig);
void		ft_handle_sigquit(int sig);
void		ft_setup_signals_handler(void);

//## PROMPT ##
void		ft_init_history(void);
void		ft_prompt(char **env, t_a *a, t_env **built);

// //  #ERROR#
// void		ft_error(int i, t_a *a);
// void		ft_free(t_a *a);
// void		ft_cleanup(t_a *a);

// //  #PROMPT
// void		ft_prompt(char **env, t_a *a);
// void		ft_init_prompt(t_a *a);

// void		ft_lexer(t_a *a);

// //  #OPTION TAB
// void		ft_option_tab(t_a *a);
// void    	ft_meta_tab(t_a *a);

// //  #RANDOM
// void		ft_init_for_option_tab(t_a *a);
// void		ft_init_for_meta_tab(t_a *a);
// void		ft_cmd_to_tab(t_a *a);
// void		ft_nice_tab(t_a *a);void	ft_env(t_env **built)

// // #HISTORY
// void		ft_init_history(void);

// // #SIGNALS
// void		ft_setup_signals_handler(void);
// void		ft_handle_sigint(int sig);

// // #BUILTIN
// void		ft_which_builtin(t_a *a, char *str, char **env);
// void		ft_pwd(char *str, char **envp);

// // #TOOLS#
// char		**ft_split(char const *s, char c);
// char		*ft_strjoin(char const *s1, char const *s2);
// char		*ft_malloc_copy_char(char c);
// char		*ft_strdup(char *s);
// char		*ft_strndup(const char *s, int n);
// char		*ft_strndup2(const char *s, int n);
// char		*ft_master_strndup(char *s, int start, int size);
// int			ft_strncmp(const char *s1, const char *s2, size_t n);
// int			ft_strstrlen(char **str);
// int			ft_strlen(char *str);

// void		*ft_calloc(size_t nmemb, size_t size);
// int			ft_option_tab_size(t_a *a);
// void		ft_option_new_tab(t_a *a);
// void		ft_option_cut_tab(t_a *a);
// void		ft_option_join_tab(t_a *a);
// int			ft_meta_char(char c);
// void		ft_meta_tab_size(t_a *a);
// int			ft_meta_detect(char *str);
// void		ft_meta_new_tab(t_a *a);
// void		ft_meta_tab_size(t_a *a);
// void		ft_meta_new_tab2(t_a *a);
// void		ft_meta_new_tab3(t_a *a);
// void		ft_meta_new_tab4(t_a *a);
// void		ft_color(char *str, int n, ...);
// void		ft_debug(t_a *a);

#endif