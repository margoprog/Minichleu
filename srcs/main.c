/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/12 22:37:45 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/29 01:15:39 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

char	**path_recup(char **env)
{
	int	i;

	i = 0;
	while (env && env[i])
	{
		if (!ft_strncmp(env[i], "PATH=", 5))
			return (ft_split(env[i] + 5, ':'));
		i++;
	}
	return (NULL);
}

int	init_struct(t_data *data, int argc, char **env)
{
	(void)env;
	(void)argc;
	data->previous = -1;
	data->pid = malloc(sizeof(int) * data->nbcmd);
	if (!data->pid)
		return (ft_free_tab(data->tab), 1);
	return (0);
}

void	printtab(char **tab)
{
	for (int i = 0; tab[i]; i++)
		fprintf(stderr, "[%i]{%s}\n", i, tab[i]);
}

int	main(int argc, char **argv, char **env)
{
	//static t_data	data = {0};
	char			*input;
	(void)argv;
	(void)argc;
	(void)env;

	while (1)
	{
		input = readline("minisheu> ");
		if (!input)
			exit (1);
		add_history(input);
		// yassine
		printf("aVANT %s\n", input);
		input = parse_input(input);
		printf("APREA %s\n", input);
		free(input);
		// data.tab = ft_split(input, '|');
		// data.nbcmd = ft_strlen_total(input, '|');
		// free(input);
		// if (init_struct(&data, argc, env))
			// return (1);
		// ft_pipex(&data, data.tab, env);
		// ft_free_tab(data.tab);
	}
	return (0);
}
