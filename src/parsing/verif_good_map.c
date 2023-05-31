/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   verif_good_map.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/26 05:20:12 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/05/24 14:08:15 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_line(t_map *map)
{
	int	i;
	int	begin;
	int	end;

	i = 0;
	while (map->map[i])
	{
		begin = 0;
		end = ft_strlen(map->map[i]) - 1;
		while (map->map[i][begin] == ' ')
			begin++;
		while (map->map[i][end] == ' ' || map->map[i][end] == '\n')
			end--;
		if (map->map[i][begin] != '1' || map->map[i][end] != '1')
			return (printf("Error\nMap not closed\n"), free_map(map), -1);
		i++;
	}
	return (check_column(map));
}

int	check_up(t_map *map, int i, int j)
{
	while (i > 0)
	{
		if (map->map[i - 1][j] && map->map[i - 1][j] == '1')
			return (0);
		if (map->map[i - 1][j] && map->map[i - 1][j] == ' ')
			return (-1);
		i--;
	}
	return (-1);
}

int	check_down(t_map *map, int i, int j)
{
	while (i < ft_tablen(map->map))
	{
		if (map->map[i + 1][j] && map->map[i + 1][j] == '1')
			return (0);
		if (map->map[i + 1][j] && map->map[i + 1][j] == ' ')
			return (-1);
		i++;
	}
	printf("tst\n");
	return (-1);
}

int	check_floor_empty(t_map *map)
{
	int		i;
	int		j;
	char	*str;

	str = "01NSEW";
	i = -1;
	while (map->map[++i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] == '0' || ft_strchr("NSEW", map->map[i][j]))
			{
				if (j + 1 > ft_strlen_bis(map->map[i - 1])
					|| j + 1 > ft_strlen_bis(map->map[i + 1])
					|| ft_strchr(str, map->map[i - 1][j]) == NULL
					|| ft_strchr(str, map->map[i + 1][j]) == NULL
					|| ft_strchr(str, map->map[i][j - 1]) == NULL
					|| ft_strchr(str, map->map[i][j + 1]) == NULL)
					return (printf("Error\nMap invalid\n"), free_map(map), -1);
			}
			j++;
		}
	}
	return (check_player(map));
}

int	check_column(t_map *map)
{
	int	begin;
	int	end;
	int	j;

	begin = 0;
	end = ft_tablen(map->map) - 1;
	if (column_max_min(map, begin) == -1 || column_max_min(map, end) == -1)
		return (-1);
	while (map->map[begin] && begin <= end)
	{
		j = 0;
		while (map->map[begin][++j])
			if (map->map[begin][j] == '0' && check_up(map, begin, j) == -1)
				return (printf("Error\nMap invalid\n"), free_map(map), -1);
		begin++;
	}
	while (end >= 0 && map->map[end])
	{
		j = 0;
		while (map->map[end][++j])
			if (map->map[end][j] == '0' && check_down(map, end, j) == -1)
				return (printf("Error\n  Map invalid\n"), free_map(map), -1);
		end--;
	}
	return (check_floor_empty(map));
}
