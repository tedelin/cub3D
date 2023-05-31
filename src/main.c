/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mcatal-d <mcatal-d@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/25 16:41:07 by mcatal-d          #+#    #+#             */
/*   Updated: 2023/04/25 20:01:54 by mcatal-d         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	main(int argc, char **argv, char **env)
{
	(void)env;
	if (argc != 2)
		return (printf("Error\nWrong number of arguments\n"), 0);
	if (ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 4)
		|| ft_strlen(argv[1]) < 5)
		return (printf("Error\nWrong file extension\n"), 0);
	if (parsing(argv[1]) == -1)
		return (0);
	return (0);
}
