/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   f_swap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/24 17:30:03 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/24 20:02:12 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

// zamienia miejscami dwie liczby na szczycie stosu
//
// PRZYKLAD
// 4 (P->null, N->8)
// 8 (P->4, N->9)
// 9 (P->8, N->null)
// wytlumaczenie w poszczegolnych wierszach
//
// wynik po ponizszej funkcji:
// 8 (P->null, N->4)
// 4 (P->8, N->9)
// 9 (P->4, N->null)

#include "push_swap.h"

static void swap(t_stack **stack)
{
	int x;

	x = stack_len(*stack);
	if (*stack == NULL || stack == NULL || x == 1)
		return ;
	*stack = (*stack)->next; // 8(P->4, N->9)
	(*stack)->prev->prev = *stack; // ustawiam wartosc prev w liczbie przed *stack (4) na *stack; 4(P->8, N->8)
	(*stack)->prev->next = (*stack)->next; // ustawiam wartosc next w liczbie przed *stack (4) na 9; 4(P->8, N->9)
	if((*stack)->next) // jest to warunek, ktory wykona sie jesli w stosie sa 3 liczby lub wiecej; jezeli *stack->next ma jakas liczbe (nie NULL)...
		(*stack)->next->prev = (*stack)->prev; // ...ustawiam wartosc prev liczby po stacku (9) na (*stack)->prev (4); 9(P->4, N->null)
	(*stack)->next = (*stack)->prev; // 8(P->4, N->4)
	(*stack)->prev = NULL; // 8(P->NULL, N->4)
}

void sa(t_stack **a)
{
	swap(a);
	write(1, "sa\n", 3);
}

void sb(t_stack **b)
{
	swap(b);
	write(1, "sb\n", 3);
}

void ss(t_stack **a, t_stack **b)
{
	swap(a);
	swap(b);
	write(1, "ss\n", 3);
}