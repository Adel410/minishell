/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahadj-ar <ahadj-ar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/09 13:11:33 by ahadj-ar          #+#    #+#             */
/*   Updated: 2024/10/11 12:59:58 by ahadj-ar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

// PWD
void	ft_pwd(t_exe *current, t_env *built)
{
	char	buf[PATH_MAX];
	char	*cwd;
	size_t	size;

	if (current->cmds[1] && current->cmds[1][0] == '-')
	{
		ft_putstr("minishell : ");
		ft_putstr(current->cmds[1]);
		ft_putstr(" invalid option\n");
		built->exit_code = 1;
		return ;
	}
	size = PATH_MAX;
	cwd = getcwd(buf, size);
	if (cwd == NULL)
	{
		perror("minishell : pwd");
		built->exit_code = 1;
	}
	else
	{
		ft_putstr(cwd);
		ft_putstr("\n");
		built->exit_code = 0;
	}
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

void	ft_redirec_builtin(t_exe *current)
{
	int	flags;
	int	fd_outfile;
	int	i;

	i = 0;
	if (current->output_file)
	{
		while (current->output_file[i])
		{
			flags = O_WRONLY | O_CREAT;
			if (current->append_output)
				flags |= O_APPEND;
			else
				flags |= O_TRUNC;
			fd_outfile = open(current->output_file[i], flags, 0644);
			if (fd_outfile == -1)
				ft_put_error2(current->output_file[i], 1);
			if (dup2(fd_outfile, STDOUT_FILENO) == -1)
				ft_put_error2(current->output_file[i], 1);
			close(fd_outfile);
			i++;
		}
	}
}

void	ft_builtin(t_exe *current, t_env *built, t_b *b)
{
	if (ft_strcmp(current->cmds[0], "cd") == 0)
		ft_cd(current, built);
	else if (ft_strcmp(current->cmds[0], "pwd") == 0)
		ft_pwd(current, built);
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

void	ft_which_builtin(t_exe *current, t_env *built, t_b *b)
{
	if (current->output_file)
	{
		ft_redirec_builtin(current);
		ft_builtin(current, built, b);
		dup2(built->save_stdout, STDOUT_FILENO);
	}
	else if (current->output_file == NULL)
		ft_builtin(current, built, b);
}
