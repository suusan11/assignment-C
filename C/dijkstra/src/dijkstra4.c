/*
 * dijkstra4.c
 *
 *  Created on: 2018/06/04
 *      Author: miiiiiiiiiiie
 */


#include <stdio.h>
#include <stdlib.h>

#define INF 3200;

int getNumberOfNodes(){
	return 7;
}
int getNumberOfEdges(){
	return 9;
}
char* getNodes(){
	return "A,B,C,D,E,F,G";//these are the nodes of the graph!
}
char* getEdges(){
	return "A_B_6,B_E_10,C_A_2,C_D_3,C_E_7,D_B_4,E_F_7,F_G_5,G_D_10";
}
struct Node {
	struct Node* from;
	int visited;
	char name;
	int cost;
	struct Node* next;
	struct Edge* edge;
};

struct Edge {
	int distance;
	struct Node* to;
	struct Edge* next;
};



//void showNodes(struct Node *nodes) {
//   	    printf("Show Nodes-----------\n");
//   	    while (nodes != NULL) {
//   	        printf("id = %c\n", nodes->name);
//   	        //printf("prevNode = %d\n", nodes->prevNode);
//   	        while (nodes->edge != NULL) {
//   	            printf("%c %d\n", nodes->edge->to->name, nodes->edge->distance);
//   	            nodes->edge = nodes->edge->next;
//   	        }
//   	        nodes = nodes->next;
//   	    }
//   	}


void main (void) {

	   int i=0;
	   char getNodes[] = {'A','B','C','D','E','F','G'};
	   char getEdges[] = {"A_B_6,B_E_10,C_A_2,C_D_3,C_E_7,D_B_4,E_F_7,F_G_5,G_D_10"};
	   int e = getNumberOfEdges();
	   int n = getNumberOfNodes();
	   char first[] = {'A','B','C','C','C','D','E','F','G'};
	   char second[] = {'B','E','A','D','E','B','F','G','D'};
	   int value[] = {6,10,2,3,7,4,7,5,10};

	   printf("These are Nodes %s ", getNodes);
	   printf("\n");

	   char source;
	   printf("Enter Source: ");
	   scanf(" %c", &source);

	   char  destination;
	   printf("Enter Destination: ");
	   scanf(" %c", &destination);


	   struct Node* head;
	   struct Node* current;
	   struct Edge* edgecurrent;
	   //Pointer of Node
	   struct Node* p;
	   //Pointer of Edge
	   struct Edge* pe;
	   struct Node* findMin;
	   struct Node* temp;
	   struct Edge* nextEdge;
	   struct Node* findPath;
	   int pathCost;
	   char path[n+1];

	   //Create area which Node of current
	   current = (struct Node*)malloc(sizeof(struct Node));
	   head = current;

	   //Create Node
	   for(i = 0; i < n; i++) {
		 //reset current value
		   current->name = getNodes[i];
		   current->cost = INF;
		   current->visited = 0;
		   current->edge = NULL;

		   if(i < n-1){
		   //Create area which Node of current of next
		   current->next = (struct Node*)malloc(sizeof(struct Node));
		   //Change current
		   current = current->next;
		   }
	    }

	   //Last current - NULL
	   	current->next = NULL;

	   	//Create Edge
	   	for(i = 0; i < e; i++) {
	   		//Create area of edge and add value
	   		edgecurrent = (struct Edge*)malloc(sizeof(struct Edge));
	   		p = head;
	   		while(p->name != second[i]){
	   			//find p-next
	   			p = p->next;
	   		}

	   		edgecurrent->to = p;
	   		edgecurrent->distance = value[i];
	   		edgecurrent->next = NULL;

	   		p=head;
	   		while(p->name != first[i]){
	   			p = p->next;
	   		}
	   		if(p->edge == NULL){
	   			p->edge = edgecurrent;
	   		}else{
	   			pe = p->edge;
	   			while(pe->next != NULL){
	   			pe = pe->next;
	   			}
	   			pe->next = edgecurrent;
	   		}
	   	}

//	   	showNodes(head);



	   	//dijkstra
	   	int min = INF;
		p = head;
		//Repeat until Node-next-NULL
		while(p != NULL) {
			if (p->name == source) {
				p->cost = 0;
				p->visited = 1;

				break;
			   }
			 p = p->next;
		}
		temp = p;
		for(i = 1; i < n; i++){
			nextEdge = temp->edge;
			if(nextEdge != NULL){
				while(nextEdge != NULL){
					if(temp->cost + nextEdge->distance < nextEdge->to->cost){
						nextEdge->to->cost = temp->cost + nextEdge->distance;
						nextEdge->to->from = temp;
					}
					nextEdge = nextEdge->next;
				}
			}
			findMin = head;
			min = INF;
			while(findMin != NULL){
				if(findMin->cost < min+1 && findMin->visited == 0) {
					min = findMin->cost;
					temp = findMin;
				}
				findMin = findMin->next;
			}
			temp->visited = 1;
		}

		//find shortest path and the cost
		 findPath = head;
		while(findPath->name != destination) {
			findPath = findPath->next;
		}
		pathCost = findPath->cost;

		i = 0;
		memset(path, '\0', n+1);
		while(findPath->name != source){
			path[i] = findPath->name;
			i++;
			findPath = findPath->from;
			if(findPath == NULL && findPath->name != source){
				//couldn't find any path
				i = 0;
				break;
			}
		}
		if(i > 0) {
		path[i] = findPath->name;
		}

		printf("The shortest path %c to %c is \n", source, destination);
		if(i != 0) {
			for(; i >= 0; i--){
				printf("===> %c ", path[i]);
			}
		}else {
			printf("HAVEN'T PATH");
		}
		printf("\nThe total cost is %d\n", pathCost);



}
