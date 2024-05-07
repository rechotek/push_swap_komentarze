/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 12:24:52 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/21 17:13:53 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PUSH_SWAP_H
# define PUSH_SWAP_H

# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <stdbool.h>
# include <stddef.h>
# include <stdio.h>

// w tym miejscu definiuje cala strukture listy; umiescilem ja w bibliotece,
// aby miec do niej dostep przy uzywaniu dowolnej funkcji
typedef struct s_stack
{
	int		value;
	int		current_position;
	int		final_index; // ta zmienna chyba nie jest potrzebna - jest nieuzywana
	int		push_price;
	bool	above_mediana; // bool to zmienna, ktora obluguje tylko warunek true/false
	bool 	cheapest;
	struct s_stack	*target_node;
	struct s_stack	*next;
	struct s_stack	*prev;
}	t_stack; // dzieki typedef na poczatku, zamiast pisac "struct s_stack" wystarczy ze napisze t_stack

// Ogarnia kiedy do programu wprowadzimy argc == 2
char **ft_split(char *str, char separator);

// Bledy
int error_repetition(t_stack *a, int nbr);
int error_syntax(char *str);
void error_free(t_stack **a, char *argv[], bool flag_argc_2);
void matrix_free (char *argv[]);
void stack_free(t_stack **stack);


// Tworzenie stosu
void stack_init(t_stack **a, char *argv[], bool flag_argc_2);
void init_nodes(t_stack *a, t_stack *b);
void set_current_position(t_stack *stack);
void set_price(t_stack *a, t_stack *b);
void set_cheapest(t_stack *b);
t_stack *return_cheapest(t_stack *b);
t_stack *find_smallest(t_stack *a);





// Linked list
void append_node(t_stack **stack, int nbr);
t_stack *find_last_node(t_stack *head);
int stack_len(t_stack *stack);
bool stack_sorted(t_stack *stack);
void finish_rotation(t_stack **stack, t_stack *top_node, char stack_name);

// Algorytmy
 void sort_three(t_stack **a);
void sort_five(t_stack **a, t_stack **b);
 void push_swap(t_stack **a, t_stack **b);



// Moves
void sa(t_stack **a);
void sb(t_stack **b);
void ss(t_stack **a, t_stack **b);
void ra(t_stack **a);
void rb(t_stack **b);
void rr(t_stack **a, t_stack **b);
void rra(t_stack **a);
void rrb(t_stack **b);
void rrr(t_stack **a, t_stack **b);
void pa(t_stack **a, t_stack **b);
void pb(t_stack **b, t_stack **a);

#endif