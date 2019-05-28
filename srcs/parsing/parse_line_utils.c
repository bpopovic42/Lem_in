/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_line_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/28 18:10:12 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/28 19:05:48 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		line_is_comment(const char *line)
{
	return (*line == '#' && *(line + 1) != '#');
}

int		line_is_command(const char *line)
{
	return (*line == '#' && *(line + 1) == '#');
}

int		line_is_link(const char *line)
{
	return (ft_count_words(line, WSPCS) == 1 && ft_strchrn(line, '-') == 1);
}

int		line_is_room(const char *line)
{
	return (ft_count_words(line, WSPCS) == 3);
}
