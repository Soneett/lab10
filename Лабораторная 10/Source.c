#include<stdio.h>
#include<stdlib.h>

typedef struct { //структура, определ€юща€ односв€зный список
	int coeff;
	int degree;
	struct polynom* next;
}polynom;

polynom* add_term(polynom* prev_term, int c, int d) // функци€ добавлени€ элемента с заданными пол€ми структуры в список
{
	polynom* new_term = (polynom*)malloc(sizeof(polynom));
	if (!new_term) return NULL;
	new_term->coeff = c;
	new_term->degree = d;
	new_term->next = NULL;
	if(!prev_term) return new_term;
	prev_term->next = new_term;
	return new_term;
}

polynom* create_polynom(char* str) // функци€ создани€ многочлена
{
	polynom* head= NULL, *prev_term;
	int c, d;
	printf("Enter '0' to finish input\nEnter the coefficient of term in %s polynom:  ", str);
	if (!scanf_s("%d", &c))
	{
		printf("Error! Incorrect coefficient");
		exit(1);
	}
	if (c == 0) return NULL;
	printf("Enter the degree of term in %s polynom:  ", str);
	if (!scanf_s("%d", &d) || d < 0)
	{
		printf("Error! Incorrect degree");
		exit(1);
	}
	head = add_term(head, c, d);
	prev_term = head;
	while (1)
	{
		printf("Enter '0' to finish input\nEnter the coefficient of term in %s polynom:  ", str);
		if (!scanf_s("%d", &c))
		{
			printf("Error! Incorrect coefficient");
			exit(1);
		}
		if (c == 0) break;
		printf("Enter the degree of term in %s polynom:  ", str);
		if (!scanf_s("%d", &d) || d<0)
		{
			printf("Error! Incorrect degree");
			exit(1);
		}
		prev_term = add_term(prev_term, c, d);
	}
	return head;
}

 void is_correct(polynom* head) // если в многочлене есть одинаковые степени, они суммируютс€
{
	if (!head) return NULL;

	polynom* tmp_1= head, *tmp_2, *tmp_3;
	while (tmp_1)
	{
		tmp_2 = tmp_1;
		while(tmp_2->next)
		{ 
			if (tmp_1->degree == ((polynom*)tmp_2->next)->degree)
			{
				tmp_1->coeff += ((polynom*)tmp_2->next)->coeff;
				tmp_3 = tmp_2->next;
				tmp_2->next = ((polynom*)tmp_2->next)->next;
				free(tmp_3);
			}
			else tmp_2 = tmp_2->next;
		}
		tmp_1 = tmp_1->next;
	}	
}

polynom* new_polynom(polynom** head_1, polynom** head_2) //формироание многочлена согласно заданию
{
	polynom* head=NULL, *prev_term=NULL, *tmp_1 = *head_1;
	while (tmp_1)
	{
		polynom* tmp_2 = *head_2;
		while (tmp_2)
		{
			if (tmp_1->degree == tmp_2->degree)
			{
				int max = (tmp_1->coeff > tmp_2->coeff) ? tmp_1->coeff : tmp_2->coeff;
				if (!head)
				{
					head = add_term(head, max, tmp_1->degree);
					prev_term = head;
				}
				else prev_term = add_term(prev_term, max, tmp_1->degree);
			}
			tmp_2 = tmp_2->next;
		}
		tmp_1 = tmp_1->next;
	}
	return head;
}

void print_polynom(polynom* head, char* str) // вывод многочлена на экран
{
	if (!head)return;

	printf("%s: ", str);
	while (head)
	{
		printf("%d*x^%d", head->coeff, head->degree);
		head = head->next;
		if(head) printf("+");
	}
	printf("\n");
}

void clean(polynom** head) // очистка динамической пам€ти
{
	polynom* tmp = *head, *next;

	while (tmp)
	{
		next = tmp->next;
		free(tmp);
		tmp = next;
	}
	*head = NULL;
}

int main()
{
	polynom* L_1 = create_polynom("first");
	is_correct(L_1); // преобразование многочленов
	polynom* L_2 = create_polynom("second");
	is_correct(L_2);
	print_polynom(L_1, "L_1");
	print_polynom(L_2, "L_2");
	polynom* L = new_polynom(&L_1, &L_2);
	print_polynom(L, "L");
	clean(&L_1);
	clean(&L_2);
	clean(&L);
	
	return 0;
}