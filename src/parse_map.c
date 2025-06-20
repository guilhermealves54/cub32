/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:48:24 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/20 17:14:07 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	check_textures(t_cub *cub);
static char	**finalmap(t_cub *cub);
static int	chk_closedmap(t_cub *cub);
static int	search_row(t_cub *cub, int *i, int *j);
static int	search_col(t_cub *cub, int *i, int *j);

int	parse_map(t_cub *cub)
{
	if (check_textures(cub) == -1)
		return (write(2, "Error\nInvalid textures\n", 23), -1);
	cub->map.map = finalmap(cub);
	if (cub->map.map == NULL)
		return (write(2, "Error\nInvalid map\n", 18), -1);
	if (chk_closedmap(cub) == -1)
		return (cln_maparr(cub), write(2, "Error\nInvalid map\n", 18), -1);
	return (0);
}

static int	check_textures(t_cub *cub)
{
	int		no_fd;
	int		so_fd;
	int		we_fd;
	int		ea_fd;

	no_fd = open(cub->mapset.no, O_RDONLY);
	if (no_fd < 0)
		return (-1);
	so_fd = open(cub->mapset.so, O_RDONLY);
	if (so_fd < 0)
		return (close (no_fd), -1);
	ea_fd = open(cub->mapset.ea, O_RDONLY);
	if (ea_fd < 0)
		return (close (no_fd), close (so_fd), -1);
	we_fd = open(cub->mapset.we, O_RDONLY);
	if (we_fd < 0)
		return (close (no_fd), close (so_fd),
			close (ea_fd), -1);
	return (close (no_fd), close (so_fd), close (ea_fd), close (we_fd), 0);
}

char	**finalmap(t_cub *cub)
{
	int	i;

	mapsize(cub);
	if (cub->map.col < 3 || cub->map.lns < 3)
		return (NULL);
	cub->map.map = ft_calloc (cub->map.lns + 1, sizeof(char *));
	if (!cub->map.map)
		return (NULL);
	cub->map.map[cub->map.lns] = NULL;
	i = 0;
	while (i < cub->map.lns)
	{
		cub->map.map[i] = ft_calloc (cub->map.col + 1, sizeof(char));
		if (!cub->map.map[i])
			return (cln_maparr(cub), NULL);
		cub->map.map[i][cub->map.col] = '\0';
		i++;
	}
	if (fill_final_map(cub, cub->map.col, cub->map.lns) == -1)
		return (cln_maparr(cub), NULL);
	return (cub->map.map);
}

int	chk_closedmap(t_cub *cub)
{
	int		i;
	int		j;

	i = 0;
	while (i < cub->map.lns)
	{
		if (search_row(cub, &i, &j) == -1)
			return (-1);
	}
	j = 0;
	while (j < cub->map.col)
	{
		if (search_col(cub, &i, &j) == -1)
			return (-1);
	}
	return (0);
}

static int	search_row(t_cub *cub, int *i, int *j)
{
	char	fst_elem;
	char	lst_elem;

	*j = 0;
	fst_elem = 0;
	lst_elem = 0;
	while (cub->map.map[*i][*j] == ' ')
		(*j)++;
	fst_elem = cub->map.map[*i][*j];
	while (cub->map.map[*i][*j] == '1' || cub->map.map[*i][*j] == '0')
		(*j)++;
	if (*j > 0)
		lst_elem = cub->map.map[*i][*j - 1];
	else
		lst_elem = cub->map.map[*i][*j];
	if (fst_elem != '1' || lst_elem != '1')
		return (-1);
	(*i)++;
	return (0);
}

static int	search_col(t_cub *cub, int *i, int *j)
{
	char	fst_elem;
	char	lst_elem;

	*i = 0;
	fst_elem = 0;
	lst_elem = 0;
	while (*i < cub->map.lns && cub->map.map[*i][*j] == ' ')
		(*i)++;
	fst_elem = cub->map.map[*i][*j];
	while (*i < cub->map.lns && (cub->map.map[*i][*j] == '1'
		|| cub->map.map[*i][*j] == '0'))
		(*i)++;
	if (*i > 0)
		lst_elem = cub->map.map[*i - 1][*j];
	else
		lst_elem = cub->map.map[*i][*j];
	if (fst_elem != '1' || lst_elem != '1')
		return (-1);
	(*j)++;
	return (0);
}
