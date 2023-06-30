/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:25:39 by maheraul          #+#    #+#             */
/*   Updated: 2023/06/30 22:48:44 by maheraul         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H
# include "ft_printf.h"
# include "libft.h"
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>

// > 1
// >> 2
// < 3
// << 4
typedef struct t_list
{
	char			*file;
	int				type;
	struct t_list	*next;
}					t_list;

typedef struct t_cmd
{
	t_list			*lst;
	char			**arg;
	char			*cmd;
}					t_cmd;

typedef struct t_data
{
	int				nbcmd;
	char			**path;
	char			**tab;
	int				*pid;
	int				previous;
	int				fd[2];
}					t_data;

typedef struct t_var
{
	int				i;
	int				j;
	int				n;
	int				d;
	int				len;
	int				lentotal;
}					t_var;

int					ft_strlen_total(char const *str, char sep);

//utils
void				*ft_free_tab(char **tab);
void				printtab(char **tab);
void				printstruct(t_cmd *cmds);

//pipex
char				*write_path(char *cmd, t_data *data);
void				error_cmd(char *cmd);
void				*execute(t_data *data, t_cmd *cmd, char **env);
void				*free_pipex(t_data *data);
void				*ft_pipex(t_data *data, char **argv, char **env);
//redirection
int					redirection(t_data *data, int index, t_cmd *cmd);
void				invalid_fd(t_data *data, t_cmd *cmd, char *file);
void				openfiles(t_data *data, t_cmd *cmd);
//parse input
void				*parse_input(char *input);
//fill_cmd_struct.c
int					chevron_comp(char *str);
int					countarg(char **tab);
t_cmd				parse(char *str);
//lst.c
t_list				*ft_redirnew(char *file, int type);
void				ft_rediradd_back(t_list **lst, t_list *new);
void				ft_lst_clear(t_list **lst);
void				ft_printlist(t_list *list);

#endif