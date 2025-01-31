/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jyriarte <jyriarte@student.42roma.it>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/21 20:28:41 by jyriarte          #+#    #+#             */
/*   Updated: 2025/01/29 17:39:38 by jyriarte         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

# define MAX_WIDTH 30
# define MAX_HEIGHT 15
# define TRANSPARENT_COLOR 0xFF00FF
# define GLOBAL_FRAMERATE 3000
# define PLAYER_FRAMERATE 10
# define BLACK_HOLE_FRAMERATE 1
# define EXPLOSION_FRAMERATE 1500
# define BH_SPEED 16

# include "libft.h"

typedef struct s_map	t_map;
typedef struct s_img	t_img;
typedef enum e_imgs		t_imgname;
typedef struct s_entity	t_entity;

typedef struct s_data
{
	void				*process;
	void				*window;

	int					finished;
	int					moves;
	t_point				*moves_location;
	t_point				*explosion;

	t_map				*map;
	t_img				**imgs;

	t_entity			*player;
	t_entity			*exit;
	t_entity			*black_hole;
	t_entity			**moulinettes;

}						t_data;

typedef struct s_map
{
	char				**grid;
	int					start;
	int					exit;
	t_point				*start_point;
	t_point				*exit_point;
	int					moulinettes;
	t_point				**moulinettes_arr;
	int					width;
	int					height;

}						t_map;

typedef struct s_img
{
	void				*addr;
	int					width;
	int					height;
}						t_img;

typedef struct s_entity
{
	t_img				*img;
	t_point				*location;
	int					mirror;

}						t_entity;

typedef enum e_imgs
{
	player0,
	player1,
	player2,
	player_attack,
	player_attacked,
	moulinette,
	start,
	stairs,
	ground,
	wall,
	top_left_wall,
	top_right_wall,
	left_wall,
	right_wall,
	bottom_wall,
	bottom_left_wall,
	bottom_right_wall,
	num0,
	num1,
	num2,
	num3,
	num4,
	num5,
	num6,
	num7,
	num8,
	num9,
	explosion1,
	explosion2,
	explosion3,
	blackhole1,
	blackhole2,
	blackhole3,
	blackhole4,
	blackhole5,
}						t_imgname;

void					init_data(t_data *data, char *mapname);
void					init_map(t_data *data, char *mapname);
void					init_imgs(t_data *data);
void					init_moves(t_data *data);

void					free_data(t_data *data);

void					check_mapname(char *mapname);
int						check_map(t_data *data);
int						check_map_border(t_data *data);
int						check_map_components(t_data *data);
int						check_valid_path(t_data *data);

void					print_error_exit(char *error, char *name, t_data *data);

int						get_abs(int num);
int						get_width(char *row);
void					fill_path(char **map, int x, int y);
void					save_components(t_data *data, int x, int y);
void					save_moulinette_point(t_data *data, int x, int y);

void					render_all(t_data *data);
void					render_map(t_data *data);
void					render_player(t_data *data);
void					render_moulinettes(t_data *data);
void					render_black_hole(t_data *data);
void					render_exit(t_data *data);
void					render_moves(t_data *data);
void					render_explosion(t_data *data);
void					render_entity(t_data *data, t_entity *entity);
void					render_tile(t_data *data, t_imgname name, int x, int y);
void					render_img(t_data *data, t_img *img, t_point *location,
							int mirror);

void					hooks(t_data *data);
void					move_player(t_data *data, int x, int y);
void					player_won(t_data *data);
void					player_lost(t_data *data);

#endif
