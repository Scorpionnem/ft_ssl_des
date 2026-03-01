/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ctx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:07 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 14:32:56 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#define UNUSED(x)	_unused_##x __attribute__((unused))

#include "opt.h"
#include "md5.h"
#include "sha256.h"

typedef int (*t_command_func)(void *ctx);

typedef struct	s_ctx
{
	t_command_func	fn;
	char		*fn_str;

	t_opt_ctx			opt_ctx;

	t_opt				help;

	t_opt				echo;
	t_opt				quiet;
	t_opt				reverse;
	t_opt				string;
}	t_ctx;

int		ctx_init(t_ctx *ctx, char ***av);
void	ctx_delete(t_ctx *ctx);

int	ft_putnbr_hex_u(unsigned long int n, int level);
