/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/27 16:47:04 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/18 20:01:14 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

static const char	*get_error_msg(int error_code)
{
	if (error_code == EINVANT)
		return (EINVANT_MSG);
	else if (error_code == ENEROOM)
		return (ENEROOM_MSG);
	else if (error_code == ENELINK)
		return (ENELINK_MSG);
	else if (error_code == EINVMAP)
		return (EINVMAP_MSG);
	else if (error_code == ENOPATH)
		return (ENOPATH_MSG);
	else
		return ("Undefined error.");
}

void				lemin_perror(int error_code, char *line)
{
	if (ERR_DBG)
		ft_printf("{red}");
	ft_putstr("ERROR");
	if (ERR_DBG)
	{
		ft_printf(": %s{eoc}\n", get_error_msg(error_code));
		if (line && error_code != EINVMAP)
		{
			ft_printf("{red}Problematic line :{eoc}\n");
			ft_printf("%s {red}<-{eoc}\n", line);
		}
	}
}
