/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:40:18 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/13 00:45:58 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	func(void)
{
	static int	r;

	r = 12;
	return (r++);
}

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
		waitpid(data->pid[i++], NULL, 0);
	free(data->pid); //?
	close(data->fd[0]);
	return (NULL);
}

int		get_cmd(t_data *data)
{
	data->onecmd = parse(data->tab[0]);
	if (data->onecmd == NULL)
	{
		free_arg(1, 2, 1, data->pid, data->onecmd->arg, data->tab, &data->onecmd->lst),
			exit(1); //quel exit pout malloc foire
	}
	if (!data->onecmd->cmd)
		return (0);
	if (!ft_strcmp(data->onecmd->cmd, "cd"))
		return (1);
	if (!ft_strcmp(data->onecmd->cmd, "echo"))
		return (1);
	printf("[%s] is not a builtin\n", data->onecmd->cmd);
	free_arg(0, 1, 1, data->onecmd->arg, &data->onecmd->lst);
	return (0);
}

int	ft_nofork(t_data *data, t_cmd *cmd, char **env)
{
	int	fd_tmp;

	fd_tmp = dup(STDOUT_FILENO);
	if (!openfiles_nofork(data, cmd))
		ft_is_builtin(cmd, env);
	dup2(fd_tmp, STDOUT_FILENO);
	close(fd_tmp);
	return (0);
}

void	ft_enfant(t_data *data, char **argv, int i, char **env)
{
	t_cmd	*cmd = NULL;

	free(data->pid);
	cmd = parse(argv[i]);
	if (cmd == NULL)
	{
		free_arg(0, 2, 1, cmd->arg, data->tab, &cmd->lst);
		exit(1);
	}
	redirection(data, i, cmd);
	if (cmd->cmd && !ft_is_builtin(cmd, env))
		execute(data, cmd, env);
	free_arg(0, 2, 1, cmd->arg, data->tab, &cmd->lst);
	exit(127);

}

void	*ft_pipex(t_data *data, char **argv, char **env)
{
	int		i;

	i = -1;
	if (data->nbcmd == 1 && get_cmd(data))
	{

		return (ft_nofork(data, data->onecmd, env), NULL);
	}
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

void	ft_parent(t_data *data, int i)
{
	close(data->fd[1]);
	if (i != 0)
		close(data->previous);
	data->previous = data->fd[0];
}


int test()
{
	int r = blabla();
	data->valeur = r;
	return (0);
}

void	func()
{
	printf("%i\n", data->valeur);
}