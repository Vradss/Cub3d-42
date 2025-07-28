/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_colors.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amdemuyn <amdemuyn@student.42madrid.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/24 18:17:57 by amdemuyn          #+#    #+#             */
/*   Updated: 2025/07/28 21:50:09 by amdemuyn         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

/**
 * Parses a line defining a color (F or C), validates the format and values,
 * and updates the corresponding color field in `data`.
 * 
 * 1 - Comma check: Ensure the line contains exactly 2 commas with 
 *     `count_commas()`. If not, exit with error.
 * 2 - Split RGB: Call `split_rgb()` to trim and split the line into 3 
 *     components (R, G, B) based on commas.
 * 3 - Validate values: Use `valid_rgb_params()` to ensure all 3 values are 
 *     numeric and in the 0–255 range.
 * 4 - Store in `data`: Call `update_data_colors()` to save the parsed RGB 
 *     values in either `f_color` or `c_color` based on the prefix (F/C).
 * 
 * 5 - Return true to signal successful parsing of a color line.
 */
int	valid_color(char *line, t_data *data)
{
	char	**rgb;

	if (!count_commas(line))
		exit_error("Error:\nMust be 3 colors separated by 2 commas");
	rgb = split_rgb(line, " \n");
	valid_rgb_params(rgb);
	update_data_colors(rgb, data, line[0]);
	return (true);
}

/**
 * Checks if the line contains exactly 2 commas, as required for RGB format.
 * 
 * 1 - Iterate through the line and count commas.
 * 2 - Return false if there are not exactly 2 commas.
 * 3 - Return true if the count is valid.
 */
int	count_commas(char *line)
{
	int	i;
	int	nb_of_comas;

	i = 0;
	nb_of_comas = 0;
	while (line[i] != '\0')
	{
		if (line[i] == ',')
			nb_of_comas++;
		i++;
	}
	if (nb_of_comas != 2)
		return (false);
	return (true);
}

/**
 * Extracts the RGB components from a trimmed line, splitting by commas.
 * 
 * 1 - Trim whitespace/newlines starting after the first character (F/C).
 * 2 - Split the trimmed string by commas into 3 elements (R, G, B).
 * 3 - Validate that all 3 values are present; exit on missing/memory error.
 * 4 - Return the resulting RGB array.
 */
char	**split_rgb(char *line, char *linebreak)
{
	char	*trimmed_line;
	char	**rgb;

	trimmed_line = ft_strtrim(line + 1, linebreak);
	if (!trimmed_line)
		exit_error("Error:\nMemory allocation failed for color parsing");
	rgb = ft_split(trimmed_line, ',');
	free (trimmed_line);
	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2])
		exit_error("Error:\nMissing RGB parameter(s)");
	return (rgb);
}

/**
 * Validates that the RGB array contains exactly 3 numeric values,
 * each within the 0–255 range.
 * 
 * 1 - Check the RGB array has exactly 3 elements (no more, no less).
 * 2 - For each element:
 *     - Ensure all characters are digits.
 *     - Convert the string to int and check it is between 0 and 255.
 * 3 - Exit with error on invalid format or out-of-range values.
 * 4 - Return true if all validations pass.
 */
int	valid_rgb_params(char **rgb)
{
	int		i;
	int		value;
	char	*str;

	if (!rgb || !rgb[0] || !rgb[1] || !rgb[2] || rgb[3])
		exit_error("Error:\nRGB must have exactly 3 values");
	i = 0;
	while (i < 3)
	{
		str = rgb[i];
		while (*str)
		{
			if (!ft_isdigit(*str))
				exit_error("Error:\nInvalid character(s) for RGB line");
			str++;
		}
		value = ft_atoi(rgb[i]);
		if (value < 0 || value > 255)
			exit_error("Error:\nRGB value out of range");
		i++;
	}
	return (true);
}

/**
 * Converts RGB string values to integers and stores them in the
 * `f_color` or `c_color` array of `data`, depending on the prefix.
 * 
 * 1 - Check whether the line starts with 'F' (floor) or 'C' (ceiling).
 * 2 - For the chosen color type, convert each of the RGB values with 
 *     `ft_atoi()` and assign them to the respective position.
 * 3 - Free the RGB array after use.
 */
void	update_data_colors(char **rgb, t_data *data, char f_or_c)
{
	if (f_or_c == 'F')
	{
		data->f_color[0] = ft_atoi(rgb[0]);
		data->f_color[1] = ft_atoi(rgb[1]);
		data->f_color[2] = ft_atoi(rgb[2]);
	}
	else if (f_or_c == 'C')
	{
		data->c_color[0] = ft_atoi(rgb[0]);
		data->c_color[1] = ft_atoi(rgb[1]);
		data->c_color[2] = ft_atoi(rgb[2]);
	}
	free_array((void **)rgb);
}
