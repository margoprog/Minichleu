/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_cmd_struct.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:40:06 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/25 18:51:00 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	chevron_comp(char *str)
{
	if (!ft_strcmp(str, ">"))
		return (1);
	if (!ft_strcmp(str, ">>"))
		return (2);
	if (!ft_strcmp(str, "<"))
		return (3);
	if (!ft_strcmp(str, "<<"))
		return (4);
	return (0);
}

int	countarg(char **tab)
{
	int	size;
	int	i;

	size = 0;
	i = 0;
	while (tab[i])
	{
		if (chevron_comp(tab[i]))
			i++;
		else
			size++;
		i++;
	}
	return (size);
}

t_cmd	*parse(char *str)
{
	static t_cmd	cmds = {0};
	t_list			*lst;
	char			**input;
	int				j;
	int				i;

	j = 0;
	i = 0;
	lst = 0;
	input = ft_split(str, ' ');
	if (!input)
		return (NULL);
	cmds.arg = ft_calloc(sizeof(char *), countarg(input) + 1);
	if (!cmds.arg)
		return (free(input), NULL);
	int v = 0;
	while (input[i])
	{
		int r = chevron_comp(input[i]);
		if (r)
		{
			ft_rediradd_back(&lst, ft_redirnew(ft_strdup(input[i + 1]), r, v));
			if (r == 4)
				v++;
			i++;
		}
		else
			cmds.arg[j++] = ft_strdup(input[i]);
		i++;
	}
	ft_freetab(input);
	cmds.cmd = cmds.arg[0];
	cmds.lst = lst;
	//printstruct(&cmds);
	return (&cmds);
}
