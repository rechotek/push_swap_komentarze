/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_three.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 18:12:04 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/24 20:02:17 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// szukam najwiekszej liczby; w funkcji jest highest_node, poniewaz
// chce zwrocic nie najwyzsza wartosc (bo nie potrzebuje jej wartosci)
// a wezel (node), ktory przechowuje ta najwyzsza wartosc

static t_stack *find_highest(t_stack *stack) // dlaczego tu jest static?
{
	int		highest;
	t_stack	*highest_node;

	if(stack == NULL)
		return (NULL);
	highest = INT_MIN;
	while (stack)
	{
		if (stack->value > highest)
		{
			highest = stack->value;
			highest_node = stack;
		}
		stack = stack->next;
	}
	return (highest_node);
}

// algorytm do sortowania, kiedy mamy tylko 3 liczby (bardzo prosty jak sobie to rozrysowac)

 void sort_three(t_stack **a)
 {
	t_stack *highest_node;

	highest_node = find_highest(*a);
	if (*a == highest_node)
		ra(a);
	else if ((*a)->next == highest_node)
		rra(a);
	if ((*a)->value > (*a)->next->value)
		sa(a);
 }