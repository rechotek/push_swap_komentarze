/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/23 19:29:54 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/23 21:00:35 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// przenosze wartosc z gory stosu na dno
//
// PRZYKLAD
// 4 (P->null, N->8)
// 8 (P->4, N->9)
// 9 (P->8, N->null)
// wytlumaczenie w poszczegolnych wierszach
//
// wynik po ponizszej funkcji:
// 8 (P->null, N->9)
// 9 (P->8, N->4)
// 4 (P->9, N->null)

static void rotate (t_stack **stack) // zrozumiec pointery tutaj
{
	t_stack	*last;
	int		x;

	x = stack_len(*stack);
	if (stack == NULL || *stack == NULL || x == 1) // stack == NULL sprawdza czy mam wskaznik do wezla, a *stack == NULL sprawdza czy sam wezel istnieje
		return ;
	last = find_last_node(*stack); // 9
	last->next = *stack; // ustawiam wartosc next liczby 9 na poczatek stosu, czyli 4; 9 (P->8, N->4)
	*stack = (*stack)->next; // zmieniam poczatek stosu na liczbe nastepna po poczatku stosu, czyli 4 na 8 (zdaje sie ze to jest wazne, aby ustawic nowy pocztaek stosu)
	(*stack)->prev = NULL; // ustawiam prev obecnej liczby poczatkowej (8) NULL; 8 (P->null, N->9) - next 9 pozostaje bez mian to samo
	last->next->prev = last; // ustawiam wartosc prev nastepnej liczbie po ostatniej (4) na ostatnia liczbe (9); 4 (P->9, N->8)
	last->next->next = NULL; // ustawiam wartosc next nastepnej liczbie po ostatniej (4) na NULL; 4 (P->9, N->null)
}

void ra(t_stack **a)
{
	rotate(a);
	write(1, "ra\n", 3);
}

void rb(t_stack **b)
{
	rotate(b);
	write(1, "rb\n", 3);
}

void rr(t_stack **a, t_stack **b)
{
	rotate(a);
	rotate(b);
	write(1, "rr\n", 3);
}

// int main (void)
// {
// 	t_stack *a;

// 	a = NULL;
// 	append_node(&a, -4);
// 	append_node(&a, 8);
// 	append_node(&a, 9);

// 	t_stack	*ca = a;
// 	for (int x = 0; x < 10; ++x)
// 	{
// 		ca = a;
// 		while (ca)
// 		{
// 			printf("%d\n%d\n%d\n", ca->value, ca->prev : ca->next? ca->next->value : 0);
// 			ca = ca->next;
// 		}
// 		ra(&a, 0);
// 	}
// 	return (0);
// }
