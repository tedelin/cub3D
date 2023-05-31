/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_to_char.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 19:45:29 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/04/27 00:37:54 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	len_file(char *file)
{
	int		fd;
	int		i;
	char	*res;

	i = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\n"), perror(file), -1);
	res = get_next_line(fd);
	while (res)
	{
		free(res);
		i++;
		res = get_next_line(fd);
	}
	close(fd);
	return (i);
}

char	**file_to_tab(char *file, int i, char **file_content)
{
	int		fd;
	int		j;
	char	*res;

	j = 0;
	fd = open(file, O_RDONLY);
	if (fd == -1)
		return (printf("Error\n"), perror(file), NULL);
	file_content = malloc(sizeof(char *) * (i + 1));
	if (!file_content)
		return (printf("Error\nMalloc failed\n"), NULL);
	while (i-- > 0)
	{
		res = get_next_line(fd);
		file_content[j] = ft_strdup(res);
		j++;
		free(res);
	}
	file_content[j] = NULL;
	close(fd);
	return (file_content);
}

int	parsing(char *file)
{
	int		i;
	t_map	*map;

	i = len_file(file);
	map = malloc(sizeof(t_map));
	ft_memset(map, 0, sizeof(t_map));
	if (i == -1)
		return (free_map(map), -1);
	map->file_content = file_to_tab(file, i, map->file_content);
	if (!map->file_content)
		return (free_map(map), -1);
	return (search_newsfc(map));
}
