/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/28 01:27:25 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/30 22:18:16 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	*ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (NULL);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

void	printtab(char **tab)
{
	for (int i = 0; tab[i]; i++)
		fprintf(stderr, "[%i]{%s}\n", i, tab[i]);
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
	ft_printlist(cmds->lst);
}
