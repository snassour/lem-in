/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 17:36:07 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 17:36:21 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include <stdio.h>
# include <libft.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>
# include <fcntl.h>
# define OTHER 3
# define END 2
# define START 1
# define RPATH 1
# define WPATH 0
# define COM_END 5
# define COM_START 6
# define RED		"\x1b[31m"
# define GREEN	"\x1b[32m"
# define YELLOW	"\x1b[33m"
# define BLUE	"\x1b[34m"
# define MAGENTA	"\x1b[35m"
# define CYAN	"\x1b[36m"
# define RESET "\x1b[0m"
# define NOT_WAITING 29
# define WAITING 30
# define SET 31
# define NOT_SET 32

struct	s_node
{
	char			*name;
	int				x;
	int				y;
	int				changed;
	int				nb_paths;
	int				index;
	int				status;
	int				passe_par_la;
	struct s_node	**links;
	int				nb_links;
	int				disp_index;
	int				ant_curr;
	int				ant_prec;
	struct s_node	*next;
};

typedef struct s_node	t_node;

struct	s_path
{
	t_node	***tab;
	int		nb_paths;
	int		*paths_len;
	int		nb_dependant_paths;
	int		*dependant_paths_index;
};

typedef struct s_path	t_path;

struct	s_map
{
	t_node	**tab;
	t_node	*begin_list;
	t_node	*start;
	t_node	*end;
	t_path	*paths;
	int		nb_nde;
	int		nb_ants;
	int		ants_at_start;
	int		ants_at_end;
	int		start_end_connected;
	char	*anthill;
	int		real_len;
	int		display_len;
	int		color;
	int		fd_read;
	int		fd_write;
	int		read;
	int		write;
	int		path_used;
	int		waiting_for_start;
	int		waiting_for_end;
	int		start_set;
	int		end_set;
};

typedef struct s_map	t_map;

int		lemin_isint(char *str);
t_node	**transform_graph(t_node *begin_list, int nb_nde);
void	lemin_delnode(t_node **node);
void	lemin_modify(t_node *lst, char *name, int x, int y);
t_node	*lemin_createnode(char *name, int x, int y, t_node *lst);
t_node	*lemin_initnode(char *name, int x, int y);
void	lemin_initmap(t_map *map);
void	lemin_lstnddel(t_node **begin_list);
void	lemin_tabnddel(t_node ***tab);
void	lemin_delmap(t_map **map);
int		lemin_valid_name(char *name);
int		check_format_room(char *line);
int		check_link_name(char *name, t_map *map);
int		check_format_link(char *line, t_map *map, int status);
int		check_format_nb(char *line);
void	add_start_end(t_map *map, t_node *n, int comment);
int		add_room(char *line, t_map *map, int comment);
void	lemin_appendtab(t_node ***new, t_node *old, t_node *added);
int		create_link(t_node *n1, t_node *n2);
int		add_link(char *line, t_map *map);
int		add_nb_ants(char *line, t_map *map);
int		add_to_map(char *line, t_map *map, int status, int comment);
int		check_comment(char *line, t_map *map);
int		check_links(t_node *m, t_node *n);
int		check_map(t_map *map);
int		get_paths(t_node *end, t_node *st, int depth);
int		find_paths(t_map *map);
t_path	*lemin_createpath(t_map *map);
void	lemin_destroypath(t_path **path);
t_node	*lemin_getnextnde(t_node *tmp);
int		add_to_paths(t_path *path, int num_path, t_map *map, int num_link);
void	lemin_finish_ants(t_map *map, int min, t_path *path);
void	move_ants(int ant, int min, t_path *path);
void	lemin_display_path(t_map *map, int min, t_path *path);
void	lemin_playants(t_map *map, t_path *path);
int		save_paths(t_map *map);
int		lemin_algo(t_map *map);
int		add_anthill(t_map *map, char *line);
void	treat_argc_argv(t_map *map, int ac, char **av);
void	update_status(char *line, t_map *map, int *status, int *comment);
int		write_start_equals_end(t_map *map, int fd);
void	update_anthill1(int *status, int *comment, t_map *map, char **line);
void	set_link_nodes(t_node **n1, t_node **n2, char **s, t_node *og);

#endif
