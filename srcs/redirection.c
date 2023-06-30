/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirection.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/14 02:49:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/01 00:29:53 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	invalid_fd(t_data *data, t_cmd *cmd, char *file)
{
	ft_printf("bash: %s: ", file);
	perror("");
	ft_free_tab(cmd->arg);
	ft_free_tab(data->tab);
	ft_lst_clear(&cmd->lst);
	if (data->previous != -1)
		close(data->previous);
	exit(1);
}

void	openfiles(t_data *data, t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;

	tmp = cmd->lst;
	while (tmp)
	{
		if (tmp->type == 1) // >
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_TRUNC, 0666);
		else if (tmp->type == 2) // >>
			fd = open(tmp->file, O_WRONLY | O_CREAT | O_APPEND, 0666);
		else if (tmp->type == 3) // <
			fd = open(tmp->file, O_RDONLY);
		if (fd == -1)
			invalid_fd(data, cmd, tmp->file);
		if (tmp->type == 1 || tmp->type == 2)
			dup2(fd, STDOUT_FILENO);
		else
			dup2(fd, STDIN_FILENO);
		close(fd);
		tmp = tmp->next;
	}
}

int	redirection(t_data *data, int index, t_cmd *cmd)
{
	if (index != data->nbcmd - 1) //ls cat grep
		dup2(data->fd[1], STDOUT_FILENO);
	if (index != 0) // cat grep lsblk
	{
		dup2(data->previous, STDIN_FILENO);
		close(data->previous);
		close(data->fd[0]);
		close(data->fd[1]);
		openfiles(data, cmd);
	}
	return (0);
}
