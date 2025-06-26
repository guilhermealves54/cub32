/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:58:52 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/26 17:00:16 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	fill_loop(t_cub *cub, int *n, int *i, int *j);
static int	fill_void(t_cub *cub, int *n, int *i, int *j);
static int	fill_space(t_cub *cub, int *n, int *i, int *j);
static int	set_pl_start(t_cub *cub, int *n, int *i, int *j);

int	fill_final_map(t_cub *cub, int col, int lns)
{
	int	i;
	int	j;
	int	n;
	int	status;

	i = 0;
	n = 0;
	while (i < lns)
	{
		j = 0;
		while (j < col)
		{
			status = fill_loop(cub, &n, &i, &j);
			if (status == -1)
				return (-1);
			else if (status == 1)
				break ;
		}
	}
	return (0);
}

static int	fill_loop(t_cub *cub, int *n, int *i, int *j)
{
	if (cub->map.tmp_map[*n] == '\t'
		|| cub->map.tmp_map[*n] == ' ')
		return (fill_void (cub, n, i, j));
	else if (cub->map.tmp_map[*n] == '1'
		|| cub->map.tmp_map[*n] == '0')
		return (fill_space (cub, n, i, j));
	else if (cub->map.tmp_map[*n] == 'N'
		|| cub->map.tmp_map[*n] == 'S'
		|| cub->map.tmp_map[*n] == 'E'
		|| cub->map.tmp_map[*n] == 'W')
		return (set_pl_start (cub, n, i, j));
	else if (cub->map.tmp_map[*n] == '\n')
	{
		(*n)++;
		(*i)++;
		return (1);
	}
	else
		return (-1);
}

static int	fill_void(t_cub *cub, int *n, int *i, int *j)
{
	int	tab;

	if (cub->map.tmp_map[*n] == '\t')
	{
		tab = 0;
		while (tab < 4)
		{
			cub->map.map[*i][*j] = ' ';
			tab++;
			(*j)++;
		}
		(*n)++;
	}
	else if (cub->map.tmp_map[*n] == ' ')
	{
		cub->map.map[*i][*j] = ' ';
		(*j)++;
		(*n)++;
	}
	return (0);
}

static int	fill_space(t_cub *cub, int *n, int *i, int *j)
{
	if (cub->map.tmp_map[*n] == '1')
	{
		cub->map.map[*i][*j] = '1';
		(*j)++;
		(*n)++;
	}
	else if (cub->map.tmp_map[*n] == '0')
	{
		cub->map.map[*i][*j] = '0';
		(*j)++;
		(*n)++;
	}
	return (0);
}

static int	set_pl_start(t_cub *cub, int *n, int *i, int *j)
{
	if (cub->map.tmp_map[*n] == 'N')
		cub->player.angle = 90;
	if (cub->map.tmp_map[*n] == 'S')
		cub->player.angle = 270;
	if (cub->map.tmp_map[*n] == 'E')
		cub->player.angle = 0;
	if (cub->map.tmp_map[*n] == 'W')
		cub->player.angle = 180;
	cub->player.pos_y = *i + 0.5;
	cub->player.pos_x = *j + 0.5;
	cub->map.map[*i][*j] = '0';
	(*j)++;
	(*n)++;
	return (0);
}
