/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francesca <francesca@student.42.fr>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/07 12:27:16 by francesca         #+#    #+#             */
/*   Updated: 2025/04/07 15:47:20 by francesca        ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

int ft_is_space(char c)
{
    if ((c == ' ') || (c > 9 && c <= 13))
        return (1);
    return (0);
}

int ft_isdigit(char c)
{
    if (c >= '0' && c <= '9')
        return (1);
    return (0);
}

//Secure atoi that return -1 if the input is invalid
//e non ammette numeri negativi perche in philo nn sefvono!
int ft_atoi(const char *str)
{
    long result;
    int i;

    result = 0;
    i = 0;
    while (ft_is_space(str[i]))
        i++;
    if (str[i] == '+')
        i++;
    else if (str[i] == '-')
        return (-1);
    while (str[i])
    {
        if (!(ft_isdigit(str[i])))
            return (-1);
        result = result * 10 + (str[i] - '0');
        if (result > 2147483647)
            return (-1); // overflow int
        i++;
    }
    return ((int)result);
}
