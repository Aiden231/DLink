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

// 초기화
void init(DlistNode* phead)
{
	phead->llink = phead;
	phead->rlink = phead;
}

// 삽입연산
void dinsert(DlistNode* before, const char* data)
{
	DlistNode* newnode = (DlistNode*)malloc(sizeof(DlistNode));
	strcpy(newnode->data, data);
	newnode->llink = before;
	newnode->rlink = before->rlink;
	before->rlink->llink = newnode;
	before->rlink = newnode;
}

// 삭제연산
void ddelete(DlistNode *head,DlistNode *removed)
{
	if (removed == head) return;
	removed->llink->rlink = removed->rlink;
	removed->rlink->llink = removed->llink;
	free(removed);
}

// 출력
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
	init(head); // 리스트 초기화
	char enter_menu; // 메뉴 입력 변수
	char fruit_insert[20]; // 과일 이름 변수

	DlistNode* current = head; // 현재 위치 저장

	do {
		printf("-----Memu-----\n");
		printf("n) next fruit(앞으로)\n");
		printf("p) previous fruit(뒤로)\n");
		printf("d) delete the current fruit(삭제)\n");
		printf("i) insert fruit after current fruit(추가)\n");
		printf("o) output the fruit list(output [0] at the end of the currently selected fruit)(출력)\n");
		printf("e) exit(종료)\n");
		printf("---------------\n");

		printf("Select a menu(메뉴 선택) : ");
		scanf_s("%c", &enter_menu);

		// 앞으로
		if (enter_menu == 'n')
		{
			// 비어있지 않을 경우 앞으로 이동
			if (head->rlink != head)
			{
				current = current->rlink;

				// 앞으로 갔는데 헤드인 경우 한 번 더 이동
				if (current == head)
				{
					current = current->rlink;
				}
				printf("\n");
			}
			// 비어있는 경우 앞으로 이동 X
			else
			{
				printf("과일 리스트가 비어있습니다.\n");
				printf("\n");
			}
		}
		// 뒤로
		else if (enter_menu == 'p')
		{
			if (head->llink != head)
			{
				current = current->llink;
				
				// 뒤로 갔는데 헤드인 경우 한 번 더 이동
				if (current == head)
				{
					current = current->llink;
				}
				printf("\n");
			}
			else
			{
				printf("과일 리스트가 비어있습니다.\n");
				printf("\n");
			}
		}
		// 삭제
		else if (enter_menu == 'd')
		{
			// 비어있지 않은 경우 삭제
			if (head->rlink != head)
			{
				DlistNode* temp = current; // 현재 선택한 값 삭제
				current = current->rlink; // 선택한 값 앞으로 변경
				ddelete(head, temp);
				printf("\n");
			}
			// 비어있는 경우 삭제 X
			else
			{
				printf("과일 리스트가 비어있어서 삭제할 수 없습니다.\n");
				printf("\n");
			}
		}
		// 추가
		else if (enter_menu == 'i')
		{
			printf("추가 할 과일 이름을 입력하세요 : ");
			scanf_s("%s",fruit_insert,sizeof(fruit_insert));
			printf("\n");

			// 비어있는 경우
			if (head->rlink == head)
			{
				dinsert(current, fruit_insert);
				current = current->rlink;
			}
			// 비어있지 않은 경우
			else
			{
				dinsert(current, fruit_insert);
			}
		}
		// 출력
		else if (enter_menu == 'o')
		{
			print_dlist(head, current);
		}
		// 종료
		else if (enter_menu == 'e')
		{
			break;
		}
		// 메뉴 오입력 시
		else
		{
			printf("Invalid menu(다시 입력해 주세요)\n");
			printf("\n");
		}

		getchar();
	} while (1);

	return 0;
}