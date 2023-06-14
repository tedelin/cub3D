/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_struct_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 05:12:20 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/06/14 09:20:14 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	set_map(t_map *map, int i)
{
	int	j;

	j = 0;
	map->map = malloc(sizeof(char *) * (ft_tablen(map->file_content) - i + 1));
	if (!map->map)
		return (printf("Error\nMalloc failed\n"), free_map(map), -1);
	while (map->file_content[i])
	{
		if (!ft_empty(map->file_content[i]) && ft_is_last(map->file_content, i))
			return (map->map[j] = NULL, printf("Error\nEmpty line in map\n"),
				free_map(map), -1);
		if (!ft_empty(map->file_content[i]))
			break ;
		map->map[j++] = ft_strdup(map->file_content[i++]);
	}
	map->map[j] = NULL;
	return (check_caracter(map));
}

int	already_set(t_map *map, char **split)
{
	if (split[0][0] == 'N' && map->north)
		return (-1);
	else if (split[0][0] == 'E' && map->east)
		return (-1);
	else if (split[0][0] == 'W' && map->west)
		return (-1);
	else if (split[0][0] == 'S' && map->south)
		return (-1);
	else if (split[0][0] == 'F' && map->floor)
		return (-1);
	else if (split[0][0] == 'C' && map->celestial)
		return (-1);
	return (1);
}

int	set_newsfc(t_map *map, char *line)
{
	char	**split;

	split = ft_split(line, ' ');
	if (already_set(map, split) == -1)
		return (printf("Error\nDouble declaration of texture\n"),
				free_tab(split),
				free_map(map),
				-1);
	if (!ft_strncmp(split[0], "NO", 2) && !map->north && !split[2]
		&& ft_strlen(split[0]) == 2)
		map->north = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "EA", 2) && !map->east && !split[2]
		&& ft_strlen(split[0]) == 2)
		map->east = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "WE", 2) && !map->west && !split[2]
		&& ft_strlen(split[0]) == 2)
		map->west = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "SO", 2) && !map->south && !split[2]
		&& ft_strlen(split[0]) == 2)
		map->south = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "F", 1) && !map->floor && !split[2]
		&& ft_strlen(split[0]) == 1)
		map->floor = ft_strdup(split[1]);
	else if (!ft_strncmp(split[0], "C", 1) && !map->celestial && !split[2]
		&& ft_strlen(split[0]) == 1)
		map->celestial = ft_strdup(split[1]);
	return (free_tab(split), 0);
}

int	search_newsfc(t_map *map)
{
	char	*str;
	int		i;
	int		j;

	str = "NEWSFC";
	i = -1;
	while (map->file_content[++i])
	{
		j = 0;
		while (map->file_content[i][j] == ' ')
			j++;
		if (ft_strchr(str, map->file_content[i][j]))
		{
			if (set_newsfc(map, map->file_content[i]) == -1)
				return (-1);
		}
		else if (map->file_content[i][j] != '\n' && (!map->north || !map->south
					|| !map->west || !map->east || !map->floor
					|| !map->celestial))
			return (printf("Error\nInvalid Texture\n"), free_map(map), -1);
		if (map->north && map->south && map->west && map->east && map->floor
			&& map->celestial)
			break ;
	}
	return (search_newsfc2(map, ++i));
}

int	search_newsfc2(t_map *map, int i)
{
	while (map->file_content[i] && !ft_empty(map->file_content[i]))
		i++;
	return (set_map(map, i));
}
