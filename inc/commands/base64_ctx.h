/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   base64_ctx.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/20 12:34:07 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/25 10:39:42 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include "opt.h"

typedef struct	s_base64_ctx
{
	char	***av;

	t_opt_ctx			opt_ctx;

	t_opt				help;

	t_opt				decode;
	t_opt				encode;
	t_opt				input;
	t_opt				output;
}	t_base64_ctx;

int		base64_ctx_init(t_base64_ctx *ctx, char ***av);
void	base64_ctx_delete(t_base64_ctx *ctx);
