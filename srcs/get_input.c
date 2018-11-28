/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_input.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/19 23:21:56 by bopopovi          #+#    #+#             */
/*   Updated: 2018/11/28 16:42:38 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "get_next_line.h"

static void		append_line_to(char *line, char **dst)
{
	char *tmp;

	if (!(tmp = ft_strjoin(*dst, line)))
		ft_perror("append_line_to: join failed.");
	ft_strdel(&line);
	if (*dst)
		ft_strdel(dst);
	if (!(*dst = ft_strjoin(tmp, "\n")))
		ft_perror("append_line_to: join failed.");
	ft_strdel(&tmp);
}

char			**get_input()
{
	int		ret;
	char	*line;
	char	*input_str;
	char	**input_array;

	ret = 0;
	line = NULL;
	input_str = NULL;
	input_array = NULL;
	/* Get input line by line */
	while ((ret = get_next_line(STDIN, &line)) > 0)
	{
		/* Append each line in input_str separated by a '\n' */
		append_line_to(line, &input_str);
	}
	if (ret < 0)
		ft_perror("get_input: failed to properly read input.");
	ft_strdel(&line);
	/* Split input_str into a string array */
	if (!(input_array = ft_strsplit(input_str, "\n")))
		ft_perror("get_input: split failed.");
	ft_strdel(&input_str);
	return (input_array);
}
