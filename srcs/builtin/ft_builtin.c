/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:11:33 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/02 19:43:05 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PWD
void	ft_pwd(char **env, t_exe *current)
{
	char	buf[1024];
	char	*cwd;
	size_t	size;

	(void)env;
	if (current->cmds[1][0] == '-')
	{
		ft_putstr("bash : ");
		ft_putstr(current->cmds[1]);
		ft_putstr(" invalid option\n");
		return ;
	}
	size = 1024;
	cwd = getcwd(buf, size);
	ft_putstr(cwd);
	ft_putstr("\n");
}

// ENV
void	ft_env(t_env *built)
{
	int	i;

	i = 0;
	while (built->env[i])
	{
		if (built->env[i][0] == '_' && built->env[i][1] == '=')
			ft_putstr("_=/usr/bin/env\n");
		else
		{
			ft_putstr(built->env[i]);
			ft_putstr("\n");
		}
		i++;
	}
}

void	ft_redirec_builtin(t_exe *current, int fd_outfile, int saved_stdout)
{
	int	flags;

	if (current->output_file)
	{
		saved_stdout = dup(STDOUT_FILENO);
		flags = O_WRONLY | O_CREAT;
		if (current->append_output)
			flags |= O_APPEND;
		else
			flags |= O_TRUNC;
		fd_outfile = open(current->output_file, flags, 0644);
		if (fd_outfile == -1)
			exit(EXIT_FAILURE);
		if (dup2(fd_outfile, STDOUT_FILENO) == -1)
			exit(EXIT_FAILURE);
		close(fd_outfile);
	}
	else
	{
		(void)saved_stdout;
		return ;
	}
}

void	ft_builtin(t_exe *current, t_env *built, t_b *b, char **env)
{
	if (ft_strcmp(current->cmds[0], "cd") == 0)
		ft_cd(current, built);
	else if (ft_strcmp(current->cmds[0], "pwd") == 0)
		ft_pwd(env, current);
	else if (ft_strcmp(current->cmds[0], "env") == 0)
		ft_env(built);
	else if (ft_strcmp(current->cmds[0], "echo") == 0)
		ft_echo(current, built);
	else if (ft_strcmp(current->cmds[0], "export") == 0)
		ft_call_export(built, current);
	else if (ft_strcmp(current->cmds[0], "unset") == 0)
		ft_call_unset(built, current);
	else if (ft_strcmp(current->cmds[0], "exit") == 0)
		ft_exit(current, built, b);
}

void	ft_which_builtin(t_exe *current, t_env *built, t_b *b, char **env)
{
	int	fd_outfile;
	int	saved_stdout;

	fd_outfile = 0;
	saved_stdout = 0;
	if (current->output_file)
	{
		ft_redirec_builtin(current, fd_outfile, saved_stdout);
		ft_builtin(current, built, b, env);
		dup2(saved_stdout, STDOUT_FILENO);
	}
	else if (current->output_file == NULL)
		ft_builtin(current, built, b, env);
	built->exit_code = 0;
}
