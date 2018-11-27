/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: snassour <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/09/05 18:11:46 by snassour          #+#    #+#             */
/*   Updated: 2018/09/05 18:11:48 by snassour         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

void	lemin_display_path(t_map *map, int min, t_path *path)
{
	int		i;
	int		fd;

	i = -1;
	fd = map->write == 0 ? 1 : map->fd_write;
	ft_putstr_fd(YELLOW, fd);
	ft_putendl_fd("\n\nPATH USED :", fd);
	ft_putstr_fd(RESET, fd);
	ft_putstr_fd(MAGENTA, fd);
	ft_putstr_fd("START = ", fd);
	ft_putstr_fd(map->start->name, fd);
	ft_putstr_fd(RESET, fd);
	ft_putstr_fd(" -> ", fd);
	while (path && ++i < path->paths_len[min] - 1 && min != -100)
	{
		ft_putstr_fd(path->tab[min][i]->name, fd);
		ft_putstr_fd(" -> ", fd);
	}
	ft_putstr_fd(GREEN, fd);
	ft_putstr_fd(map->end->name, fd);
	ft_putstr_fd(" = END", fd);
	ft_putendl_fd(RESET, fd);
}

void	treat_argc_argv_write(t_map *map, int ac, char **av, int i)
{
	if (i + 1 < ac)
	{
		map->fd_write = open(av[i + 1], O_CREAT | O_WRONLY, 0600);
		if (map->fd_write < 0)
		{
			write(2, "Writing on standard input\n", 26);
			write(2, "Couldn't create file named : ", 29);
			write(2, av[i + 1], ft_strlen(av[i + 1]));
			write(2, "\n", 1);
		}
		else
			map->write = 1;
	}
	else
		write(1, "No file provided, writing on standard input\n", 44);
}

void	treat_argc_argv_read(t_map *map, int ac, char **av, int i)
{
	if (i + 1 < ac)
	{
		map->fd_read = open(av[i + 1], O_RDONLY);
		if (map->fd_read < 0)
		{
			write(2, "Reading from standard input\n", 28);
			write(2, "Couldn't open file named : ", 27);
			write(2, av[i + 1], ft_strlen(av[i + 1]));
			write(2, "\n", 1);
		}
		else
			map->read = 1;
	}
}

void	treat_argc_argv_help(t_map *map)
{
	if (map->write > 0)
		close(map->fd_write);
	if (map->read > 0)
		close(map->fd_read);
	lemin_delmap(&map);
	ft_putstr("\nUsage:\t./lemin [OPTIONS [FILES]]\n\n \
	\rGoal : move all the ants from start to end\n \
	\rInput format:\n \
	\r\tComments :\t#\n \
	\r\tStart :\t\t##start\n \
	\r\tEnd :\t\t##end\n \
	\r\tAnts number :\tpositive integer - one line\n \
	\r\tRooms :\t\troom_name first_coordinate second_coordinate\n \
	\r\tLinks :\t\troom_name_one-room_name_two\n \
	\rWhen you finish typing the rooms, then you can enter the links.\n\
	\rThere is no coming back.\n\n \
	\rOptions:\n \
	\r--help\t\tDisplays help\n \
	\r-c\t\nHelps visualize the ants arrival at the finish line\n \
	\r--path\t\tPrints the path followed by the ants at the end\n \
	\r--read file\tReads anthill from file.\n \
	\rIF file not opened, reads from standard input\n \
	\r--write file\tWrites solution in file.\n \
	\rIF file creation fails, writes on the standard output\n");
}

void	treat_argc_argv(t_map *map, int ac, char **av)
{
	int		i;

	if (ac == 1)
		return ;
	i = 1;
	while (i < ac && av[i])
	{
		if (ft_strcmp(av[i], "-c") == 0)
			map->color = 1;
		if (ft_strcmp(av[i], "--path") == 0)
			map->path_used = 1;
		if (ft_strcmp(av[i], "--read") == 0)
			treat_argc_argv_read(map, ac, av, i);
		if (ft_strcmp(av[i], "--write") == 0)
			treat_argc_argv_write(map, ac, av, i);
		if (ft_strcmp(av[i], "--help") == 0)
		{
			treat_argc_argv_help(map);
			exit(3);
		}
		++i;
	}
}
