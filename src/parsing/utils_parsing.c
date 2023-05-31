/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/28 01:36:58 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/05/24 14:08:12 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	check_caracter(t_map *map)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	str = " NSWEFC\n";
	while (map->map[i])
	{
		j = 0;
		while (map->map[i][j])
		{
			if (map->map[i][j] != '1' && map->map[i][j] != '0' && ft_strchr(str,
					map->map[i][j]) == 0)
				return (printf("Error\nCaracter not valid\n"), free_map(map),
					-1);
			j++;
		}
		i++;
	}
	return (check_line(map));
}

int	column_max_min(t_map *map, int i)
{
	int	j;

	j = 0;
	while (map->map[i][j])
	{
		if (map->map[i][j] != '1' && map->map[i][j] != ' '
			&& map->map[i][j] != '\n')
			return (printf("Error\nMap not closed\n"), free_map(map), -1);
		j++;
	}
	return (0);
}

int	ft_strlen_bis(char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	return (i);
}

int	ft_is_last(char **tab, int i)
{
	while (tab && tab[i])
	{
		if (ft_empty(tab[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_empty(char *str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		if (str[i] != ' ' && str[i] != '\n')
			return (1);
		i++;
	}
	return (0);
}
