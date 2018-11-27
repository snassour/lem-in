/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 19:07:49 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 19:07:56 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int		add_to_paths(t_path *path, int num_path, t_map *map, int num_link)
{
	int		i;
	t_node	*tmp;

	path->paths_len[num_path] = map->start->links[num_link]->index + 1;
	i = sizeof(t_node *) * (path->paths_len[num_path] + 1);
	path->tab[num_path] = (t_node **)ft_memalloc(i);
	if (!path->tab[num_path])
		return (ERROR);
	tmp = map->start->links[num_link];
	i = -1;
	while (++i < path->paths_len[num_path] && tmp)
	{
		path->tab[num_path][i] = tmp;
		tmp = lemin_getnextnde(tmp);
	}
	path->tab[num_path][i] = NULL;
	path->paths_len[num_path] = i;
	return (TRUE);
}

void	lemin_end_output(int i, t_map *map, int fd)
{
	write(fd, "L", 1);
	ft_putnbr_fd(i, fd);
	write(fd, "-", 1);
	map->color == 1 ? write(fd, GREEN, ft_strlen(GREEN)) : 0;
	write(fd, map->end->name, ft_strlen(map->end->name));
	map->color == 1 ? write(fd, RESET, ft_strlen(RESET)) : 0;
	write(fd, "\n", 1);
}

int		lemin_algo(t_map *map)
{
	int	i;
	int	fd;

	i = 0;
	fd = map->write == 0 ? 1 : map->fd_write;
	if (map->start_end_connected == 1)
	{
		write(fd, map->anthill, map->display_len);
		write(fd, "\n", 1);
		while (++i <= map->nb_ants)
			lemin_end_output(i, map, fd);
		map->path_used ? lemin_display_path(map, -100, NULL) : NULL;
		return (0);
	}
	if (map->end == map->start && map->end != NULL)
		return (0 * write_start_equals_end(map, fd));
	if ((i = check_map(map)) == ERROR)
		return (ERROR);
	if ((i = find_paths(map)) == ERROR)
		return (ERROR);
	if ((i = save_paths(map) == ERROR))
		return (ERROR);
	return (i);
}

void	update_status(char *line, t_map *map, int *status, int *comment)
{
	if (line && *status == 1)
		*status = check_format_room(line);
	if (line && (*status == FALSE || *status == 2))
		*status = check_format_link(line, map, *status);
	if (line && *status == 3)
		*status = check_format_nb(line);
	*status = add_to_map(line, map, *status, *comment);
	*comment = check_comment(line, map);
}

int		main(int ac, char **av)
{
	char	*line;
	int		status;
	t_map	*map;
	int		comment;

	status = 3;
	if (!(map = (t_map *)ft_memalloc(sizeof(t_map))))
		return (-1 + 0 * write(2, "ERROR\n", 6));
	lemin_initmap(map);
	if (!map)
		return (-1 + 0 * write(2, "ERROR\n", 6));
	treat_argc_argv(map, ac, av);
	comment = 0;
	line = NULL;
	while (map && status && get_next_line(map->read * map->fd_read, &line) > 0)
		update_anthill1(&status, &comment, map, &line);
	close(map->read == 0 ? 0 : map->fd_read);
	get_next_line(map->read == 0 ? 0 : map->fd_read, &line);
	line ? ft_strdel(&line) : NULL;
	status = (map ? lemin_algo(map) : status);
	status == ERROR ? write(2, "ERROR\n", 6) : 0;
	map ? lemin_delmap(&map) : NULL;
	return (0);
}
