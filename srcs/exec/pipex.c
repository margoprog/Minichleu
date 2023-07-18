/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:40:18 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/16 03:37:21 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	ft_nofork(t_data *data, t_cmd *cmd, char **env)
{
	int	fd_tmp;

	free(data->pid);
	fd_tmp = dup(STDOUT_FILENO);
	int fd_tmp2 = dup(STDIN_FILENO);
	if (!openfiles_nofork(data, cmd))
	{
		fprintf(stderr, "je suis la!\n");
		ft_is_builtin(cmd, env);
	}
	dup2(fd_tmp, STDOUT_FILENO);
	dup2(fd_tmp2, STDOUT_FILENO);
	close(fd_tmp);
	close(fd_tmp2);
	free_arg(0, 1, 1, cmd->arg, &cmd->lst);
	return (0);
}

void	ft_enfant(t_data *data, char **argv, int i, char **env)
{
	t_cmd	*cmd;

	cmd = NULL;
	free(data->pid);
	cmd = parse(argv[i]);
	if (cmd == NULL)
	{
		close_heredocs(data->docs, data->nb_hd);
		free_arg(0, 2, 1, cmd->arg, data->tab, &cmd->lst);
		exit(1);
	}
	redirection(data, i, cmd);
	if (cmd->cmd && !ft_is_builtin(cmd, env))
		execute(data, cmd, env);
	free_arg(0, 2, 1, cmd->arg, data->tab, &cmd->lst);
	exit(127);
}

void	ft_parent(t_data *data, int i)
{
	close(data->fd[1]);
	if (i != 0)
		close(data->previous);
	data->previous = data->fd[0];
}

void	*ft_pipex(t_data *data, char **argv, char **env)
{
	int	i;

	i = -1;
	if (data->nbcmd == 1 && get_cmd(data))
		return (ft_nofork(data, data->onecmd, env), NULL);
	while (++i < data->nbcmd)
	{
		if (pipe(data->fd) == -1)
			return (write(2, "pipe failed\n", 13), NULL);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
			ft_enfant(data, argv, i, env);
		else if (data->pid[i] > 0)
			ft_parent(data, i);
	}
	return (free_pipex(data));
}
