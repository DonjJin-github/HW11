#include<stdio.h>
#include<stdlib.h>
#define MAX_VERTICES 10 //vertex�� �ִ�� ����
#define FALSE 0
#define TRUE 1

int visited_BFS[MAX_VERTICES]; //BFS�� �湮���θ� ������ �迭
int visited_DFS[MAX_VERTICES]; //DFS�� �湮���θ� ������ �迭
typedef struct GraphNode{ //�׷�������� ����ä
    int vertex;
    struct GraphNode* link;
}GraphNode;

typedef struct GraphType{ //�׷���Ÿ���� ����ü
    int n;
    GraphNode* adj_list[MAX_VERTICES];
}GraphType;

typedef struct QueueType{ //ť ����ü
    int element[MAX_VERTICES];
    int front,rear;
	int size;
}QueueType;

void initialize(GraphType* g); //�׷���Ÿ���� �ʱ�ȭ �ϴ� �Լ�
void insert_vertex(GraphType* g); //�׷����� vertex�� �߰��ϴ� �Լ�
void insert_edge(GraphType* g,int u,int v); //�׷����� vertex�� �����Ű�� �Լ�
void print_list(GraphType* g); //�׷����� ����ϴ� �Լ�
void reset_DFS(); //visited_DFS�� �ʱ�ȭ �ϴ� �Լ�
void reset_BFS(); //visited_BFS�� �ʱ�ȭ �ϴ� �Լ�
void dfs(); //���� �켱 Ž�� �Լ�
void bfs(); //���� �켱 Ž�� �Լ�

int main()
{
	printf("[----- [�ֵ���]  [2019038016] -----]\n"); 
	char command; 
	int vertex;
	int vertex1;
	int vertex2;
	GraphType *g=(GraphType*)malloc(sizeof(GraphType)); //�׷���g������ �����Ҵ�

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
			initialize(g); //initialize�Լ��� ȣ���Ͽ� g�� �ʱ�ȭ
			break;
		case 'v': case 'V': //command�� v or V�϶�
			insert_vertex(g); //insert_vertex�Լ��� ȣ���Ͽ� �׷��� g�� vertex�� �߰�
			break;
		case 'd': case 'D': //command�� d or D�϶�
			printf("start vertex");
			scanf("%d", &vertex); //����ڿ��� ó�� Ž���� vertex�� �Է¹޴´�
			dfs(g,vertex); //dfs�Լ��� ȣ���Ͽ� ���̿켱Ž���� �Ѵ�
			reset_DFS(); //visited_DFS�� �ʱ�ȭ
			break;
		case 'p': case 'P': //command�� p or P�϶�
			print_list(g); //print_list�Լ��� ȣ���Ͽ� �׷���g�� ����Ѵ�
			break; 
		case 'e': case 'E': //command�� e or E�϶�
			printf("Your vertex1 = "); //����ڿ��� ������ �ΰ��� vertex�� �Է¹޴´�
			scanf("%d", &vertex1); 
			printf("Your &vertex2 = ");
			scanf("%d", &vertex2); 
			insert_edge(g,vertex1,vertex2);	//insert_edge�Լ��� ȣ���Ͽ� vertex�� �����Ų��
			break;
		case 'b': case 'B': //command�� b or B�϶�
			printf("start vertex"); //����ڿ��� ó�� Ž���� vertex�� �Է¹޴´�
			scanf("%d", &vertex); 
			bfs(g,vertex);//bfs�Լ��� ȣ���Ͽ� ���̿켱Ž���� �Ѵ�
			reset_BFS(); //visited_BFS�� �ʱ�ȭ
			break;
		case 'q': case 'Q': //command�� q or Q�϶�
			free(g); //g�� �޸� ����
			break;
		default: //command�� ���� ����� �ٸ���
			printf("\n       >>>>>   Concentration!!   <<<<<     \n");
			break;
		}

	}while(command != 'q' && command != 'Q'); //command�� q or Q�϶� �ݺ��� ����

	return 1; //�Լ� ����
}

