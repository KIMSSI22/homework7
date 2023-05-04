#include<stdio.h>
#include<stdlib.h>

typedef struct Node {
	int key;  //데이터 변수
	struct Node* llink;  //이전 노드를 가르키는 포인터
	struct Node* rlink;  //다음 노드를 가르키는 포인터
} listNode;

typedef struct Head {
	struct Node* first;  //첫번째 노드를 가르키는 포인터
}headNode;


//함수 선언
int initialize(headNode** h);

int freeList(headNode* h);

int insertNode(headNode* h, int key);
int insertLast(headNode* h, int key);
int insertFirst(headNode* h, int key);
int deleteNode(headNode* h, int key);
int deleteLast(headNode* h);
int deleteFirst(headNode* h);
int invertList(headNode* h);

void printList(headNode* h);


int main()
{
    printf("[----- [김민서] [2022040010] -----]");
	char command;
	int key;
	headNode* headnode=NULL;

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Doubly Linked  List                        \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize    = z           Print         = p \n");
		printf(" Insert Node   = i           Delete Node   = d \n");
		printf(" Insert Last   = n           Delete Last   = e\n");
		printf(" Insert First  = f           Delete First  = t\n");
		printf(" Invert List   = r           Quit          = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command);

		switch(command) {  //입력 받은 command 값에 따른 케이스
		case 'z': case 'Z':
			initialize(&headnode);  //리스트 초기화
			break;
		case 'p': case 'P':
			printList(headnode);  //리스트 출력
			break;
		case 'i': case 'I':
			printf("Your Key = ");
			scanf("%d", &key);
			insertNode(headnode, key);  //노드 삽입
			break;
		case 'd': case 'D':
			printf("Your Key = ");
			scanf("%d", &key);
			deleteNode(headnode, key);  //노드 삭제
			break;
		case 'n': case 'N':
			printf("Your Key = ");
			scanf("%d", &key);
			insertLast(headnode, key);  //리스트 마지막 노드 삽입
			break;
		case 'e': case 'E':
			deleteLast(headnode);  //리스트 마지막 노드 삭제
			break;
		case 'f': case 'F':
			printf("Your Key = ");
			scanf("%d", &key);
			insertFirst(headnode, key);  //리스트 첫 노드 삽입
			break;
		case 't': case 'T':
			deleteFirst(headnode);  //리스트 첫 노드 삭제
			break;
		case 'r': case 'R':
			invertList(headnode);  //리스트 도치
			break;
		case 'q': case 'Q':
			freeList(headnode);  //메모리 할당 해제 
			break;
		default:
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q');

	return 1;
}


int initialize(headNode** h) {   //리스트 초기화

	if(*h != NULL)
		freeList(*h);

	*h = (headNode*)malloc(sizeof(headNode));
	(*h)->first = NULL;  //첫번째 포인터 초기화
	return 1;
}

int freeList(headNode* h){   //리스트 메모리 해제

	listNode* p = h->first;

	listNode* prev = NULL;  //구조체 해제
	while(p != NULL) {
		prev = p;
		p = p->rlink;
		free(prev);
	}
	free(h);
	return 0;
}


void printList(headNode* h) {   //리스트 출력
	int i = 0;
	listNode* p;

	printf("\n---PRINT\n");

	if(h == NULL) {  //비어있을 때
		printf("Nothing to print....\n");
		return;
	}

	p = h->first;

	while(p != NULL) {  //안비었을 때
		printf("[ [%d]=%d ] ", i, p->key);
		p = p->rlink;
		i++;
	}

	printf("  items = %d\n", i);
}



int insertLast(headNode* h, int key) { //마지막 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = NULL;
	node->llink = NULL;

	if (h->first == NULL)  //리스트가 비어있을 때
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
	while(n->rlink != NULL) {  //안비어있을 때
		n = n->rlink;
	}
	n->rlink = node;
	node->llink = n;
	return 0;
}



int deleteLast(headNode* h) {  //마지막 노드 삭제

	if (h->first == NULL)
	{
		printf("nothing to delete.\n");
		return 0;
	}

	listNode* n = h->first;
	listNode* trail = NULL;

	if(n->rlink == NULL) {  //비었을 때
		h->first = NULL;
		free(n);
		return 0;
	}

	while(n->rlink != NULL) {  //안비었을 때
		n = n->rlink;
	}

	trail->rlink = NULL;
	free(n);

	return 0;
}


int insertFirst(headNode* h, int key) {  //첫 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->rlink = node->llink = NULL;

	if(h->first == NULL)  //비었을 때
	{
		h->first = node;
		return 1;
	}

	node->rlink = h->first;
	node->llink = NULL;

	listNode *p = h->first;
	p->llink = node;
	h->first = node;

	return 0;
}

int deleteFirst(headNode* h) {  //첫 노드 삭제

	if (h->first == NULL)  //비었을 때
	{
		printf("nothing to delete.\n");
		return 0;
	}
	listNode* n = h->first;
	h->first = n->rlink;

	free(n);

	return 0;
}

int invertList(headNode* h) {  //리스트 도치


	if(h->first == NULL) {  //비었을 때
		printf("nothing to invert...\n");
		return 0;
	}
	listNode *n = h->first;
	listNode *trail = NULL;
	listNode *middle = NULL;

	while(n != NULL){  //안비었을 때
		trail = middle;
		middle = n;
		n = n->rlink;
		middle->rlink = trail;
		middle->llink = n;
	}

	h->first = middle;

	return 0;
}


int insertNode(headNode* h, int key) {  //새로운 노드 삽입

	listNode* node = (listNode*)malloc(sizeof(listNode));
	node->key = key;
	node->llink = node->rlink = NULL;

	if (h->first == NULL)  //비었을 때
	{
		h->first = node;
		return 0;
	}

	listNode* n = h->first;
 
	while(n != NULL) {  //안비었을 때
		if(n->key >= key) {
			if(n == h->first) {
				insertFirst(h, key);
			} else { 
				node->rlink = n;
				node->llink = n->llink;
				n->llink->rlink = node;
			}
			return 0;
		}

		n = n->rlink;
	}

	insertLast(h, key);
	return 0;
}


int deleteNode(headNode* h, int key) {  //노드 삭제

	if (h->first == NULL)  //비었을 때
	{
		printf("nothing to delete.\n");
		return 1;
	}

	listNode* n = h->first;

	while(n != NULL) {  //안비었을 때
		if(n->key == key) {
			if(n == h->first) {
				deleteFirst(h);
			} else if (n->rlink == NULL){
				deleteLast(h);
			} else {
				n->llink->rlink = n->rlink;
				n->rlink->llink = n->llink;
				free(n);
			}
			return 1;
		}

		n = n->rlink;
	}

	printf("cannot find the node for key = %d\n", key);
	return 1;
}