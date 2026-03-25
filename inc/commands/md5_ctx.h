/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5_ctx.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:07 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/24 18:05:49 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "opt.h"

typedef struct	s_md5_ctx
{
	char	***av;

	t_opt_ctx			opt_ctx;

	t_opt				help;

	t_opt				echo;
	t_opt				quiet;
	t_opt				reverse;
	t_opt				string;
}	t_md5_ctx;

int		md5_ctx_init(t_md5_ctx *ctx, char ***av);
void	md5_ctx_delete(t_md5_ctx *ctx);
