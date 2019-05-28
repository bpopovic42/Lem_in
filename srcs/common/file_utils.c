/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 20:04:06 by bopopovi          #+#    #+#             */
/*   Updated: 2019/05/28 18:05:42 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_file(t_file *file)
{
	if (file)
	{
		if (file->data)
			ft_strdel(&file->data);
		ft_bzero(file, sizeof(*file));
	}
}

int		init_file(t_file *file)
{
	ft_bzero(file, sizeof(*file));
	if (!(file->data = ft_strnew(LMN_BUFF_SIZE + 1)))
		return (-1);
	file->capacity = LMN_BUFF_SIZE + 1;
	file->size = 0;
	return (0);
}
