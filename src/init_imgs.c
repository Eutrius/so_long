/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_imgs.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/27 11:36:26 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/27 21:59:01 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include "mlx.h"
#include "so_long.h"
#include <stddef.h>
#include <stdlib.h>

static void	create_img(t_data *data, char *path);
static void	save_img(t_data *data, t_img *img);
static void	init_more_imgs(t_data *data);

void	init_imgs(t_data *data)
{
	create_img(data, "./textures/idle1.xpm");
	create_img(data, "./textures/idle2.xpm");
	create_img(data, "./textures/idle3.xpm");
	create_img(data, "./textures/attack1.xpm");
	create_img(data, "./textures/attack2.xpm");
	create_img(data, "./textures/moulinette.xpm");
	create_img(data, "./textures/start.xpm");
	create_img(data, "./textures/stairs.xpm");
	create_img(data, "./textures/ground.xpm");
	create_img(data, "./textures/top_walls.xpm");
	create_img(data, "./textures/top_left_wall.xpm");
	create_img(data, "./textures/top_right_wall.xpm");
	create_img(data, "./textures/left_wall.xpm");
	create_img(data, "./textures/right_wall.xpm");
	create_img(data, "./textures/bottom_walls.xpm");
	create_img(data, "./textures/bottom_left_wall.xpm");
	create_img(data, "./textures/bottom_right_wall.xpm");
	init_more_imgs(data);
}

static void	init_more_imgs(t_data *data)
{
	create_img(data, "./textures/0.xpm");
	create_img(data, "./textures/1.xpm");
	create_img(data, "./textures/2.xpm");
	create_img(data, "./textures/3.xpm");
	create_img(data, "./textures/4.xpm");
	create_img(data, "./textures/5.xpm");
	create_img(data, "./textures/6.xpm");
	create_img(data, "./textures/7.xpm");
	create_img(data, "./textures/8.xpm");
	create_img(data, "./textures/9.xpm");
	create_img(data, "./textures/explosion1.xpm");
	create_img(data, "./textures/explosion2.xpm");
	create_img(data, "./textures/explosion3.xpm");
	create_img(data, "./textures/blackhole1.xpm");
	create_img(data, "./textures/blackhole2.xpm");
	create_img(data, "./textures/blackhole3.xpm");
	create_img(data, "./textures/blackhole4.xpm");
	create_img(data, "./textures/blackhole5.xpm");
}

static void	create_img(t_data *data, char *path)
{
	t_img	*img;

	img = ft_calloc(1, sizeof(t_img));
	if (!img)
		print_error_exit("Memory allocation failed", NULL, data);
	img->addr = mlx_xpm_file_to_image(data->process, path, &img->width,
			&img->height);
	if (!img->addr)
	{
		free(img);
		print_error_exit("Failed to create image: ", path, data);
	}
	save_img(data, img);
}

static void	save_img(t_data *data, t_img *img)
{
	int	i;

	i = 0;
	if (!data->imgs)
	{
		data->imgs = ft_calloc(40, sizeof(t_img *));
		if (!data->imgs)
			print_error_exit("Memory allocation failed", NULL, data);
	}
	while (data->imgs[i] != NULL)
		i++;
	data->imgs[i] = img;
}
