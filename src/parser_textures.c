/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_textures.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:18:47 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/28 21:44:51 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Normalizes a line from the configuration section by cleaning up spacing 
 * and ensuring consistent formatting, especially for color definitions.
 * 
 * 1 - Skip leading whitespace: Starts by skipping any leading spaces or tabs.
 * 2 - Loop through the rest of the line:
 *     - If a space or tab is found, set a flag `space = 1`.
 *     - If a comma is found, call `handle_char()` to:
 *         a. Remove space(s) before the comma,
 *         b. Add the comma to the output,
 *         c. Skip spaces after the comma.
 *     - If it’s a normal character, add a single space if needed, and copy 
 *       the character to the write position (`line[j++]`).
 * 3 - Trim trailing space: If the final character is a space, remove it.
 * 4 - Null-terminate the string and return 1.
 * 
 * This function modifies the original line in-place, removing redundant 
 * spaces/tabs and ensuring clean formatting like "F 220,100,0".
 */
int	normalize_line(char *line)
{
	int	i;
	int	j;
	int	space;

	i = 0;
	j = 0;
	space = 0;
	while (line[i] == ' ' || line[i] == '\t')
		i++;
	while (line[i])
	{
		if (line[i] == ' ' || line[i] == '\t')
			space = 1;
		else if (handle_char(line, &i, &j, &space))
			continue ;
		i++;
	}
	if (j > 0 && line[j - 1] == ' ')
		j--;
	line[j] = '\0';
	return (1);
}

/**
 * Handles special formatting cases while normalizing a line:
 * 
 * 1 - If the current character is a comma:
 *     a. Remove trailing spaces before the comma.
 *     b. Write the comma to the output position.
 *     c. Skip all whitespace after the comma.
 *     d. Return 1 to signal `normalize_line` to continue without incrementing.
 * 2 - If there was a space before the current character, and the output isn’t 
 *     at the beginning, insert a single space.
 * 3 - Copy the current character to the output and reset the space flag.
 * 
 * This function helps ensure consistent spacing around commas and prevents 
 * multiple spaces between values or identifiers.
 */


int	handle_char(char *line, int *i, int *j, int *space)
{
	if (line[*i] == ',')
	{
		while (*j > 0 && line[*j - 1] == ' ')
			(*j)--;
		line[(*j)++] = ',';
		(*i)++;
		while (line[*i] == ' ' || line[*i] == '\t')
			(*i)++;
		return (1);
	}
	if (*space && *j > 0)
		line[(*j)++] = ' ';
	line[(*j)++] = line[*i];
	*space = 0;
	return (0);
}

/**
 * Validates that a configuration line has a correct attribute identifier 
 * (NO, SO, EA, WE, F, or C) and checks that it hasn't already been set 
 * before. If invalid or duplicated, exits with an error.
 * 
 * 1 - Check for invalid attribute: If the line does not begin with a 
 * valid prefix ("NO", "SO", "EA", "WE", "F", or "C"), raise an error for
 * incorrect attributes.
 * 2 - Check for duplicated texture paths:
 *     - If line starts with "NO " and `data->no` is already set (not "X"),
 *       raise duplication error. Same for "SO ", "EA ", and "WE ".
 * 3 - Check for duplicated color values:
 *     - If line starts with "F " and `data->f_color[0]` is already filled 
 *       (not -1), raise dup error. Same for "C " and `data->c_color[0]`.
 * 
 * Always returns false to signal that parsing should continue after this check.
 */
int	invalid_or_dup_attr(char *line, t_data *data)
{
	if (line[0] != '\n' && ft_strncmp(line, "NO", 2) != 0
		&& ft_strncmp(line, "SO", 2) != 0
		&& ft_strncmp(line, "EA", 2) != 0
		&& ft_strncmp(line, "WE", 2) != 0
		&& ft_strncmp(line, "F", 1) != 0
		&& ft_strncmp(line, "C", 1) != 0)
		exit_error("Error:\nIncorrect attributes");
	if (ft_strncmp(line, "NO ", 3) == 0 && ft_strcmp(data->no, "X") != 0)
		exit_error("Error:\n'NO' parameter duplicated");
	if (ft_strncmp(line, "SO ", 3) == 0 && ft_strcmp(data->so, "X") != 0)
		exit_error("Error:\n'SO' parameter duplicated");
	if (ft_strncmp(line, "EA ", 3) == 0 && ft_strcmp(data->ea, "X") != 0)
		exit_error("Error:\n'EA' parameter duplicated");
	if (ft_strncmp(line, "WE ", 3) == 0 && ft_strcmp(data->we, "X") != 0)
		exit_error("Error:\n'WE' parameter duplicated");
	if (ft_strncmp(line, "F ", 2) == 0 && data->f_color[0] != -1)
		exit_error("Error:\n'F' parameter duplicated");
	if (ft_strncmp(line, "C ", 2) == 0 && data->c_color[0] != -1)
		exit_error("Error:\n'C' parameter duplicated");
	return (false);
}

/**
 * Parses a line that defines a texture direction (NO, SO, EA, WE),
 * extracts the corresponding file path, and updates the appropriate field 
 * in `data` if the file is accessible.
 * 
 * 1 - Identify the direction prefix:
 *     - If line starts with "NO ", "SO ", "EA ", or "WE ", set `nsew` to 
 *       'N', 'S', 'E', or 'W' accordingly. If none match, return false.
 * 2 - Trim the file path:
 *     - Extract the path by trimming spaces and newlines from the rest of 
 *       the line (starting after the prefix).
 * 3 - Check file accessibility:
 *     - If the file can be opened (`file_is_open`), call 
 *       `update_data_textures()` to update the corresponding field in `data`.
 *     - If file can't be opened, free memory and return false.
 * 
 * 4 - Return true to signal successful processing of a texture line.
 */
int	valid_texture_dir(char *line, t_data *data)
{
	char	*file;
	char	nsew;

	if (ft_strncmp(line, "NO ", 3) == 0)
		nsew = 'N';
	else if (ft_strncmp(line, "SO ", 3) == 0)
		nsew = 'S';
	else if (ft_strncmp(line, "EA ", 3) == 0)
		nsew = 'E';
	else if (ft_strncmp(line, "WE ", 3) == 0)
		nsew = 'W';
	else
		return (false);
	file = ft_strtrim(line + 2, " \n");
	if (!file)
		return (false);
	if (file_is_open(file))
		update_data_textures(file, data, nsew);
	else
		return (free(file), false);
	return (true);
}

/**
 * Updates the `data` struct with the path to a texture file, depending on 
 * the direction given ('N', 'S', 'E', or 'W').
 * 
 * 1 - Based on `nsew`, choose which texture path to update in `data`:
 *     - 'N' → update `data->no`
 *     - 'S' → update `data->so`
 *     - 'E' → update `data->ea`
 *     - 'W' → update `data->we`
 * 2 - Before assignment, free the previous value (even if it's "X").
 * 3 - Use `ft_strdup(file)` to store a new copy of the path string.
 * 4 - Free the original `file` string since it has been duplicated.
 */
void	update_data_textures(char *file, t_data *data, char nsew)
{
	if (nsew == 'N')
	{
		free(data->no);
		data->no = ft_strdup(file);
	}
	if (nsew == 'S')
	{
		free(data->so);
		data->so = ft_strdup(file);
	}
	if (nsew == 'E')
	{
		free(data->ea);
		data->ea = ft_strdup(file);
	}
	if (nsew == 'W')
	{
		free(data->we);
		data->we = ft_strdup(file);
	}
	free(file);
}
