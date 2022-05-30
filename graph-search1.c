#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 10

typedef struct GraphNode{
    int vertex;
    struct GraphNode* link;
}GraphNode;

typedef struct GraphType{
    int n;
    GraphNode* adj_list[MAX_VERTICES];
}GraphType;

void initialize(GraphType* g);
void insert_vertex(GraphType* g);
void insert_edge(GraphType* g,int u,int v);
void print_list(GraphType* g);


int main()
{
	printf("[----- [�ֵ���]  [2019038016] -----]\n"); 
	char command; 
	int vertex;
	int vertex1;
	int vertex2;
	GraphType *g=(GraphType*)malloc(sizeof(GraphType));

	do{
		printf("----------------------------------------------------------------\n");
		printf("                     Singly Linked List                         \n");
		printf("----------------------------------------------------------------\n");
		printf(" Initialize Graph    = z           \n");
		printf(" Insert Vertex       = v           Insert Edge           = e \n");
		printf(" Depth First Search  = d           Breath First Search   = b\n");
		printf(" Print Graph         = p           Quit                  = q\n");
		printf("----------------------------------------------------------------\n");

		printf("Command = ");
		scanf(" %c", &command); //����ڿ��� �޴��� �Է¹޴´�

		switch(command) { //commad�� ���� ���� ����
		case 'z': case 'Z': //command�� z or Z�϶�
			initialize(g);
			break;
		case 'v': case 'V': //command�� i or I�϶�
			insert_vertex(g);
			break;
		case 'd': case 'D': //command�� e or E�϶�
			printf("start vertex");
			break;
		case 'p': case 'P': //command�� d or E�϶�
			print_list(g);
			break; 
		case 'e': case 'E': //command�� n or N�϶�
			printf("Your vertex1 = ");
			scanf("%d", &vertex1); 
			printf("Your &vertex2 = ");
			scanf("%d", &vertex2); 
			insert_edge(g,vertex1,vertex2);		
			break;
		case 'b': case 'B': //command�� n or N�϶�
			printf("start vertex");
			break;
		case 'q': case 'Q': //command�� q or Q�϶�
			free(g);
			break;
		default: //command�� ���� ����� �ٸ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q or Q�϶� �ݺ��� ����

	return 1; //�Լ� ����
}

void initialize(GraphType* g){
    g->n=0;
    for(int i=0;i<MAX_VERTICES;i++)
        g->adj_list[i]=NULL;
}

void insert_vertex(GraphType* g){
    if(((g->n)+1)>MAX_VERTICES){
		printf("vertex is full\n");
        return;
    }
    g->n++;
}


void insert_edge(GraphType* g,int u,int v){
    GraphNode* node;
    if(u>=g->n||v>=g->n){;
        return;
    }
    node= (GraphNode*)malloc(sizeof(GraphNode));
    node->vertex=v;
    node->link=g->adj_list[u];
    g->adj_list[u]=node;
}


void print_list(GraphType* g){
    for(int i=0;i<g->n;i++){
        GraphNode* p=g->adj_list[i];
        printf("vertex %d�� ���� ����Ʈ",i);
        while(p!=NULL){
            printf("->%d",p->vertex);
            p=p->link;
        }
        printf("\n");
    }
}