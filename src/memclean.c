/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42porto.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:41:29 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/19 19:33:42 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cln_conf(t_cub *cub, int opt);

void	cln_maparr(t_cub *cub)
{
	int	i;

	i = 0;
	while (cub->map.map[i])
		free (cub->map.map[i++]);
	free (cub->map.map);
}

void	cln_conf(t_cub *cub, int opt)
{
	if (cub->mapset.no)
		free (cub->mapset.no);
	if (cub->mapset.so)
		free (cub->mapset.no);
	if (cub->mapset.ea)
		free (cub->mapset.no);
	if (cub->mapset.we)
		free (cub->mapset.no);
	if (opt == 1)
	{
		if (cub->mapset.tmp_map)
			free (cub->mapset.tmp_map);
	}
}
