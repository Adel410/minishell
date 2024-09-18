/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils_exec2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/17 19:00:49 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/09/18 16:29:39 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	ft_create_new(t_exe *new)
{
	new->next = ft_calloc(1, sizeof(t_exe));
	if (new->next == NULL)
		return ;
	new->next->next = NULL;
}

void	ft_get_path(t_b *b, char **env)
{
	int	i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], "PATH=", 5) == 0)
		{
			b->path = ft_strdup(env[i] + 5);
			return ;
		}
		i++;
	}
}

void	ft_cmd_path(t_b *b, char **env)
{
	ft_get_path(b, env);
	b->cmd_path = ft_split2(b->path, ":");
	ft_add_slash_to_paths(b->cmd_path);
}

void	ft_print_exec(t_exe *exec)
{
	while (exec)
	{
		if (exec->cmds)
		{
			printf("cmds: %s\n", exec->cmds[0]);
			if (exec->cmds[1])
				printf("options: %s\n", exec->cmds[1]);
		}
		printf("builtin: %d\n", exec->builtin);
		printf("input_file: %s\n", exec->input_file);
		printf("output_file: %s\n", exec->output_file);
		printf("append_output: %d\n", exec->append_output);
		printf("here_doc: %d\n", exec->here_doc);
		printf("string: %s\n", exec->string);
		printf("limiter: %s\n", exec->limiter);
		printf("NEW NODE ------>\n");
		exec = exec->next;
	}
}

void	ft_check_type(t_lex *lex)
{
	t_lex	*current;

	current = lex;
	if (current->type == '4')
		ft_putstr("minishell: syntax error near unexpected token '|'\n");
	else if (current->type == '5' || current->type == '6'
		|| current->type == '#' || current->type == '$')
		ft_putstr("minishell: syntax error near unexpected token `newline'\n");
}
