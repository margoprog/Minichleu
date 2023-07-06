/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_nofork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/06 00:59:43 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/06 03:16:04 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	invalid_fd_nofork(t_data *data, t_cmd *cmd, char *file)
{
	(void)data;
	ft_printf("bash: %s: ", file);
	perror("");
	(void)cmd;
	// ft_lst_clear(&cmd->lst);
	// ft_free_tab(cmd->arg);
	return (1);
}
int	openfiles_nofork(t_data *data, t_cmd *cmd)
{
	t_list	*tmp;
	int		fd;

	fd = -1;
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
			return (invalid_fd_nofork(data, cmd, tmp->file));
		if (tmp->type == 1 || tmp->type == 2)
			dup2(fd, STDOUT_FILENO);
		close(fd);
		tmp = tmp->next;
	}
	return (0);
}
