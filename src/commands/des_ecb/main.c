/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 17:57:01 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 21:05:48 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "des_ecb_ctx.h"
#include "libft.h"
#include "ft_printf.h"
#include "input.h"
#include <stdint.h>

int	des_ecb_main(char **av)
{
	t_des_ecb_ctx	ctx;

	if (des_ecb_ctx_init(&ctx, &av) == -1)
		return (1);

	des_ecb_ctx_delete(&ctx);
	return (0);
}
