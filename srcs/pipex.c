/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:40:18 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/06 03:15:55 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	*write_path(char *cmd, t_data *data)
{
	int		i;
	char	*path;

	i = 0;
	while (data->path && data->path[i] && cmd)
	{
		path = ft_strjoin(data->path[i], "/");
		if (!path)
			return ("");
		path = ft_realloc(path, cmd);
		if (access(path, F_OK | X_OK) != -1)
			return (path);
		free(path);
		i++;
	}
	return ("");
}

void	*execute(t_data *data, t_cmd *cmd, char **env)
{
	char	*path;

	if (cmd->cmd && ft_strchr(cmd->cmd, '/')) //et si nom de fichier contient /?
		path = cmd->cmd;
	else
	{
		data->path = path_recup(env);
		path = write_path(cmd->cmd, data);
		ft_freetab(data->path);
	}
	execve(path, cmd->arg, env);
	if (errno == 13)
		ft_printf("%s: permission denied\n", cmd->cmd);
	else if (cmd->cmd && ft_strchr(cmd->cmd, '/'))
		ft_printf("%s: no such file or directory \n", cmd->cmd);
	else
		error_cmd(cmd->cmd);
	return (NULL);
}

void	*free_pipex(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nbcmd)
	{
		waitpid(data->pid[i], NULL, 0);
		i++;
	}
	free(data->pid); //?
	close(data->fd[0]);
	return (NULL);
}

t_cmd	*get_cmd(t_data *data, t_cmd *cmd)
{
	*cmd = parse(data->tab[0]);
	if (!ft_strcmp(cmd->cmd, "cd"))
		return (cmd);
	if (!ft_strcmp(cmd->cmd, "echo"))
		return (cmd);
	printf("[%s] is not a builtin\n", cmd->cmd);
	ft_free_tab(cmd->arg);
	ft_lst_clear(&cmd->lst);
	return (NULL);
}

void	ft_parent(t_data *data, int i)
{
	close(data->fd[1]);
	if (i != 0)
		close(data->previous);
	data->previous = data->fd[0];
}

int	ft_nofork(t_data *data, t_cmd *cmd, char **env)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	if (!openfiles_nofork(data, cmd))
		ft_is_builtin(cmd, env);
	ft_free_tab(cmd->arg);
	ft_lst_clear(&cmd->lst);
	dup2(fd_tmp, STDOUT_FILENO);
	close(fd_tmp);
	close(data->fd[1]);
	close(data->fd[0]);
	free(data->pid);
	return (0);
}

void	*ft_pipex(t_data *data, char **argv, char **env)
{
	int		i;
	t_cmd	cmd;

	i = -1;
	while (++i < data->nbcmd)
	{
		if (pipe(data->fd) == -1)
			return (write(2, "pipe failed\n", 13), NULL);
		if (data->nbcmd == 1 && get_cmd(data, &cmd))
			return (ft_nofork(data, &cmd, env), NULL);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			free(data->pid);
			cmd = parse(argv[i]);
			redirection(data, i, &cmd);
			if (cmd.cmd && !ft_is_builtin(&cmd, env))
				execute(data, &cmd, env);
			ft_free_tab(data->tab);
			ft_free_tab(cmd.arg);
			ft_lst_clear(&cmd.lst);
			exit(127);
		}
		else if (data->pid[i] > 0)
			ft_parent(data, i);
	}
	return (free_pipex(data));
}
