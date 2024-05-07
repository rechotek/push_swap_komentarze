/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/21 16:34:46 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/23 18:45:00 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// szukam tu ostatniej liczby, ktora dodalem do stosu

t_stack *find_last_node(t_stack *head)
{
	if (head == NULL)
		return (NULL);
	while (head->next)
		head = head->next;
	return (head);
}

// append_node dodaje liczbe do stosu, czyli tworzy nowy node i nadaje mu wartosc
// dla kazdego nowego node, next = NULL, poniewaz po nim nie ma jeszcze nic
// a previous = last_node, czyli ten, ktory ostatnio probowalem "wgrac"
// jesli to jest pierwszy node to przechowuje wskaznik na stos a

void append_node(t_stack **stack, int nbr)
{
	t_stack *node;
	t_stack *last_node;

	if (stack == NULL)
		return ; // jak jest void to return musi byc pusty, poniewaz void sam z siebie nie zwraca nic
	node = malloc(sizeof(t_stack)); // alokujac pamiec tworze node
	if (node == NULL)
		return ;
	node->next = NULL;
	node->value = nbr; // przypisuje liczbe (nbr) do node
	if (*stack == NULL) // sprawdzam czy jest pusty (to dlatego w main inicjalizuje t_stack *a = NULL)
	{
		*stack = node;
		node->prev = NULL;
	}
	else
	{
		last_node = find_last_node(*stack);
		last_node->next = node;
		node->prev = last_node;
	}
}

// przeszukuje stos az natknie sie na pozycje oflagowana przez set_cheapest jako najtansza i ja zwraca

t_stack *return_cheapest(t_stack *b)
{
	if(b == NULL)
		return (NULL);
	while (b)
	{
		if (b->cheapest)
			return (b);
		b = b->next;
	}
	return (NULL);
}

// find_smallest wyszukuje najmniejsza liczbe w stosie a i zwraca pointer do tej liczby

t_stack *find_smallest(t_stack *a)
{
	long	smallest;
	t_stack	*smallest_node;

	if (a == NULL)
		return (NULL);
	smallest = LONG_MAX;
	while (a)
	{
		if (a->value < smallest)
		{
			smallest = a->value;
			smallest_node = a;
		}
		a = a->next;
	}
	return (smallest_node);
}