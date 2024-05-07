/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_five.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:41:42 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/24 20:02:18 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

void sort_five(t_stack **a, t_stack **b)
{
    while (stack_len(*a) > 3)
    {
        init_nodes(*a, *b);
        finish_rotation(a, find_smallest(*a), 'a');
        pb(b, a);
    }
}