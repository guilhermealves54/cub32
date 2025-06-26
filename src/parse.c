/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gribeiro <gribeiro@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/19 17:34:53 by gribeiro          #+#    #+#             */
/*   Updated: 2025/06/26 15:48:28 by gribeiro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	readmap(t_cub *cub, int fd);
static int	fillmap(t_cub *cub, char *file);
static char	*get_map(char *file);

int	cubparse(t_cub *cub, int argc, char **argv)
{
	int	fd;

	if (argc != 2)
		return (write(2, "Error\nInvalid Arguments\n", 25), -1);
	if (!argv[1])
		return (write(2, "Error\nInvalid Arguments\n", 25), -1);
	if (ft_strncmp (&argv[1][ft_strlen (argv[1]) - 4], ".cub", 4) != 0)
		return (write(2, "Error\nInvalid Map\n", 18), -1);
	fd = open (argv[1], O_RDONLY);
	if (fd < 0)
		return (write(2, "Error\nInvalid Map\n", 18), -1);
	if (readmap(cub, fd) == -1)
		return (close (fd), -1);
	close (fd);
	if (parse_map(cub) == -1)
		return (cln_conf(cub, 1), -1);
	free (cub->map.tmp_map);
	return (0);
}

static int	readmap(t_cub *cub, int fd)
{
	char	buff[1000];
	char	*file;
	char	*temp;
	int		r;

	r = 1;
	file = ft_strdup ("");
	if (!file)
		return (write(2, "Error\nMemmory Error\n", 20), -1);
	while (r > 0)
	{
		r = read (fd, buff, 999);
		buff[r] = '\0';
		temp = NULL;
		temp = file;
		file = ft_strjoin (file, buff);
		if (!file)
			return (free (file), free (temp),
				write(2, "Error\nMemmory Error\n", 20), -1);
		free (temp);
	}
	if (fillmap(cub, file) == -1)
		return (free(file), -1);
	if (chk_remain (file) == -1)
		return (cln_conf(cub, 1), free(file),
			write(2, "Error\nInvalid Map\n", 18), -1);
	return (free(file), 0);
}

static int	fillmap(t_cub *cub, char *file)
{
	int	params;

	params = 0;
	cub->map.no = get_texture(file, "NO", &params, 0);
	cub->map.so = get_texture(file, "SO", &params, 0);
	cub->map.we = get_texture(file, "WE", &params, 0);
	cub->map.ea = get_texture(file, "EA", &params, 0);
	cub->map.f = get_color(file, "F", &params);
	if (cub->map.f == -1)
		return (cln_conf(cub, 0),
			write(2, "Error\nInvalid RGB color\n", 25), -1);
	cub->map.c = get_color(file, "C", &params);
	if (cub->map.c == -1)
		return (cln_conf(cub, 0),
			write(2, "Error\nInvalid RGB color\n", 25), -1);
	if (params != 6)
		return (cln_conf(cub, 0),
			write(2, "Error\nInvalid map settings\n", 27), -1);
	cub->map.tmp_map = get_map(file);
	return (0);
}

static char	*get_map(char *file)
{
	int		i;
	int		j;
	char	*tmp_map;

	i = ft_strlen(file);
	j = i;
	while (i > 0 && (!file[i] || file[i] == '\n'))
		i--;
	while (i > 0)
	{
		if (file[i] == '\n' && file[i - 1] == '\n')
		{
			i += 1;
			break ;
		}
		i--;
	}
	if (i <= 0)
		return (NULL);
	tmp_map = ft_strdup(&file[i]);
	if (!tmp_map)
		return (NULL);
	return (clean_text(file, i, j), tmp_map);
}
