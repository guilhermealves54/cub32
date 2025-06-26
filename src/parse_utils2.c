/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 18:52:55 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/26 16:31:22 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		check_xpm_file(t_cub *cub);
int		search_row(t_cub *cub, int i);
int		search_col(t_cub *cub, int j);
void	load_textures(t_cub *cub);

void	mapsize(t_cub *cub)
{
	int	i;
	int	max_col;

	i = 0;
	max_col = 0;
	cub->map.col = 0;
	cub->map.lns = 0;
	while (cub->map.tmp_map[i] && cub->map.tmp_map[i] == '\n')
		i++;
	while (cub->map.tmp_map[i])
	{
		while (cub->map.tmp_map[i] && cub->map.tmp_map[i] != '\n')
		{
			if (cub->map.tmp_map[i] == '\t')
				cub->map.col += 4;
			else
				cub->map.col++;
			i++;
		}
		if (cub->map.tmp_map[i] == '\n'
			&& cub->map.tmp_map[i - 1] != '\n')
			cub->map.lns++;
		if (cub->map.col >= max_col)
			max_col = cub->map.col;
		cub->map.col = 0;
		i++;
	}
	cub->map.col = max_col;
}

int	check_xpm_file(t_cub *cub)
{
	int	size;

	size = ft_strlen (cub->map.no);
	if (size < 7 || ft_strncmp (&cub->map.no[size - 4], ".xpm", 4) != 0)
		return (-1);
	size = ft_strlen (cub->map.so);
	if (size < 7 || ft_strncmp (&cub->map.so[size - 4],
			".xpm", 4) != 0)
		return (-1);
	size = ft_strlen (cub->map.ea);
	if (size < 7 || ft_strncmp (&cub->map.ea[size - 4],
			".xpm", 4) != 0)
		return (-1);
	size = ft_strlen (cub->map.we);
	if (size < 7 || ft_strncmp (&cub->map.we[size - 4],
			".xpm", 4) != 0)
		return (-1);
	return (0);
}

int	search_row(t_cub *cub, int i)
{
	int		j;
	char	c;

	j = 0;
	while (cub->map.map[i][j])
	{
		c = cub->map.map[i][j];
		if (c == '0')
		{
			if (j == 0 || !cub->map.map[i][j - 1]
				|| cub->map.map[i][j - 1] == ' ')
				return (-1);
			if (!cub->map.map[i][j + 1] || cub->map.map[i][j + 1] == ' ')
				return (-1);
		}
		j++;
	}
	return (0);
}

int	search_col(t_cub *cub, int j)
{
	int		i;
	char	c;

	i = 0;
	while (i < cub->map.lns)
	{
		c = cub->map.map[i][j];
		if (c == '0')
		{
			if (i == 0 || j >= cub->map.col || cub->map.map[i - 1][j] == ' ')
				return (-1);
			if (i + 1 >= cub->map.lns || j >= cub->map.col
				|| cub->map.map[i + 1][j] == ' ')
				return (-1);
		}
		i++;
	}
	return (0);
}

void	load_textures(t_cub *cub)
{
	char	*paths[4];
	int	i;

	paths[TEX_N] = cub->map.no;
	paths[TEX_S] = cub->map.so;
	paths[TEX_E] = cub->map.ea;
	paths[TEX_W] = cub->map.we;
	i = 0;
	while (i < 4)
	{
		cub->tex[i].img = mlx_xpm_file_to_image(cub->mlx, paths[i],
			&cub->tex[i].width, &cub->tex[i].height);
		if (!cub->tex[i].img)
		{
			printf("Could not load Texture\n");
			while (--i >= 0)
				mlx_destroy_image(cub->mlx, cub->tex[i].img);
			cln_basic(cub);
			exit(1);
		}
		cub->tex[i].pix = (int *)mlx_get_data_addr(cub->tex[i].img,
			&cub->tex[i].bpp, &cub->tex[i].size_line, &cub->tex[i].endian);
		i++;
	}
}
