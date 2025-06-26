/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memclean.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:41:29 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/26 16:31:42 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	cln_conf(t_cub *cub, int opt);
void	mem_clean(t_cub *cub);
void	cln_basic(t_cub *cub);

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
	if (cub->map.no)
		free (cub->map.no);
	if (cub->map.so)
		free (cub->map.so);
	if (cub->map.ea)
		free (cub->map.ea);
	if (cub->map.we)
		free (cub->map.we);
	if (opt == 1)
	{
		if (cub->map.tmp_map)
			free (cub->map.tmp_map);
	}
}

void	mem_clean(t_cub *cub)
{
	int	i;

	mlx_destroy_image(cub->mlx, cub->img);
	i = 0;
	while (i < 4)
		mlx_destroy_image(cub->mlx, cub->tex[i++].img);
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	cln_maparr(cub);
	cln_conf(cub, 0);
}

void	cln_basic(t_cub *cub)
{
	mlx_destroy_window(cub->mlx, cub->win);
	mlx_destroy_display(cub->mlx);
	cln_maparr(cub);
	cln_conf(cub, 0);
}
