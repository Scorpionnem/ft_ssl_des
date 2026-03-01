/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispatch.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 21:04:16 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/01 14:36:04 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "sha256.h"
#include "md5.h"
#include "ctx.h"

int	md5_dispatch(void *ctx_ptr)
{
	t_ctx	*ctx = ctx_ptr;
	(void)ctx;
	return (0);
}

int	sha256_dispatch(void *ctx_ptr)
{
	t_ctx	*ctx = ctx_ptr;
	(void)ctx;
	return (0);
}
