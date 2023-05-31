/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/30 14:23:16 by tedelin           #+#    #+#             */
/*   Updated: 2023/05/31 13:40:39 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	init_textures(t_data *data)
{
	data->n_wall.img = mlx_xpm_file_to_image(data->mlx, data->map->north,
			&data->n_wall.width, &data->n_wall.height);
	data->s_wall.img = mlx_xpm_file_to_image(data->mlx, data->map->south,
			&data->s_wall.width, &data->s_wall.height);
	data->w_wall.img = mlx_xpm_file_to_image(data->mlx, data->map->west,
			&data->w_wall.width, &data->w_wall.height);
	data->e_wall.img = mlx_xpm_file_to_image(data->mlx,
			data->map->east, &data->e_wall.width, &data->e_wall.height);
	data->render.img = mlx_new_image(data->mlx, SCREENWIDTH, SCREENHEIGHT);
	if (!data->e_wall.img || !data->w_wall.img || !data->s_wall.img
		|| !data->n_wall.img || !data->render.img)
		return (printf(IMG), free_mlx(data), exit(0), 1);
	data->render.data = (unsigned int *)mlx_get_data_addr(data->render.img,
			&data->render.bpp, &data->render.size_line,
			&data->render.endian);
	data->n_wall.data = (unsigned int *)mlx_get_data_addr(data->n_wall.img,
			&data->n_wall.bpp, &data->n_wall.size_line, &data->n_wall.endian);
	data->s_wall.data = (unsigned int *)mlx_get_data_addr(data->s_wall.img,
			&data->s_wall.bpp, &data->s_wall.size_line, &data->s_wall.endian);
	data->w_wall.data = (unsigned int *)mlx_get_data_addr(data->w_wall.img,
			&data->w_wall.bpp, &data->w_wall.size_line, &data->w_wall.endian);
	data->e_wall.data = (unsigned int *)mlx_get_data_addr(data->e_wall.img,
			&data->e_wall.bpp, &data->e_wall.size_line, &data->e_wall.endian);
	return (0);
}

void	ft_set(t_data *data, double dir_x, double dir_y, double plane_x)
{
	data->dir_x = dir_x;
	data->dir_y = dir_y;
	data->plane_x = plane_x;
	data->map->map_int[(int)data->pos_x][(int)data->pos_y] = 0;
	data->pos_x += 0.5;
	data->pos_y += 0.5;
}

int	get_pos_player(t_map *map, t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->map = map;
	while (map->map[++i])
	{
		j = -1;
		while (++j < ft_strlen(map->map[i]))
		{
			data->pos_x = i;
			data->pos_y = j;
			if (map->map_int[i][j] == 3)
				return (data->plane_y = 0, ft_set(data, 0, 1, 0.66), 0);
			else if (map->map_int[i][j] == 4)
				return (data->plane_y = 0, ft_set(data, 0, -1, -0.66), 0);
			else if (map->map_int[i][j] == 5)
				return (data->plane_y = -0.66, ft_set(data, 1, 0, 0), 0);
			else if (map->map_int[i][j] == 6)
				return (data->plane_y = 0.66, ft_set(data, -1, 0, 0), 0);
		}
	}
	return (0);
}

void	make_tab(char **tab_c, int **tab, int i, int j)
{
	while (++j < ft_strlen(tab_c[i]))
	{
		if (tab_c[i][j] == '1')
			tab[i][j] = 1;
		else if (tab_c[i][j] == '0')
			tab[i][j] = 0;
		else if (tab_c[i][j] == 'N')
			tab[i][j] = 3;
		else if (tab_c[i][j] == 'S')
			tab[i][j] = 4;
		else if (tab_c[i][j] == 'E')
			tab[i][j] = 5;
		else if (tab_c[i][j] == 'W')
			tab[i][j] = 6;
		else
			tab[i][j] = -1;
	}
}

int	**tab_char_to_tab_int(char **tab_c)
{
	int	i;
	int	j;
	int	**tab;

	i = 0;
	while (tab_c[i])
		i++;
	tab = malloc(sizeof(int *) * (i + 1));
	i = -1;
	while (tab_c[++i])
	{
		j = -1;
		tab[i] = malloc(sizeof(int) * ft_strlen(tab_c[i]));
		make_tab(tab_c, tab, i, j);
	}
	tab[i] = NULL;
	return (tab);
}
