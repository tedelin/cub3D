/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_rgb.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tedelin <tedelin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/24 16:08:59 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/06/01 22:11:49 by tedelin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	verif_rgb(t_map *map)
{
	int	i;

	i = -1;
	map->celestial_tab = ft_splitnum(map->celestial, ',');
	map->floor_tab = ft_splitnum(map->floor, ',');
	if (ft_tablen(map->celestial_tab) != 3)
	{
		if (map->celestial_tab == NULL)
			return (printf(NUM_C), free_map(map), -1);
		return (printf(ARG_C), free_map(map), -1);
	}
	if (ft_tablen(map->floor_tab) != 3)
	{
		if (map->floor_tab == NULL)
			return (printf(NUM_F), free_map(map), -1);
		return (printf(ARG_F), free_map(map), -1);
	}
	while (++i < 3)
		if (ft_atoi(map->celestial_tab[i]) > 255
			|| ft_atoi(map->celestial_tab[i]) < 0
			|| ft_atoi(map->floor_tab[i]) > 255
			|| ft_atoi(map->floor_tab[i]) < 0)
			return (printf(RGB), free_map(map), -1);
	return (mlx_start(map));
}

int	convert_rgb(char **tab)
{
	int	r;
	int	g;
	int	b;
	int	hex_value;

	r = ft_atoi(tab[0]);
	g = ft_atoi(tab[1]);
	b = ft_atoi(tab[2]);
	hex_value = (r << 16) | (g << 8) | b;
	return (hex_value);
}

int	mlx_start(t_map *map)
{
	t_data	data;

	ft_memset(&data, 0, sizeof(t_data));
	data.map = map;
	map->map_int = tab_char_to_tab_int(map->map);
	data.mlx = mlx_init();
	if (!data.mlx)
		return (free_mlx(&data), printf(MLX_FAIL), exit(1), 1);
	data.win = mlx_new_window(data.mlx, SCREENWIDTH, SCREENHEIGHT, "Cub3D");
	if (!data.win)
		return (free_mlx(&data), printf(MLX_FAIL), exit(1), 1);
	init_textures(&data);
	get_pos_player(map, &data);
	data.ceiling = convert_rgb(map->celestial_tab);
	data.floor = convert_rgb(map->floor_tab);
	ft_draw(&data);
	mlx_put_image_to_window(data.mlx, data.win, data.render.img, 0, 0);
	mlx_hook(data.win, KeyPress, KeyPressMask, &key_press, &data);
	mlx_hook(data.win, KeyRelease, KeyReleaseMask, &key_release, &data);
	mlx_hook(data.win, 17, 1L << 17, mlx_loop_end, data.mlx);
	mlx_loop_hook(data.mlx, ft_move, &data);
	mlx_loop(data.mlx);
	return (free_mlx(&data), 0);
}
