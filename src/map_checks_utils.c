/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/26 21:18:49 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/28 21:59:03 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"

int	get_width(char *row)
{
	int	i;

	i = 0;
	while (row && row[i] != '\0' && row[i] != '\n')
		i++;
	return (i);
}

void	save_components(t_data *data, int x, int y)
{
	t_map	*map;

	map = data->map;
	if (map->grid[y][x] == 'P')
	{
		(map->start)++;
		map->start_point = ft_pointnew(x, y);
		if (!map->start_point)
			print_error_exit("Memory allocation failed", NULL, data);
	}
	if (map->grid[y][x] == 'E')
	{
		(map->exit)++;
		map->exit_point = ft_pointnew(x, y);
		if (!map->exit_point)
			print_error_exit("Memory allocation failed", NULL, data);
	}
	if (map->grid[y][x] == 'C')
	{
		(map->moulinettes)++;
		save_moulinette_point(data, x, y);
	}
}

void	save_moulinette_point(t_data *data, int x, int y)
{
	t_map	*map;
	t_point	*point;

	point = ft_pointnew(x, y);
	if (!point)
		print_error_exit("Memory allocation failed", NULL, data);
	map = data->map;
	if (!map->moulinettes_arr)
	{
		map->moulinettes_arr = ft_calloc(1, sizeof(t_point *));
		if (!map->moulinettes_arr)
			print_error_exit("Memory allocation failed", NULL, data);
	}
	map->moulinettes_arr = ft_pointscat(map->moulinettes_arr, point);
	if (!map->moulinettes_arr)
		print_error_exit("Memory allocation failed", NULL, data);
}

void	fill_path(char **map, int x, int y)
{
	map[y][x] = '1';
	if (map[y - 1][x] != '1')
		fill_path(map, x, y - 1);
	if (map[y + 1][x] != '1')
		fill_path(map, x, y + 1);
	if (map[y][x - 1] != '1')
		fill_path(map, x - 1, y);
	if (map[y][x + 1] != '1')
		fill_path(map, x + 1, y);
}
