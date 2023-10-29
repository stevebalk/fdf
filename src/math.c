/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   math.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sbalk <sbalk@student.fr>                   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/28 15:55:54 by sbalk             #+#    #+#             */
/*   Updated: 2023/10/29 16:31:01 by sbalk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/* Convert from degrees to radiant */
double	deg_to_rad(double deg)
{
	return (deg * 0.01745329f);
}

/* Convert from radiant to degrees */
double	rad_to_degree(double rad)
{
	return (rad * 57.29578f);
}