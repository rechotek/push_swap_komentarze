/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   push_swap_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/07 18:18:38 by mrechuli          #+#    #+#             */
/*   Updated: 2024/05/07 18:18:40 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// Sprawdzam polozenie kazdego node wzgleden mediany dla danej konfiguracji
// polozenia wezlow. Bo to polozenie zmienia sie po kazdym ruchu w stosie.

void set_current_position(t_stack *stack)
{
    int x;
    int mediana;

	x = 0;
	if (stack == NULL)
		return ;
	mediana = stack_len(stack) / 2;
	while (stack)
	{
		stack->current_position = x; // pierwsze miejsce na gorze stosu ma wartosc 0
		if (x <= mediana) // jesli jest powyzej mediany to jest true
			stack->above_mediana = true;
		else
			stack->above_mediana = false; // a jesli ponizej mediany to jest false
		stack = stack->next; // przechodze do kolejnego miejsca w stacku
		x++; // zwiekszam x, aby miec kolejny indeks
	}
}

// target_node jest to najmniejsza wieksza liczba dla liczby ze stosu b w stosie a
// jesli nie ma takiej (czyli w przypadku kiedy liczba ze stosu b jest wieksza od kazdej z liczb w stosie a)
// to lacze ja z najmniejsza liczba ze stosu a
// szukam wiec tu polaczen liczb ze stosu b z liczbami ze stosu a

static void set_target_node(t_stack *a, t_stack *b) // dlaczego tu jest static? to tez chce zrozumiec
{
	t_stack	*current_a;
	t_stack *target_node;
	long	best_match_index;

	while (b) // dopoki w stosie b sa liczby
	{
		best_match_index = LONG_MAX; // przypisany LONG_MAX,a nie INT_MAX, poniewaz przy pierwszym if-ie sprawdzam czy dana liczba jest mniejsza od best_match_index; a jesli ta liczba bylby maksymalny int, to ten warunek by nie zadzialal
		current_a = a; // do current_a przypisuje liczbe z wierzchu stosu a (pierwsza)
		while (current_a) // dopoki sa jakies liczby w stosie a
		{
			if ((current_a->value > b->value) && (current_a->value < best_match_index)) // jezeli liczba a jest wieksza od liczby b iiiii liczba a jest mniejsza od best_match_index (bo szukam najmniejszej wiekszej)
			{
				best_match_index = current_a->value; // przypisuje best_match aktulna wartosc ze stosu a
				target_node = current_a; // przypisuje target_node aktualna pozycje liczby a
			}
			current_a = current_a->next; // przechodze do kolejnej liczby w stosie a
		}
		if (best_match_index == LONG_MAX)
			b->target_node = find_smallest(a); // w przypadku kiedy liczba ze stosu b jest wieksza od kazdej z liczb w stosie a, to lacze ja z najmniejsza liczba ze stosu a
		else
			b->target_node = target_node;
		b = b->next; // przechodze do nastepnej liczby w stosie b, aby ustawic target node dla kazdej z liczb
	}
}

// set_price okresla "koszt" wypchniecia liczby ze stosy b do stosu a,
// czyli ilosc ruchow jaka jest potrzebna, aby obie polaczone liczby (b i jej target_node)
// stanely na szczycie swoxih stosow

void set_price(t_stack *a, t_stack *b)
{
	int len_a;
	int len_b;

	len_a = stack_len(a);
	len_b = stack_len(b);
	while (b)
	{
		b->push_price = b->current_position; // koszt wypchniecia liczby b na szczyt stosu to numer aktualnej pozycj
		if (!(b->above_mediana)) // jesli liczba b jest ponizej mediany... 
			b->push_price = len_b - (b->current_position); // ...to koszt przesuniecia liczby b na szczyt, to dlugosc stosu - aktualna pozycja liczby
		if (b->target_node->above_mediana) // jesli target_node liczby b jest powyzej mediany...
			b->push_price += b->target_node->current_position; // ...to calosciowy koszt to koszt przesuniecia liczby b + aktualna pozycja target_node liczby b
		else // jesli target_node liczby b jest ponizej mediany...
			b->push_price += len_a - (b->target_node->current_position); // ...to calosciowy koszt to koszt przesuniecia liczby b + dlugosc stosu a - aktualna pozycja target_node liczby b
		b = b->next; // przechodze do kolejnej liczby w stosie b, aby obliczyc "koszt" dla kazdej z nich
	}
}

// set_cheapest szuka "najtanszej" opcji do przesuniecia i oznacza ja

void set_cheapest(t_stack *b)
{
	long	best_match_value;
	t_stack	*best_match_node;

	if (b == NULL)
		return ;
	best_match_value = LONG_MAX; // poczatkowo value ustawione na LONG_MAX, aby zawsze pierwszy push_price byl mniejszy od tej wartosci
	while (b)
	{
		if (b->push_price < best_match_value) // jezeli push_price liczby ze stosu b jest mniejszy od value...
		{
			best_match_value = b->push_price; // ... to wartosc nowego value to "cena" wypchniecia wlasnie tej liczby
			best_match_node = b; // przypisuje aktualna pozycje ze stosu b jako najlepszy node
		}
		b = b->next; // przechodze do kolejnej pozycji w b, aby sprawdzic "ceny" dla wszystkich polaczen
	}
	best_match_node->cheapest = true; // przypisuje best_match_node (czyli dana pozycje ze stosu b) jako najtansza i oznaczam ja jako true
}

void init_nodes(t_stack *a, t_stack *b)
{
    set_current_position(a);
    set_current_position(b);
    set_target_node(a, b);
    set_price(a, b);
    set_cheapest(b);
}