/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/30 22:21:07 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/30 22:23:27 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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

void	ft_lst_clear(t_list **lst)
{
	t_list	*temp;
	t_list	*copylst;

	if ((*lst) == NULL)
		return ;
	copylst = (*lst);
	while (copylst)
	{
		temp = copylst->next;
		free(copylst->file);
		free(copylst);
		copylst = temp;
	}
	(*lst) = NULL;
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