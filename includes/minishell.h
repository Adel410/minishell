/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:53:19 by nicjousl          #+#    #+#             */
/*   Updated: 2024/09/18 16:15:19 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <fcntl.h>
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

typedef struct s_b
{
	char			**cmd_path;
	char			*path;
	int				nb_cmds;
	int				pid;
	int				i;
	int				l;
	int				m;
	int				n;
	int				o;
	int				p;
	int				w;
}					t_b;

typedef struct s_a
{
	char			*input;
	char			**tab_space_input;
	char			**tab_input;
	char			**tab_option_input;
	char			**tab_meta_new_input;
	char			**tab_meta_input;
	char			**tab_string_input;
	char			***tab_cmd;
	char			*str_tmp;
	char			*str_tmp2;
	char			*str_path;
	char			*str_test;
	char			**cmd_path;

	int				*token_pos;

	int				tab_space_size;
	int				string_tab_size;
	int				meta_tab_size;
	int				option_size;
	int				cmd_tab_size;
	int				cmd_size;
	int				meta_size;
	int				token_count;
	int				meta_index;
	int				option_index;
	int				meta_copy;
	int				simple_quotes_count;
	int				doble_quotes_count;

	int				i;
	int				j;
	int				k;
	int				h;
	int				t;
	int				u;
	int				v;
	int				w;

	int				len_input;
	int				debug;
	int				nb_cmds;
	int				pid;
	int				error;
	int				flag;
	int				detect;

	int				start;
	int				size;
	struct s_b		*b;
}					t_a;

typedef struct s_lex
{
	char			type;
	char			*str;
	struct s_lex	*next;
}					t_lex;

typedef struct s_env
{
	char			*env_str;
	struct s_env	*next;
}					t_env;

typedef struct s_exe
{
	char			**cmds;
	char			*string;
	char			**cmd_path;
	char			*input_file;
	char			*limiter;
	char			*output_file;
	int				append_output;
	int				here_doc;
	int				builtin;
	struct s_exe	*next;
	struct s_a		*a;
}					t_exe;

int					ft_check_access(char *to_test, char **paths);
void				ft_print_exec(t_exe *exec);
void				ft_check_type(t_lex *lex);
void				ft_init_for_string_tab(t_a *a);
void				ft_init_for_check_close_quotes(t_a *a);
void				ft_check_here_doc(t_exe *exec);
void				ft_add_slash_to_paths(char **paths);
void				ft_cmd_path(t_b *b, char **env);
void				ft_create_new(t_exe *new);
void				ft_recast_to_lst(t_a *a, t_lex *lex);
void				ft_debug_lst(t_exe *exe);
void				ft_debug_lexer(t_a *a);
void				ft_debug_parser(t_a *a);
void				ft_debug_parser2(t_a *a);
void				ft_debug_parser3(t_a *a);
void				ft_free_lexer(t_a *a);
void				ft_free_parser3(t_a *a);
void				ft_free_parser2(t_a *a);
void				ft_free_parser(t_a *a);
void				ft_putstr(char *str);
int					ft_strstrstrlen(char ***str);
void				ft_space_tab(t_a *a);
void				ft_double_redir(t_a *a);
void				ft_recast(t_lex *lex, t_exe *exec);
//## REDIRECTION ##
void				ft_setup_redirection(t_exe *exec, int cmd_index,
						int *pipefd, int count_cmds);
void				ft_close_pipes(int *pipefd, int cmds_count);

//## EXECUTION ##
int					ft_execute(t_lex *lex, t_env **built, char **env);
void				ft_init_exec(t_exe *exec);
void				ft_free_cmds(t_exe *exec);
void				ft_free_exec(t_exe *exec, t_a *a);
int					ft_count_cmds(t_lex *lex);
int					ft_here_doc(t_exe *exec);

//## BUILTIN ##
void				ft_lstadd_back(t_env **lst, t_env *new);
t_env				*ft_lstnew(char *str);
void				ft_free_stack(t_env **head);
void				ft_read_list(t_env **head);

//## DEBUG ##
void				ft_debug(t_a *a);

//## LEXER ##
void				ft_lexer(t_a *a, t_env **built, char **env);
void				ft_parse_to_lex(t_a *a);
void				ft_detect_lexer(t_a *a);
void				ft_detect_lexer2(t_a *a);
void				ft_detect_lexer3(t_a *a);
void				ft_detect_lexer4(t_a *a);
void				ft_detect_lexer5(t_a *a);
void				ft_detect_lexer6(t_a *a);

//## PARSING ##
//##META TAB UTILS ##
int					ft_meta_char(char c);
int					ft_meta_detect(char *str);
void				ft_meta_tab_size(t_a *a);
//##META TAB ##
void				ft_meta_new_tab(t_a *a);
void				ft_meta_new_tab2(t_a *a);
void				ft_meta_new_tab3(t_a *a);
void				ft_meta_new_tab4(t_a *a);

//##NICE TAB ##
void				ft_meta_tab(t_a *a);
void				ft_nice_tab(t_a *a);
void				ft_option_tab(t_a *a);

//##OPTION TAB ##
void				ft_option_new_tab(t_a *a);
void				ft_option_cut_tab(t_a *a);
void				ft_option_join_tab(t_a *a);
int					ft_option_tab_size(t_a *a);

//##STRING TAB##
void				ft_string_new_tab(t_a *a);
void				ft_string_new_tab2(t_a *a);
void				ft_string_new_tab3(t_a *a);

//##STRING TAB UTILS##
int					ft_string_char(char c);
int					ft_string_detect(char *str);
void				ft_string_end_tmp(t_a *a);
void				ft_string_tmp(t_a *a);

//## UTILS ##
//## COLORS ##
void				ft_putstr2(char *str);
void				ft_color(char *str, int n, ...);

//## FREE ##
void				ft_free(t_a *a);
void				ft_cleanup(t_a *a);

//## INIT ##
void				ft_init_prompt(t_a *a);
void				ft_init_for_meta_tab(t_a *a);
void				ft_init_for_option_tab(t_a *a);
void				ft_init_for_string_tab(t_a *a);
void				ft_init_for_lexer(t_a *a);

//## SPLIT ##
void				freetab(char **tab, int k);
char				**ft_split(char *s, char c);
char				**ft_split2(char *str, char *charset);
// static int	ft_word_count(char *s, char c);
// static char	**ft_malloc_word(char **tab, char *s, char c);
// static char	*ft_put_word_in_malloc(char *s, char c, char *tab);

//## STRDUP ##
char				*ft_strdup(char *s);
char				*ft_malloc_copy_char(char c);
char				*ft_strndup(const char *s, int n);
char				*ft_strndup2(const char *s, int n);
char				*ft_master_strndup(char *s, int start, int size);

//## STRJOIN ##
int					ft_size(char const *s1, char const *s2);
char				*ft_strjoin(char const *s1, char const *s2);
char				*ft_strjoin2(char const *s1, char const *s2);
char				*ft_join(char *str, char const *s1, char const *s2);

//## TOOLS ##
int					ft_strlen(char *str);
int					ft_strstrlen(char **str);
void				ft_bzero(void *s, size_t n);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(char *s1, char *s2);
char				*ft_free_stash(char *str);
char				*get_next_line(int fd);

//## BUILTIN ##
void				ft_echo(t_exe *current);
void				ft_which_builtin(t_exe *current, t_env **built, char **env);

//## ERROR ##
void				ft_error(int i, t_a *a);

//## SIGNAL ##
void				ft_handle_sigint(int sig);
void				ft_handle_sigquit(int sig);
void				ft_setup_signals_handler(void);

//## PROMPT ##
void				ft_init_history(void);
void				ft_prompt(char **env, t_a *a, t_env **built);

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
// void		ft_nice_tab(t_a *a);

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