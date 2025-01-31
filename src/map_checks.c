/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_checks.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 15:08:12 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/28 21:59:13 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "so_long.h"
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

void	check_mapname(char *mapname)
{
	size_t	len;

	len = ft_strlen(mapname);
	while (1)
	{
		if (len < 5)
			break ;
		if (ft_strcmp(&mapname[len - 4], ".ber") != 0)
			break ;
		if (mapname[len - 5] == '/')
			break ;
		return ;
	}
	print_error_exit("Invalid map name: ", mapname, NULL);
}

int	check_map(t_data *data)
{
	char	**map;
	int		width;
	size_t	i;

	map = data->map->grid;
	i = 1;
	width = get_width(map[0]);
	if (width == 0)
		return (0);
	while (map[i] != NULL)
	{
		if (width != get_width(map[i]))
			return (0);
		i++;
	}
	data->map->width = width;
	data->map->height = i;
	return (1);
}

int	check_map_border(t_data *data)
{
	t_map	*map;
	int		i;

	map = data->map;
	i = 0;
	while (i < map->width)
	{
		if (map->grid[0][i] != '1')
			return (0);
		if (map->grid[map->height - 1][i] != '1')
			return (0);
		i++;
	}
	i = 0;
	while (i < map->height)
	{
		if (map->grid[i][0] != '1')
			return (0);
		if (map->grid[i][map->width - 1] != '1')
			return (0);
		i++;
	}
	return (1);
}

int	check_map_components(t_data *data)
{
	t_map	*map;
	int		x;
	int		y;

	y = 0;
	map = data->map;
	while (y < map->height)
	{
		x = 0;
		while (x < map->width)
		{
			if (ft_strchr("01CEP", map->grid[y][x]) == NULL)
				return (0);
			save_components(data, x, y);
			x++;
		}
		y++;
	}
	return (map->start == 1 && map->exit == 1 && map->moulinettes >= 1);
}

int	check_valid_path(t_data *data)
{
	char	**tmp_map;
	int		i;

	tmp_map = ft_strsdup(data->map->grid);
	if (!tmp_map)
		print_error_exit("Memory allocation failed", NULL, data);
	fill_path(tmp_map, data->map->start_point->x, data->map->start_point->y);
	i = 0;
	while (tmp_map[i] != NULL)
	{
		if (ft_strchr(tmp_map[i], 'E') != NULL)
			break ;
		if (ft_strchr(tmp_map[i], 'C') != NULL)
			break ;
		i++;
	}
	ft_free_strs(tmp_map);
	return (i == data->map->height);
}
