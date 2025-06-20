/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:39:45 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/20 15:50:30 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		get_color(char *file, char *place, int *params);
int		extract_color(char *file, int i, int *j);
void	clean_text(char *file, int i, int j);
int		chk_remain(char *file);

char	*get_texture(char *file, char *texture, int *params, int i_bk)
{
	char	*path;
	int		i;
	int		j;

	path = NULL;
	i = 0;
	j = 0;
	while (file[i])
	{
		if (!ft_strncmp(&file[i], texture, 2))
		{
			i_bk = i;
			i += 2;
			while (file[i] && (file[i] == '\t' || file[i] == ' '))
				i++;
			j = i;
			while (file[j] && file[j] != '\n')
				j++;
			path = ft_substr(file, i, j - i);
			return (clean_text(file, i_bk, j), (*params)++, path);
		}
		i++;
	}
	return (path);
}

int	get_color(char *file, char *place, int *params)
{
	int	color;
	int	i;
	int	i_bk;
	int	j;

	color = -1;
	i = 0;
	i_bk = 0;
	j = 0;
	while (file[i])
	{
		if (!ft_strncmp(&file[i], place, 1))
		{
			i_bk = i;
			i += 2;
			while (file[i] && (file[i] == '\t' || file[i] == ' '))
				i++;
			color = extract_color(file, i, &j);
			return (clean_text(file, i_bk, j), (*params)++, color);
		}
		i++;
	}
	return (color);
}

int	extract_color(char *file, int i, int *j)
{
	int		r;
	int		g;
	int		b;

	r = 0;
	g = 0;
	b = 0;
	while (file[i] && (file[i] >= '0' && file[i] <= '9'))
		r = r * 10 + (file[i++] - '0');
	while (file[i] && (file[i] == ',' || file[i] == '\t' || file[i] == ' '))
		i++;
	while (file[i] && (file[i] >= '0' && file[i] <= '9'))
		g = g * 10 + (file[i++] - '0');
	while (file[i] && (file[i] == ',' || file[i] == '\t' || file[i] == ' '))
		i++;
	while (file[i] && (file[i] >= '0' && file[i] <= '9'))
		b = b * 10 + (file[i++] - '0');
	*j = i;
	if ((r > 255 || g > 255 || b > 255) || (r < 0 || g < 0 || b < 0))
		return (-1);
	return ((r << 16) | (g << 8) | b);
}

void	clean_text(char *file, int i, int j)
{
	while (i < j)
		file[i++] = '#';
}

int	chk_remain(char *file)
{
	int	i;

	i = 0;
	while (file[i])
	{
		if (file[i] != ' ' && file[i] != '\t'
			&& file[i] != '\n' && file[i] != '#')
			return (-1);
		i++;
	}
	return (0);
}
