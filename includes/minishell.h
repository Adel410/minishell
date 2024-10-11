/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 17:53:19 by nicjousl          #+#    #+#             */
/*   Updated: 2024/10/11 14:00:41 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <limits.h>
# include <linux/limits.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/stat.h>
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
# define TOKEN "\\><|\\'\""

typedef struct s_b
{
	int				infile;
	int				outfile;
	int				hd_count;
	char			**cmd_path;
	char			*path;
	int				*pipefd;
	int				status;
	int				nb_cmds;
	int				nb_cmds1;
	int				input_count;
	int				output_count;
	int				limiter_count;
	int				pipe_count;
	pid_t			*pid;
	int				input_index;
	int				output_index;
	int				limiter_index;
	int				i;
	int				w;
	int				x;
}					t_b;

typedef struct s_parse
{
	char			*arg;
	struct s_parse	*next;
}					t_parse;

typedef struct s_lex
{
	int				flag_echo;
	char			type;
	char			*str;
	struct s_lex	*prev;
	struct s_lex	*next;
}					t_lex;

typedef struct s_split_data3
{
	char			**split;
	char			*str;
	char			*charset;
	int				i;
	int				j;
	int				word;
}					t_split_data3;

typedef struct s_split_data
{
	char			**tab;
	char			*s;
	char			c;
	int				i;
	int				j;
	int				word_count;
}					t_split_data;

typedef struct s_env
{
	int				i;
	int				j;
	int				flag;
	long			exit_code;
	int				save_stdin;
	int				save_stdout;
	int				fd_outfile;
	char			**env;
	char			*def;
	char			*value;
	char			*expand_string;
	char			*tmp;
	char			*input;
}					t_env;

typedef struct s_exe
{
	int				exit_code;
	char			**cmds;
	char			**cmd_path;
	char			*redir;
	char			*path;
	char			*string;
	char			**input_file;
	char			**output_file;
	char			**limiter;
	int				append_output;
	int				here_doc;
	int				fd_here_doc;
	int				hd_index;
	int				builtin;
	struct s_exe	*next;
	struct s_b		*b;
}					t_exe;

extern int			g_signal_received;

//## PARSING ##
void				ft_invalid_input(t_parse *parse);
void				ft_trim_arg(t_parse *parse);
void				ft_concatenate(t_parse *parse);
int					ft_check_tab(char **tab);
int					ft_space_arg(t_parse *parse);
int					ft_meta_arg(t_parse *parse);
void				ft_string_arg(t_parse *parse);
void				ft_check_double_redir(t_parse *parse);
void				ft_check_redir_type(t_parse **tmp, char redir_char);
void				ft_join_double_redir(t_parse *tmp, int redir_type);
int					ft_join_string(t_parse *parse);
void				ft_printf_lst(t_parse *parse);
void				ft_free_node(t_parse *node);
void				ft_free_tab(char **tab);
void				ft_free_parser(t_parse *parse);
void				ft_parsing(t_parse *parse, t_env *built);
int					ft_string_is_closed(char *str);
void				ft_free_env(t_env *built);
void				ft_free_lex(t_lex *lex);
void				ft_exit(t_exe *exec, t_env *built, t_b *b);
int					ft_check_access(char *to_test, char **paths);
void				ft_print_exec(t_exe *exec);
void				ft_check_type(t_lex *lex);
void				ft_check_here_doc(t_exe *exec, t_env *built);
void				ft_add_slash_to_paths(char **paths);
void				ft_cmd_path(t_b *b, char **env);
void				ft_create_new(t_exe *new);
void				ft_debug_lst(t_exe *exe);
void				ft_putstr(char *str);
int					ft_strstrstrlen(char ***str);
int					ft_recast(t_lex *lex, t_exe *exec, t_env *built, t_b *b);

//## REDIRECTION ##
void				ft_setup_redirection(t_exe *exec, t_b *b);
void				ft_close_pipes(int *pipefd, int cmds_count);

//## EXECUTION ##
void				ft_infile_outfile(t_lex *lex, t_exe *new, t_b *b, char c);
void				ft_output_redirection(t_exe *cmd, t_b *b);
void				ft_handle_pipe_output(t_b *b);
void				ft_handle_single_output(t_exe *cmd, int i);
void				ft_set_flags(t_exe *cmd, int *flags);
int					ft_execute(t_lex *lex, t_env *built);
void				ft_init_exec(t_exe *exec);
void				ft_free_cmds(t_exe *exec);
void				ft_free_exec(t_exe *exec);
int					ft_count_cmds(t_exe *exec);

//## BUILTIN ##
void				ft_lstadd_back(t_env **lst, t_env *new);
t_env				*ft_lstnew(char *str);
void				ft_free_stack(t_env **head);
void				ft_read_list(t_env **head);
void				ft_echo(t_exe *current, t_env *built);
void				ft_which_builtin(t_exe *current, t_env *built, t_b *b);

//## META TAB UTILS ##
int					ft_meta_char(char c);
int					ft_meta_detect(char *str);

//## STRING TAB UTILS ##
int					ft_string_char(char c);
int					ft_string_detect(char *str);

//## COLORS ##
void				ft_putstr2(char *str);
void				ft_color(char *str, int n, ...);

//## SPLIT ##
void				freetab(char **tab, int k);
char				**ft_split(char *s, char c);
char				**ft_split2(char *str, char *charset);

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
void				ft_print_tab(char **tab);
int					ft_check_for_options(t_lex *next, t_exe *new);
void				ft_count_elements(t_lex *lex, t_b *b);
int					ft_check_last_node(t_lex *tmp);
void				ft_unlink_here_doc(int here_doc_count);
void				ft_int_to_str(int num, char *buffer);
int					ft_strlen(char *str);
int					ft_strstrlen(char **str);
void				ft_infile_outfile(t_lex *lex, t_exe *new, t_b *b, char c);
void				*ft_calloc(size_t nmemb, size_t size);
int					ft_strncmp(const char *s1, const char *s2, size_t n);
int					ft_strcmp(char *s1, char *s2);
char				*ft_free_stash(char *str);
char				*get_next_line(int fd);
int					ft_get_digit(const char c);
void				freetab(char **tab, int k);
char				*ft_strncpy(char *dest, const char *src, unsigned int n);
int					ft_char_is_separator1(char c, char *charset);
void				ft_process_separator(t_split_data3 *data);
long				ft_strtol(const char *nptr, char **endptr, int base);
void				ft_print_and_close(t_env *built);
char				*ft_merge_sign_with_arg(char **cmds,
						t_env *built);
int					ft_handle_too_many_args(char **cmds,
						char *merged_str, t_env *built);
void				ft_is_check_after_dollar(char *str,
						t_env *built);
void				ft_zsh_prompt(t_env *built);
void				ft_multiple_checks(t_env *built, char *input);
void				ft_reset_std(t_env *built);
void				ft_ctrl_d(t_env *built);
char				*ft_here_doc_bis(char *str);
void				ft_dup_here_doc(t_exe *exec, char *file_name,
						int nb_count1);
void				ft_save_std(t_env *built);
int					ft_here_doc(t_exe *exec, t_env *built, t_b *b);
char				*ft_create_filename(int here_doc_count);
int					ft_size_of_expand(char *str);
int					ft_correct_name_export(char *str, t_env *built);
int					ft_check_export(char *str, t_env *built);
void				ft_dup2_first_last(int value, t_b *b, t_env *built);
char				*ft_strjoin3(char *s1, char *s2);
void				ft_free_string_and_parse(char *str,
						t_parse *parse);
int					ft_is_valid_number(const char *str);
char				*ft_strcat(char *dest, const char *src);
char				*ft_strcpy(char *dest, const char *src);
char				*ft_join_path(t_b *b, char *cmd);
int					ft_manage_string(t_lex *lex, t_parse *tmp, char index);
void				ft_join_echo_args(t_parse *tmp, t_lex *lex, char index);
int					ft_test_if_execute(char *arg, char **env);
void				ft_export_alphabetic_order(t_env *built);
int					ft_isdigit(char c);
int					ft_is_alpha(char c);
void				ft_handle_syntax_error(t_parse *parse);
int					ft_check_parsing(t_parse *parse);
void				ft_pipe(int *pipefd, int cmds_count);
void				ft_put_error2(char *str, int exit_code);
void				ft_put_error(char *str, int exit_code);
char				ft_tolower(char c);
int					ft_isupper(char c);
int					ft_islower(char c);
int					ft_isdigit(char c);
int					ft_isspace(char c);
int					ft_atoi(char *str);
int					ft_is_alpha_num_and_space(char c);
void				ft_putstr_fd(char *s, int fd);
int					ft_count_cmds2(t_lex *lex);
int					ft_is_alpha_num(char c);
void				ft_close_and_wait(t_b *b, t_env *built);
int					ft_init_pipe_and_pid(t_b *b);
void				ft_isolate_dollar(char *str, t_env *built);
void				ft_expand_env(t_env *built);
char				*ft_expand_dollar(char *str, t_env *built);
void				ft_free_b(t_b *b);
char				*ft_itoa(int i);
void				ft_iso_dol(char *str, int i, t_env *built);
int					ft_dollar_in_string(char *str);
int					ft_strncmpchar(char *s1, char *s2, char c);
void				ft_expand_arg(t_parse *parse, t_env *built);
void				ft_copy_env(t_env *built, char **new_env);
void				ft_call_unset(t_env *built, t_exe *current);
void				ft_print_env(t_env *head);
int					ft_find_end_def(char *str);
void				ft_call_export(t_env *built, t_exe *current);
void				ft_cd(t_exe *current, t_env *built);
char				*ft_get_path(char *path, char **env);
char				**ft_split4(char const *s, char c);
void				ft_check_node(t_exe *current);
int					ft_check_limiter(t_exe *current);
void				ft_check_list(t_exe *exec, t_env *built, t_b *b);
int					ft_check_if_already(t_exe *current, char *str);
int					ft_is_builtin(char *str);
void				ft_strrtrim(char *str, char c);
void				ft_strtrim(char *str, char c);
void				ft_print_lex(t_lex *lex);
void				ft_lexer(t_parse *parse, t_env *built);
char				**ft_split3(char *str);

//## ERROR ##
void				ft_error(int i);

//## SIGNAL ##
void				ft_handle_sigint(int sig);
void				ft_handle_sigquit(int sig);
void				ft_setup_signals_handler(void);

//## PROMPT ##
void				ft_init_history(void);
void				ft_prompt(t_env *built);

#endif