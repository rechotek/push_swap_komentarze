/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 15:51:50 by marvin            #+#    #+#             */
/*   Updated: 2024/04/24 15:51:50 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// przenosi wartosc z wierzchu jednego stosu do drugiego

static void push(t_stack **dest, t_stack **src)
{
	t_stack *to_push;

	if (*src == NULL)
		return ;
	to_push = *src; // wierzcholek stosu z ktorego bierzemy wartosc
	*src = (*src)->next; // wierzcholek stosu to teraz wartosc kolejna po wierzcholku
	if (*src)
		(*src)->prev = NULL; // wartosc prev liczby na wierzchu stosu to NULL
	to_push->prev = NULL; // wartosc prev liczby, ktora przerzucamy to NULL
	if (*dest == NULL) // jezeli stos do ktorego wrzucamy wartosc jest pusty...
	{
		*dest = to_push; // ... to ta watosc musi byc na wierzchu stosu
		to_push->next = NULL; //  
	}
	else
	{
		to_push->next = *dest; // skoro wrzucona wartosc jest na wierzchu stosu, to nastepna wartosc jest poczatkiem dawnego stosu
		to_push->next->prev = to_push;
		*dest = to_push;
	}
}

// przenosi liczbe ze stosu b -> a
void pa(t_stack **a, t_stack **b)
{
	push (a, b);
	write(1, "pa\n", 3);
}

// przenosi liczbe ze stosu a -> b
void pb(t_stack **b, t_stack **a)
{
	push (b, a);
	write(1, "pb\n", 3);
}