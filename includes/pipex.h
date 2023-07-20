/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: maheraul <maheraul@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/20 22:25:39 by maheraul          #+#    #+#             */
/*   Updated: 2023/07/18 20:21:10 by maheraul         ###   ########.fr       */
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
# include <stdarg.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/time.h>
# include <sys/wait.h>

// > 1
// >> 2
// < 3
// << 4
typedef struct t_doc
{
	char			*del;
	int				fd[2];
}					t_doc;

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
	int				fork;
	int				previous;
	int				fd[2];

	char			**env;
	t_cmd			*onecmd;

	int				nb_hd;
	t_doc			*docs;
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

typedef int			(*t_builtin)(char **arg, char **env);

t_data				*starton(void);
int					ft_strlen_total(char const *str, char sep);

//utils
void				*ft_free_tab(char **tab);
void				printtab(char **tab);
void				printstruct(t_cmd *cmds);
void				error_cmd(char *cmd);
//main.c
char				**path_recup(char **env);
//pipex
char				*write_path(char *cmd, t_data *data);
void				*execute(t_data *data, t_cmd *cmd, char **env);
void				ft_parent(t_data *data, int i);
void				*ft_pipex(t_data *data, char **argv, char **env);
//exec
char				*write_path(char *cmd, t_data *data);
void				*execute(t_data *data, t_cmd *cmd, char **env);
int					get_cmd(t_data *data);
//redirection
void				redirection(t_data *data, int index, t_cmd *cmd);
void				invalid_fd(t_data *data, t_cmd *cmd, char *file);
void				openfiles(t_data *data, t_cmd *cmd);
void				close_heredocs(t_doc *doc, int limit);
int					quelpipe(t_data *data, t_doc *doc, char *file);

//parse input
void				*parse_input(char *input);
//fill_cmd_struct.c
int					chevron_comp(char *str);
int					countarg(char **tab);
t_cmd				*parse(char *str);
//lst.c
t_list				*ft_redirnew(char *file, int type);
void				ft_rediradd_back(t_list **lst, t_list *new);
void				ft_lst_clear(t_list **lst);
void				ft_printlist(t_list *list);
//builtin
int					ft_is_builtin(t_cmd *cmd, char **env);
int					ft_is_builtin_vrmnt(char *str);
int					ft_exit(char **arg, char **env);
//echo.c
int					ft_echo(char **arg, char **env);
//pwd.c
int					ft_pwd(char **arg, char **env);
//cd.c
int					ft_cd(char **arg, char **env);
//redirnofork
int					openfiles_nofork(t_data *data, t_cmd *cmd);
int					invalid_fd_nofork(t_data *data, t_cmd *cmd, char *file);
//free.c
void				*free_arg(int str, int tab, int lst, ...);
void				*free_pipex(t_data *data);
//heredoc
void				*here_doc(t_data *data, char *str);

#endif