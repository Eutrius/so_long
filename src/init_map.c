/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:08:42 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/26 22:46:18 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

static void	init_grid(t_data *data, int fd);
static void	validate_map(t_data *data, char *mapname);

void	init_map(t_data *data, char *mapname)
{
	int	fd;

	check_mapname(mapname);
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		print_error_exit("Memory allocation failed", NULL, data);
	fd = open(mapname, O_RDONLY);
	if (fd == -1)
		print_error_exit("Cannot open map: ", mapname, data);
	init_grid(data, fd);
	validate_map(data, mapname);
}

static void	validate_map(t_data *data, char *mapname)
{
	if (!check_map(data))
		print_error_exit("Invalid map: not a rectangle: ", mapname, data);
	if (data->map->width > MAX_WIDTH || data->map->height > MAX_HEIGHT)
		print_error_exit("Invalid map: map too big: ", mapname, data);
	if (!check_map_border(data))
		print_error_exit("Invalid map: not surrounded by walls: ", mapname,
			data);
	if (!check_map_components(data))
		print_error_exit("Invalid map: wrong components: ", mapname, data);
	if (!check_valid_path(data))
		print_error_exit("Invalid map: no valid path: ", mapname, data);
}

static void	init_grid(t_data *data, int fd)
{
	char	*row;
	char	**map;

	map = ft_calloc(1, sizeof(char *));
	if (!map)
	{
		close(fd);
		print_error_exit("Memory allocation failed", NULL, data);
	}
	while (1)
	{
		row = get_next_line(fd);
		if (!row)
			break ;
		map = ft_strscat(map, row);
		if (!(*map))
		{
			close(fd);
			free(row);
			print_error_exit("Memory allocation failed", NULL, data);
		}
	}
	close(fd);
	data->map->grid = map;
}
