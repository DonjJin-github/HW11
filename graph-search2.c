#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 10

int visited_DFS[MAX_VERTICES];
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
void reset_DFS();
void dfs();

int main()
{
	printf("[----- [최동진]  [2019038016] -----]\n"); 
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
		scanf(" %c", &command); //사용자에게 메뉴를 입력받는다

		switch(command) { //commad의 값에 따라 실행
		case 'z': case 'Z': //command가 z or Z일때
			initialize(g);
			break;
		case 'v': case 'V': //command가 i or I일때
			insert_vertex(g);
			break;
		case 'd': case 'D': //command가 e or E일때
			printf("start vertex");
			scanf("%d", &vertex); 
			dfs(g,vertex);
			reset_DFS();
			break;
		case 'p': case 'P': //command가 d or E일때
			print_list(g);
			break; 
		case 'e': case 'E': //command가 n or N일때
			printf("Your vertex1 = ");
			scanf("%d", &vertex1); 
			printf("Your &vertex2 = ");
			scanf("%d", &vertex2); 
			insert_edge(g,vertex1,vertex2);		
			break;
		case 'b': case 'B': //command가 n or N일때
			printf("start vertex");
			break;
		case 'q': case 'Q': //command가 q or Q일때
			free(g);
			break;
		default: //command가 위의 값들과 다를때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q or Q일때 반복문 종료

	return 1; //함수 종료
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

void dfs(GraphType *g, int v){
	GraphNode *w;
	visited_DFS[v]=1;
	printf("%d", v);
	for(w=g->adj_list[v];w;w=w->link){
		if(!visited_DFS[w->vertex])
			dfs(g,w->vertex);
	}
}


void print_list(GraphType* g){
    for(int i=0;i<g->n;i++){
        GraphNode* p=g->adj_list[i];
        printf("vertex %d의 인접 리스트",i);
        while(p!=NULL){
            printf("->%d",p->vertex);
            p=p->link;
        }
        printf("\n");
    }
}