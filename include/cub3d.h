/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:41:34 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/06/05 15:34:07 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# define NUM_C "Error\nWrong arguments for the sky color (just need numbers)\n"
# define ARG_C "Error\nWrong number of arguments for the sky color\n"
# define NUM_F "Error\nWrong arguments for the floor color (just need numbers)\n"
# define ARG_F "Error\nWrong number of arguments for the floor color\n"
# define RGB "Error\nWrong arguments (need numbers rgb between 0 and 255)\n"
# define IMG "Error\nImage couldn't be loaded\n"
# define MLX_FAIL "Error\nMlx failed to init\n"

# define SCREENWIDTH 960
# define SCREENHEIGHT 640
# define RSPEED 0.03

# include "libft.h"
# include "mlx.h"
# include <X11/Xlib.h>
# include <X11/keysym.h>
# include <fcntl.h>
# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>

typedef struct s_map
{
	int				size;
	int				*data;
	char			**file_content;
	char			**map;
	int				**map_int;
	char			*north;
	char			*south;
	char			*west;
	char			*east;
	char			*celestial;
	char			**celestial_tab;
	char			*floor;
	char			**floor_tab;

}					t_map;

typedef struct s_tex
{
	void			*img;
	int				height;
	int				width;
	unsigned int	*data;
	int				bpp;
	int				size_line;
	int				endian;
}					t_tex;

typedef struct s_data
{
	struct s_tex	n_wall;
	struct s_tex	s_wall;
	struct s_tex	e_wall;
	struct s_tex	w_wall;
	struct s_tex	render;
	struct s_map	*map;

	int				floor;
	int				ceiling;

	int				forward;
	int				backward;
	int				left;
	int				right;
	int				r_cam;
	int				l_cam;
	double			sp;

	double			wallx;
	int				tex_x;

	void			*mlx;
	void			*win;

	double			pos_x;
	double			pos_y;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;

	double			cam_x;
	double			raydir_x;
	double			raydir_y;

	int				mapx;
	int				mapy;

	double			s_dist_x;
	double			s_dist_y;

	double			delt_distx;
	double			delt_disty;
	double			perpwalldist;

	int				step_x;
	int				step_y;

	int				hit;
	int				side;

	int				line_h;
	int				draw_start;
	int				draw_end;
	int				color;
}					t_data;

/////////////////// Parsing ///////////////////
// utils_tab.c
void				print_tab(char **tab);
int					ft_tablen(char **tab);

// utils_parsing.c
int					check_caracter(t_map *map);
int					column_max_min(t_map *map, int i);
int					ft_strlen_bis(char *s);
int					ft_is_last(char **tab, int i);
int					ft_empty(char *str);

// file_to_char.c
int					len_file(char *file);
char				**file_to_tab(char *file, int i, char **file_content);
int					parsing(char *file);

// set_struct_map.c
int					set_map(t_map *map, int i);
int					set_newsfc(t_map *map, char *line);
int					search_newsfc2(t_map *map, int i);
int					search_newsfc(t_map *map);
int					already_set(t_map *map, char **split);

// verif_good_map.c
int					check_line(t_map *map);
int					check_up(t_map *map, int i, int j);
int					check_down(t_map *map, int i, int j);
int					check_column(t_map *map);
int					check_floor_empty(t_map *map);

// free
void				free_tab(char **tab);
void				free_tab_int(int **tab);
void				free_mlx(t_data *data);
void				free_map(t_map *map);

// check_player
int					check_player(t_map *map);

// verif_rgb.c
int					verif_rgb(t_map *map);
int					convert_rgb(char **tab);
int					mlx_start(t_map *map);

/////////////////// Raycasting ///////////////////

// Raycasting.c
t_tex				ft_texture(t_data *data);
void				img_draw(int x, int start, int end, t_data *data);
void				ft_before_dda(t_data *data);
void				ft_dda(t_data *data);
void				ft_draw(t_data *data);

// Moves.c
void				forward_backward(t_data *data, int key);
void				left_right(t_data *data, int key);
void				ft_right(t_data *data, int key);
void				ft_left(t_data *data, int key);
int					key_press(int key, t_data *data);
int					key_release(int key, t_data *data);
int					ft_move(t_data *data);

// Utils.c
int					init_textures(t_data *data);
void				ft_set(t_data *data, double dir_x, double dir_y,
						double plane_x);
int					get_pos_player(t_map *map, t_data *data);
void				make_tab(char **tab_c, int **tab, int i, int j);
int					**tab_char_to_tab_int(char **tab_c);

#endif