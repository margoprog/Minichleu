/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: motroian <motroian@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/08/11 23:21:07 by motroian          #+#    #+#             */
/*   Updated: 2023/08/31 18:29:44 by motroian         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	exit_hd(int sig)
{
	t_data	*data;
	int		i;

	data = starton();
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 2);
		i = -1;
		while (++i < data->nb_hd)
		{
			close(data->docs[i].fd[1]);
			close(data->docs[i].fd[0]);
			if (data->docs[i].del != NULL)
				free(data->docs[i].del);
		}
		free_arg(2, 1, 0, data->docs, data->str, data->env_copy);
		data->stop = true;
		exit(130);
	}
}

void	child_hd(char *del, int fd1, t_data *env, bool c)
{
	char	*line;

	signal(SIGINT, &exit_hd);
	while (1)
	{
		line = readline("> ");
		if (!line || !ft_strcmp(line, del))
			break ;
		if (c == false)
			line = ft_expandd(line, env);
		ft_putendl_fd(line, fd1);
		free(line);
	}
	close(fd1);
}
