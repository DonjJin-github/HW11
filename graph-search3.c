#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 10 //vertex의 최대수 지정
#define FALSE 0
#define TRUE 1

int visited_BFS[MAX_VERTICES]; //BFS의 방문여부를 저장할 배열
int visited_DFS[MAX_VERTICES]; //DFS의 방문여부를 저장할 배열
typedef struct GraphNode{ //그래프노드의 구조채
    int vertex;
    struct GraphNode* link;
}GraphNode;

typedef struct GraphType{ //그래프타입의 구조체
    int n;
    GraphNode* adj_list[MAX_VERTICES];
}GraphType;

typedef struct QueueType{ //큐 구조체
    int element[MAX_VERTICES];
    int front,rear;
	int size;
}QueueType;

void initialize(GraphType* g); //그래프타입을 초기화 하는 함수
void insert_vertex(GraphType* g); //그래프에 vertex를 추가하는 함수
void insert_edge(GraphType* g,int u,int v); //그래프의 vertex를 연결시키는 함수
void print_list(GraphType* g); //그래프를 출력하는 함수
void reset_DFS(); //visited_DFS를 초기화 하는 함수
void reset_BFS(); //visited_BFS를 초기화 하는 함수
void dfs(); //깊이 우선 탐색 함수
void bfs(); //넓이 우선 탐색 함수

int main()
{
	printf("[----- [최동진]  [2019038016] -----]\n"); 
	char command; 
	int vertex;
	int vertex1;
	int vertex2;
	GraphType *g=(GraphType*)malloc(sizeof(GraphType)); //그래프g선언후 동적할당

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
			initialize(g); //initialize함수를 호출하여 g를 초기화
			break;
		case 'v': case 'V': //command가 v or V일때
			insert_vertex(g); //insert_vertex함수를 호출하여 그래프 g에 vertex를 추가
			break;
		case 'd': case 'D': //command가 d or D일때
			printf("start vertex");
			scanf("%d", &vertex); //사용자에게 처음 탐색할 vertex를 입력받는다
			dfs(g,vertex); //dfs함수를 호출하여 깊이우선탐색을 한다
			reset_DFS(); //visited_DFS를 초기화
			break;
		case 'p': case 'P': //command가 p or P일때
			print_list(g); //print_list함수를 호출하여 그래프g를 출력한다
			break; 
		case 'e': case 'E': //command가 e or E일때
			printf("Your vertex1 = "); //사용자에게 연결할 두개의 vertex를 입력받는다
			scanf("%d", &vertex1); 
			printf("Your &vertex2 = ");
			scanf("%d", &vertex2); 
			insert_edge(g,vertex1,vertex2);	//insert_edge함수를 호출하여 vertex를 연결시킨다
			break;
		case 'b': case 'B': //command가 b or B일때
			printf("start vertex"); //사용자에게 처음 탐색할 vertex를 입력받는다
			scanf("%d", &vertex); 
			bfs(g,vertex);//bfs함수를 호출하여 넓이우선탐색을 한다
			reset_BFS(); //visited_BFS를 초기화
			break;
		case 'q': case 'Q': //command가 q or Q일때
			free(g); //g의 메모리 해제
			break;
		default: //command가 위의 값들과 다를때
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command가 q or Q일때 반복문 종료

	return 1; //함수 종료
}

void initialize(GraphType* g){
    g->n=0; //g의 n에 0저장
    for(int i=0;i<MAX_VERTICES;i++) //반복문을 사용하여 g->adglist들을 모두 NULL로 초기화
        g->adj_list[i]=NULL;
}

void reset_DFS(){ 
	for(int i=0;i<MAX_VERTICES;i++) //반복문을 사용하여 visited_DFS에 0저장
		visited_DFS[i]=0;
}

void reset_BFS()
{
	for(int i=0;i<MAX_VERTICES;i++) //반복문을 사용하여 visited_BFS에 0저장
		visited_BFS[i]=0;
}
void insert_vertex(GraphType* g){
    if(((g->n)+1)>MAX_VERTICES){ //그래프의 vertex가 가득 찼을때
		printf("vertex is full\n");
        return;
    }
    g->n++; //g의 n을 1증가 시킨다
}
void initQueue(QueueType *q){ 
	q->size=0; //q의 size 0으로 초기화
	q->front=-1; //q의 front -1으로 초기화
	q->rear=-1; //q의 rear -1으로 초기화
	for(int i=0;i<MAX_VERTICES;i++) //반복문을 사용하여 q의 element 0으로 초기화
		q->element[i]=0;
}

void enqueue(QueueType *q,int item){ 
	q->element[++(q->rear)]=item; //q의element[rear+1]에 item 저장
	q->size++; //q의 size1증가
}

int dequeue(QueueType *q){
	int item; 
	item=q->element[++(q->front)];//item에 q의 element[front+1]저장
	q->size--; //q의 size감소
	return item; //item 리턴
}

void insert_edge(GraphType* g,int u,int v){
    GraphNode* node; //GraphNode 포인터 node선언
    if(u>=g->n||v>=g->n){;
        return;
    }
    node= (GraphNode*)malloc(sizeof(GraphNode)); //node를 동적할당
    node->vertex=v; //node의 vertex에 V저장
    node->link=g->adj_list[u]; //node의 link에 g의 adj_list[u]저장
    g->adj_list[u]=node; //g의 adj_list[u]에 node저장
}

void dfs(GraphType *g, int v){ 
	GraphNode *w; //GraphNode 포인터 w선언
	visited_DFS[v]=1; //처음 탐색을 시작한 vertex의 방문횟수 1저장
	printf("%d", v); 
	for(w=g->adj_list[v];w;w=w->link){ //반복문과 재귀함수를 활용하여 연결된 vertex를 출력하고 방문횟수 증가
		if(!visited_DFS[w->vertex])
			dfs(g,w->vertex);
	}
}

void bfs(GraphType *g, int v){
	GraphNode *w; //GraphNode 포인터 w선언
	QueueType q; //QueueType q 선언
	initQueue(&q); //q 초기화
	visited_BFS[v]=TRUE; //처음 탐색을 시작한 vertex에 방문횟수 TRUE저장
	printf("%d",v); 
	enqueue(&q,v); //v를 enqueu함수를 호출하여 q의 element에 저장

	while(q.size!=0){ //반복문을 사용하여 연결된 vertex를 출력하고 방문횟수 증가 
		v=dequeue(&q);
		for(w=g->adj_list[v];w;w=w->link){
		if(!visited_BFS[w->vertex]){
			visited_BFS[w->vertex]=TRUE;
			printf("%d ",w->vertex);
			enqueue(&q,w->vertex);
		}
	}
	}
}

void print_list(GraphType* g){ 
    for(int i=0;i<g->n;i++){ //반복문을 사용하여 그래프를 출력한다
        GraphNode* p=g->adj_list[i]; //GraphNode 포인터 p선언 후 g의 adj_list[i]저장
        printf("vertex %d의 인접 리스트",i);
        while(p!=NULL){ //반복문을 사용하여 p에 연결된 vertex들을 출력
            printf("->%d",p->vertex);
            p=p->link;
        }
        printf("\n");
    }
}