void initialize(GraphType* g){
    g->n=0; //g�� n�� 0����
    for(int i=0;i<MAX_VERTICES;i++) //�ݺ����� ����Ͽ� g->adglist���� ��� NULL�� �ʱ�ȭ
        g->adj_list[i]=NULL;
}

void reset_DFS(){ 
	for(int i=0;i<MAX_VERTICES;i++) //�ݺ����� ����Ͽ� visited_DFS�� 0����
		visited_DFS[i]=0;
}

void reset_BFS()
{
	for(int i=0;i<MAX_VERTICES;i++) //�ݺ����� ����Ͽ� visited_BFS�� 0����
		visited_BFS[i]=0;
}
void insert_vertex(GraphType* g){
    if(((g->n)+1)>MAX_VERTICES){ //�׷����� vertex�� ���� á����
		printf("vertex is full\n");
        return;
    }
    g->n++; //g�� n�� 1���� ��Ų��
}
void initQueue(QueueType *q){ 
	q->size=0; //q�� size 0���� �ʱ�ȭ
	q->front=-1; //q�� front -1���� �ʱ�ȭ
	q->rear=-1; //q�� rear -1���� �ʱ�ȭ
	for(int i=0;i<MAX_VERTICES;i++) //�ݺ����� ����Ͽ� q�� element 0���� �ʱ�ȭ
		q->element[i]=0;
}

void enqueue(QueueType *q,int item){ 
	q->element[++(q->rear)]=item; //q��element[rear+1]�� item ����
	q->size++; //q�� size1����
}

int dequeue(QueueType *q){
	int item; 
	item=q->element[++(q->front)];//item�� q�� element[front+1]����
	q->size--; //q�� size����
	return item; //item ����
}

void insert_edge(GraphType* g,int u,int v){
    GraphNode* node; //GraphNode ������ node����
    if(u>=g->n||v>=g->n){;
        return;
    }
    node= (GraphNode*)malloc(sizeof(GraphNode)); //node�� �����Ҵ�
    node->vertex=v; //node�� vertex�� V����
    node->link=g->adj_list[u]; //node�� link�� g�� adj_list[u]����
    g->adj_list[u]=node; //g�� adj_list[u]�� node����
}

void dfs(GraphType *g, int v){ 
	GraphNode *w; //GraphNode ������ w����
	visited_DFS[v]=1; //ó�� Ž���� ������ vertex�� �湮Ƚ�� 1����
	printf("%d", v); 
	for(w=g->adj_list[v];w;w=w->link){ //�ݺ����� ����Լ��� Ȱ���Ͽ� ����� vertex�� ����ϰ� �湮Ƚ�� ����
		if(!visited_DFS[w->vertex])
			dfs(g,w->vertex);
	}
}

void bfs(GraphType *g, int v){
	GraphNode *w; //GraphNode ������ w����
	QueueType q; //QueueType q ����
	initQueue(&q); //q �ʱ�ȭ
	visited_BFS[v]=TRUE; //ó�� Ž���� ������ vertex�� �湮Ƚ�� TRUE����
	printf("%d",v); 
	enqueue(&q,v); //v�� enqueu�Լ��� ȣ���Ͽ� q�� element�� ����

	while(q.size!=0){ //�ݺ����� ����Ͽ� ����� vertex�� ����ϰ� �湮Ƚ�� ���� 
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
    for(int i=0;i<g->n;i++){ //�ݺ����� ����Ͽ� �׷����� ����Ѵ�
        GraphNode* p=g->adj_list[i]; //GraphNode ������ p���� �� g�� adj_list[i]����
        printf("vertex %d�� ���� ����Ʈ",i);
        while(p!=NULL){ //�ݺ����� ����Ͽ� p�� ����� vertex���� ���
            printf("->%d",p->vertex);
            p=p->link;
        }
        printf("\n");
    }
}