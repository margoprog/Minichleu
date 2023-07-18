/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:37:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/16 01:33:10 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	init_struct(t_data *data, char **env)
{
	data->env = env;
	data->fork = 1;
	data->previous = -1;
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		return (ft_free_tab(data->tab), 1);
	return (0);
}

t_data	*starton(void)
{
	static t_data	data = {0};

	return (&data);
}

int	main(int argc, char **argv, char **env)
{
	t_data	*data;
	char	*input;

	data = starton();
	(void)argv;
	(void)argc;
	(void)env; //test
	while (1)
	{
		input = readline("minisheu> ");
		if (!input)
			exit(1);
		if (!*input)
			continue;
		add_history(input);
		input = parse_input(input);
		if (!input)
			exit(1);
		// yassine
		if (here_doc(data, input))
			return (1);
		data->tab = ft_split(input, '|');
		data->nbcmd = ft_strlen_total(input, '|');
		free(input);
		if (init_struct(data, env))
			return (1);
		ft_pipex(data, data->tab, env);
		for (int i = 0; i < data->nb_hd; i++)
		{
			free(data->docs[i].del);
			close(data->docs[i].fd[0]);
		}
		if (data->nb_hd)
			free(data->docs);
		// close_heredocs(data->docs, data->nb_hd);
		ft_free_tab(data->tab);
	}
	return (0);
}
