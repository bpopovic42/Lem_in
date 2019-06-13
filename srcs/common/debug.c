/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bopopovi <bopopovi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/06/13 16:20:25 by bopopovi          #+#    #+#             */
/*   Updated: 2019/06/13 16:33:04 by bopopovi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include "ft_printf.h"

void	print_dbg(int is_msg_last, const char *fmt_msg, ...)
{
	va_list ap;

	if (DBG_PRINT == 1)
	{
		va_start(ap, fmt_msg);
		ft_vdprintf(1, fmt_msg, ap);
		if (is_msg_last)
			ft_putchar('\n');
		va_end(ap);
	}
}
