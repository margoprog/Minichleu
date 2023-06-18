/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:40:18 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/19 00:47:23 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_recup(char **env);

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

void	error_cmd(char *cmd)
{
	if (!cmd)
		ft_printf(" : command not found\n");
	else
		ft_printf("%s: command not found\n", cmd);
	return ;
}

void	*execute(t_data *data, char *arg, char **env)
{
	char	**cmd;
	char	*path;

	cmd = ft_split(arg, ' ');
	if (!cmd)
		return (NULL);
	if (cmd[0] && ft_strchr(cmd[0], '/'))
		path = cmd[0];
	else
	{
		data->path = path_recup(env);
		path = write_path(cmd[0], data);
		ft_freetab(data->path);
	}
	execve(path, cmd, env);
	if (errno == 13)
		ft_printf("%s: permission denied\n", cmd[0]);
	else if (cmd[0] && ft_strchr(cmd[0], '/'))
		ft_printf("%s: no such file or directory \n", cmd[0]);
	else
		error_cmd(cmd[0]);
	ft_free_tab(cmd);
	ft_free_tab(data->tab);
	exit(1);
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
	free(data->pid);
	close(data->fd[0]);
	return (NULL);
}

int chevron_comp(char *str)
{
	if(!ft_strcmp(str, ">"))
		return(1);
	if(!ft_strcmp(str, ">>"))
		return(2);
	if(!ft_strcmp(str, "<"))
		return(3);
	if(!ft_strcmp(str, "<<"))
		return(4);
	return(0);
}
t_list	*ft_redirnew(char *file, int type)
{
	t_list	*lst;

	lst = malloc(sizeof(t_list));
	if (!lst)
		return (NULL);
	lst->file = file;
	lst->type = type;
	lst->next = NULL;
	return (lst);
}
void	ft_rediradd_back(t_list **lst, t_list *new)
{
	t_list	*temp;

	if (!(*lst))
		*lst = new;
	else
	{
		temp = *lst;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = new;
	}
}
void	ft_printlist(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp != NULL)
	{
		fprintf(stderr, "[%i]{%s}\n", tmp->type, tmp->file);
		tmp = tmp->next;
	}
}
void	printstruct(t_cmd *cmds)
{
	for (int i = 0; cmds->arg[i]; i++)
	{
		if (i == 0)
		{
			fprintf(stderr, "CMD = {%s}\n", cmds->arg[0]);
			continue ;
		}
		if (i == 1)
			fprintf(stderr, "ARGS =");
		fprintf(stderr, "[%s]", cmds->arg[i]);
	}
	fprintf(stderr, "\n");
	ft_printlist(cmds->lc);

}

t_cmd	parse(char *str)
{
	t_cmd cmds;
	t_list *lst;
	char **input;
	int j;
	int i;

	j = 0;
	i = 0;
	lst = 0;
	input = ft_split(str, ' ');
	while(input[i])
	{
		if(chevron_comp(input[i]))
		{
			ft_rediradd_back(&lst, ft_redirnew(ft_strdup(input[i + 1]), chevron_comp(input[i])));
			i++;
		}
		else
			cmds.arg[j++] = ft_strdup(input[i]);
		i++;
	}
	cmds.cmd = cmds.arg[0];
	cmds.arg[j] = 0;
	cmds.lc = lst;
	printstruct(&cmds);
	return(cmds);

}

void	*ft_pipex(t_data *data, char **argv, char **env)
{
	int	i;
	t_cmd	cmd;

	i = -1;
	while (++i < data->nbcmd)
	{
		if (pipe(data->fd) == -1)
			return (write(2, "pipe failed\n", 13), NULL);
		data->pid[i] = fork();
		if (data->pid[i] == 0)
		{
			free(data->pid);
			cmd = parse(argv[i]);
			redirection(data, i, argv);
			execute(data, argv[i], env);
		}
		else if (data->pid[i] > 0)
		{
			close(data->fd[1]);
			if (i != 0)
				close(data->previous);
			data->previous = data->fd[0];
		}
	}
	return (free_pipex(data));
}
