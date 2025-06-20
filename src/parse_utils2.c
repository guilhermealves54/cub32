/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:52:55 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/20 16:29:20 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	mapsize(t_cub *cub)
{
	int	i;
	int	max_col;

	i = 0;
	max_col = 0;
	cub->map.col = 0;
	cub->map.lns = 0;
	while (cub->mapset.tmp_map[i] && cub->mapset.tmp_map[i] == '\n')
		i++;
	while (cub->mapset.tmp_map[i])
	{
		while (cub->mapset.tmp_map[i] && cub->mapset.tmp_map[i] != '\n')
		{
			if (cub->mapset.tmp_map[i] == '\t')
				cub->map.col += 4;
			else
				cub->map.col++;
			i++;
		}
		if (cub->mapset.tmp_map[i] == '\n'
			&& cub->mapset.tmp_map[i - 1] != '\n')
			cub->map.lns++;
		if (cub->map.col >= max_col)
			max_col = cub->map.col;
		cub->map.col = 0;
		i++;
	}
	cub->map.col = max_col;
}
