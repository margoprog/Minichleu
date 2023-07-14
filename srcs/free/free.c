/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 18:09:30 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/14 02:12:15 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*free_arg(int str, int tab, int lst, ...)
{
	va_list	arg;

	va_start(arg, lst);
	while (str > 0)
	{
		free((char *)va_arg(arg, char *));
		str--;
	}
	while (tab > 0)
	{
		ft_free_tab((char **)va_arg(arg, char **));
		tab--;
	}
	while (lst > 0)
	{
		ft_lst_clear((t_list **)va_arg(arg, t_list **));
		lst--;
	}
	return (va_end(arg), NULL);
}

void	*free_pipex(t_data *data)
{
	int	i;

	i = 0;
	close_heredocs(data->docs, data->nb_hd);
	while (i < data->nbcmd)
		waitpid(data->pid[i++], NULL, 0);
	free(data->pid);
	close(data->fd[0]);
	return (NULL);
}
