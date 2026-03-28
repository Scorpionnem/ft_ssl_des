/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atod.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbatty <mbatty@student.42angouleme.fr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/28 11:05:24 by mbatty            #+#    #+#             */
/*   Updated: 2026/03/28 11:05:26 by mbatty           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

double	ft_atod(const char *s)
{
	double	left;
	double	right;
	int		is_positive;
	int		frac;

	left = 0;
	right = 0;
	frac = 1;
	is_positive = 1;
	while (*s == ' ')
		s++;
	if (*s == '-')
	{
		is_positive = -1;
		s++;
	}
	while (*s >= '0' && *s <= '9')
	{
		left = left * 10 + (*s - '0');
		s++;
	}
	if (*s == '.')
		s++;
	while (*s >= '0' && *s <= '9')
	{
		right = right * 10 + (*s - '0');
		frac *= 10;
		s++;
	}
	return ((left + right / frac) * is_positive);
}
