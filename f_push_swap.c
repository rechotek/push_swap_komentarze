#include "push_swap.h"

// wykonuje rotate dla obu stosow jednoczesnie
// wykonuje ja dopoki, liczba a lub liczba b nie bedzie na szczycie

static void rotate_both(t_stack **a, t_stack **b, t_stack *cheapest_node)
{
	while (*a != cheapest_node->target_node && *b != cheapest_node) // dopoki liczba na szczycie a jest rozna od target_node "najtanszej" iiiii liczba na szczycie b jest rozna od "najtanszej"
		rr(a, b);
	set_current_position(*a); // uaktualniam pozycje wzgledem mediany dla obu stosow, aby wiedziec jaki ruch wykonac (r czy rr) dla tej liczby ktora jeszcze nie doszla na szczyt swojego stosu
	set_current_position(*b);
}

// wykonuje reverse rotate dla obu stosow jednoczesnie
// wykonuje ja dopoki, liczba a lub liczba b nie bedzie na szczycie

static void reverse_rotate_both(t_stack **a, t_stack **b, t_stack *cheapest_node)
{
	while (*a != cheapest_node->target_node && *b != cheapest_node) // dopoki liczba na szczycie a jest rozna od target_node "najtanszej" iiiii liczba na szczycie b jest rozna od "najtanszej"
		rrr(a, b);
	set_current_position(*a); // uaktualniam pozycje wzgledem mediany dla obu stosow, aby wiedziec jaki ruch wykonac (r czy rr) dla tej liczby ktora jeszcze nie doszla na szczyt swojego stosu
	set_current_position(*b);
}

// finish_rotation jest po to, aby doprowadzic na szczyt ta liczbe, ktora
// po wspolnych dla obu stosow rotacjach, nie znalazla sie jeszcze na szczycie stosu

void finish_rotation(t_stack **stack, t_stack *top_node, char stack_name) // stos a lub b; cheapest_node lub cheapest_node->target_node; 'a' lub 'b' czyli nazwa stosu
{
	while (*stack != top_node) // dopoki na szczycie stosu (niewazne ktorego, tak to jest napisane aby pasowalo do obu) nie jest top_node czyli cheapest
	{
		if (stack_name == 'a')
		{
			if (top_node->above_mediana) // cheapest jest powyzej mediany
				ra(stack);
			else
				rra(stack);
		}
		else if (stack_name == 'b') // cheapest jest ponizej mediany
		{
			if (top_node->above_mediana)
				rb(stack);
			else
				rrb(stack);
		}
	}
}

static void move_nodes(t_stack **a, t_stack **b)
{
	t_stack *cheapest_node;

	cheapest_node = return_cheapest(*b); // zwraca wskaznik na cheapest
	if ((cheapest_node->above_mediana) && (cheapest_node->target_node->above_mediana)) // jesli zarowno liczba b i jej target_node sa ponad mediana to wykonuje rotate
		rotate_both(a, b, cheapest_node);
	else if (!(cheapest_node->above_mediana) && !(cheapest_node->target_node->above_mediana)) // jesli zarowno liczba b i jej target_node sa ponizej mediana to wykonuje reverse rotate
		reverse_rotate_both(a, b, cheapest_node);
	finish_rotation(b, cheapest_node, 'b');
	finish_rotation(a, cheapest_node->target_node, 'a');
	pa(a, b);
}

void push_swap(t_stack **a, t_stack **b)
{
	t_stack *smallest;
	int		len_a;

	len_a = stack_len(*a);
	if (len_a == 5)
		sort_five(a, b);
	else
	{
		while (len_a-- > 3) // dopoki w stosie a sa wiecej niz 3 liczby...
			pb(b, a); // ... to przerzucam je (push) ze stosu a do stosu b
	}
	sort_three(a); // dla 3 pozostalych w stosie a liczb wykonaj sort_three
	while (*b) // dopoki sa liczby w stosie b... (wykonuje init_nodes dla aktualnych danych w stosie, po czym na podstawie tego wykonuje jeden ruch wypchniecia liczby ze stosu b do stosu a (na to wypchniecie sklada sie oczywiscie duzo innych ruchow); w następnej petli ponownie wykonuje init_nodes bo ustawienie w stosach juz sie zmienilo)
	{
		init_nodes(*a, *b); // ...to inicjuje dane dla node: aktualna pozycje w stosie (czy jest nad czy pod mediana), target_node (polaczenie liczby b z liczba a), koszt przesuniecia poszczegolnych licz b i ich target_node, okreslenie ktory koszt jest najtanszy
		move_nodes(a, b); // wykonanie ruchow niezbednych do wypchniecia liczby ze stosu b do a
	}
	set_current_position(*a); //uaktualniam pozycje wzgledem mediany tylko dla stosu a, poniewaz po wczesniejszych operacjach wszystkie liczby sa w stosie a i teraz wystarczy najmniejsza umiescic na szczycie
	smallest = find_smallest(*a);
	if (smallest->above_mediana)
		while (*a != smallest)
			ra(a);
	else
		while (*a != smallest)
			rra(a);
}