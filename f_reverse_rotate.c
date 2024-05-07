/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reverse_rotate.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 13:03:56 by marvin            #+#    #+#             */
/*   Updated: 2024/04/24 13:03:56 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// przenosze wartosc z dolu stosu na gore
//
// PRZYKLAD
// 4 (P->null, N->8)
// 8 (P->4, N->9)
// 9 (P->8, N->null)
// wytlumaczenie w poszczegolnych wierszach
//
// wynik po ponizszej funkcji:
// 9 (P->null, N->4)
// 4 (P->9, N->8)
// 8 (P->4, N->null)

static void reverse_rotate (t_stack **stack)
{
    t_stack *last;
    int     x;

    x = stack_len(*stack);
    if (*stack == NULL || stack == NULL || x == 1)
        return ;
    last = find_last_node(*stack); // 9
	last->prev->next = NULL; // ustawiam wartosc next liczby przed ostatnia (8) na NULL; 8(P->4, N->null)
    last->next = *stack; // ustawiam wartosc next liczby 9 na poczatek stosu (4); 9(P->8, N->4)
	last->prev = NULL; // ustawiam wartosc prev liczby 9 na NULL; 9(P->null, N->4)
    *stack = last; // ustawiam last na poczatek stosu (zdaje sie ze to jest wazne, aby ustawic nowy poczatek stosu)
	last->next->prev = last; // ustawiam wartosc prev nastepnej liczby po ostatniej (4) na ostatnia (9); 4(P->9, N->8)
}

void rra(t_stack **a)
{
	reverse_rotate(a);
	write(1, "rra\n", 4);
}

void rrb(t_stack **b)
{
	reverse_rotate(b);
	write(1, "rrb\n", 4);
}

void rrr(t_stack **a, t_stack **b)
{
	reverse_rotate(a);
	reverse_rotate(b);
	write(1, "rrr\n", 4);
}