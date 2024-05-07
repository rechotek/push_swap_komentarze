/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mrechuli <mrechuli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/20 11:53:25 by mrechuli          #+#    #+#             */
/*   Updated: 2024/04/23 21:00:37 by mrechuli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "push_swap.h"

// obliczam dlugosc stosu. iteruje dopoki stos istnieje
// przy kazdej petli zmieniam pozycje stack na stack->next

int stack_len(t_stack *stack)
{
	int x;

	if (stack == NULL)
		return (0);
	x = 0;
	while (stack)
	{
		x++;
		stack = stack->next;
	}
	return (x);
}

// sprawdzam czy stos jest posortowany
// biore wartosc node i sprawdzam czy jest wieksza od nastepnego node
// jesli jest wieksza to blad, czyli stos nieposortowany

bool stack_sorted(t_stack *stack)
{
	if (stack == NULL)
		return (1);
	while (stack->next)
	{
		if (stack->value > stack->next->value)
			return (false);
		stack = stack->next;
	}
	return (true);
}

// else if (argc == 2)
// oprocz nazwy mamy tylko jeden argument, ale ten argument moze miec taka
// forme "3 5 42 -1337" i wtedy potrzebuje uzyc splita, aby wyciagnac z niego
// poszczegolny liczby (za pomoca splita zapisuje je w takiej
// formie, aby odzwierciedlic argv, poniewaz w dalszym kroku bede tworzyl stos
// zarowno dla danych wprowadzonych tak: "3 5 42 -1337" jak i tak: 3 5 42 -1337;
// ten drugi przyklad ma z natury forme argv, wiec chcemy uzyskac taka sama forme
// dla liczb uzyskanych za pomoca ft_split)

int main (int argc, char *argv[])
{
	t_stack	*a;
	t_stack	*b;

	a = NULL; // przypisuje NULL do pointerow, any uniknac "segmentation fault" - taka dobra praktyka
	b = NULL;
	if (argc == 1 || (argc == 2 && !argv[1][0])) //argc == 1 mowi nam ze mamy tylko nazwe programu; drugi warunek mowi o tym, ze jest jest drugi argument, ale pusty (w obu tych przypadkach zwracamy 1, bo to jest blad)
		return (0);
	else if (argc == 2) // oprocz nazwy mamy tylko jeden argument, ale ten argument moze miec taka forme "3 5 42 -1337"
		argv = ft_split(argv[1], ' '); // tutaj nazywamy tabele liczb, ktora utworzymy za pomoca splita argv, poniewaz linie nizej inicjuje stos i uzywam argv + 1, poniewaz chce od razu dostac sie do liczby - bedzie to dzialo zarowno dla liczb utworzonych w tabeli splitem, jak i dla danych wprowadzonych do programu w wielu stringach
	stack_init(&a, argv + 1, argc == 2); // argv+1, aby zaczac od miejsca gdzie juz powinna znajdowac sie pierwsza liczba
	if (!stack_sorted(a))
	{
		if (stack_len(a) == 2)
			sa(&a);
		else if (stack_len(a) == 3)
			sort_three(&a);
		else
			push_swap(&a, &b);
	}
	stack_free(&a);
}