/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md5.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 00:01:19 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/02 10:10:44 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once

#include <stdint.h>

int	md5_dispatch(void *ctx);
char	*md5(uint8_t *bytes, uint32_t size);
uint64_t	md5_uint64(uint8_t *bytes, uint32_t size);
