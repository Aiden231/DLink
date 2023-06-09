#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char element;

typedef struct DlistNode {
	element data[20];
	struct DlistNode* llink;
	struct DlistNode* rlink;
}DlistNode;

// �ʱ�ȭ
void init(DlistNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// ���Կ���
void dinsert(DlistNode* before, const char* data)
{
	DlistNode* newnode = (DlistNode*)malloc(sizeof(DlistNode));
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// ��������
void ddelete(DlistNode *head,DlistNode *removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

// ���
void print_dlist(DlistNode* phead, DlistNode* current)
{
	DlistNode* p;
	for (p = phead->rlink; p != phead; p = p->rlink)
	{
		if (p == current) {
			printf("%s [0]\n", p->data);
		}
		else {
			printf("%s\n", p->data);
		}
	}
	printf("\n");
}

int main()
{
	DlistNode* head = (DlistNode*)malloc(sizeof(DlistNode));
	init(head); // ����Ʈ �ʱ�ȭ
	char enter_menu; // �޴� �Է� ����
	char fruit_insert[20]; // ���� �̸� ����

	DlistNode* current = head; // ���� ��ġ ����

	do {
		printf("-----Memu-----\n");
		printf("n) next fruit(������)\n");
		printf("p) previous fruit(�ڷ�)\n");
		printf("d) delete the current fruit(����)\n");
		printf("i) insert fruit after current fruit(�߰�)\n");
		printf("o) output the fruit list(output [0] at the end of the currently selected fruit)(���)\n");
		printf("e) exit(����)\n");
		printf("---------------\n");

		printf("Select a menu(�޴� ����) : ");
		scanf_s("%c", &enter_menu);

		// ������
		if (enter_menu == 'n')
		{
			// ������� ���� ��� ������ �̵�
			if (head->rlink != head)
			{
				current = current->rlink;

				// ������ ���µ� ����� ��� �� �� �� �̵�
				if (current == head)
				{
					current = current->rlink;
				}
				printf("\n");
			}
			// ����ִ� ��� ������ �̵� X
			else
			{
				printf("���� ����Ʈ�� ����ֽ��ϴ�.\n");
				printf("\n");
			}
		}
		// �ڷ�
		else if (enter_menu == 'p')
		{
			if (head->llink != head)
			{
				current = current->llink;
				
				// �ڷ� ���µ� ����� ��� �� �� �� �̵�
				if (current == head)
				{
					current = current->llink;
				}
				printf("\n");
			}
			else
			{
				printf("���� ����Ʈ�� ����ֽ��ϴ�.\n");
				printf("\n");
			}
		}
		// ����
		else if (enter_menu == 'd')
		{
			// ������� ���� ��� ����
			if (head->rlink != head)
			{
				DlistNode* temp = current; // ���� ������ �� ����
				current = current->rlink; // ������ �� ������ ����
				ddelete(head, temp);
				printf("\n");
			}
			// ����ִ� ��� ���� X
			else
			{
				printf("���� ����Ʈ�� ����־ ������ �� �����ϴ�.\n");
				printf("\n");
			}
		}
		// �߰�
		else if (enter_menu == 'i')
		{
			printf("�߰� �� ���� �̸��� �Է��ϼ��� : ");
			scanf_s("%s",fruit_insert,sizeof(fruit_insert));
			printf("\n");

			// ����ִ� ���
			if (head->rlink == head)
			{
				dinsert(current, fruit_insert);
				current = current->rlink;
			}
			// ������� ���� ���
			else
			{
				dinsert(current, fruit_insert);
			}
		}
		// ���
		else if (enter_menu == 'o')
		{
			print_dlist(head, current);
		}
		// ����
		else if (enter_menu == 'e')
		{
			break;
		}
		// �޴� ���Է� ��
		else
		{
			printf("Invalid menu(�ٽ� �Է��� �ּ���)\n");
			printf("\n");
		}

		getchar();
	} while (1);

	return 0;
}