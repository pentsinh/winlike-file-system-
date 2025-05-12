#include <stdio.h>
#include <stdlib.h>
struct node
{
	int x;
	struct node* next;
};
struct node* find_del(struct node* head, struct node** pm);
void main()
{
	struct node* head, * tail, ** pm, * p;
	int i;
	head = NULL;
	tail = NULL;
	for (i = 0; i < 3; i++)
	{
		int a[10] = { 2,0,2,4,1,2,2,8 };
		p = (struct node*)malloc(sizeof(struct node));
		if (p == NULL)
			return -1;
		p->x = a[i];
		printf("%d", p->x);
		if (head == NULL)
		{
			head = p;
			tail = p;
		}
		else
		{
			tail->next = p;
			tail = p;
		}
	}
	p = head;
	while (p != NULL)
	{
		printf("%d\n", p->x);
		p = p->next;
	}
}
struct node* find_del(struct node* head, struct node** pm)
{
	struct node* p1, * p2, * pmax, * pre;
	if (head == NULL)
		return NULL;
	pmax = head;
	p1 = p2 = pmax;
	while (p1)
	{
		if (p1->x > pmax->x)
		{
			pre = p2;
			pmax = p1;
		}
		p2 = p1;
		p1 = p1->next;
	}
	if (pmax == head)
		head = pmax->next;
	else
		pre->next=pmax->next;
	pm = pmax;
	printf("max is %d", (*pm)->x);
	return head;
}