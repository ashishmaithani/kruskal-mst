/*
Assignment 07, Kruskal Algorithm
Name - Ashish Maithani
Date - April 21, 2015
*/

#include<stdio.h>
#include<stdlib.h>

int vertices,edges;

struct vertex{
	int vrtx;
	int rank;
	struct vertex *parent;
};

struct edge{
	int src,dest,weight;
};

// funtion to compare the weights of two struct edges
int cmpfunc(const void *a,const void *b){
	int v1,v2;
	v1 = ((struct edge *)a)->weight;
	v2 = ((struct edge *)b)->weight;
	return (v1-v2);
}

// Initializes the vertex array
void makeSet(struct vertex *vt){
	int i;
	for(i=0;i<vertices;i++){
		vt[i].vrtx = i;
		vt[i].rank = 0;
		vt[i].parent = &vt[i];
	}
}

// findSet finds the set to which the current vertex belongs
struct vertex * findSet(struct vertex *vrtx){
	if(vrtx->parent != vrtx){
		vrtx->parent = findSet(vrtx->parent);
	}
	return vrtx->parent;
}

// unionSets merges the two vertices to the same set
void unionSets(struct vertex *src,struct vertex *dest){
	if(src->rank == dest->rank){
		dest->parent = src;
		src->rank++;
	}else if(src->rank > dest->rank){
		dest->parent = src;
	}else{
		src->parent = dest;
	}
}

// Implementation of Kruskal algo to determine minimum spanning tree
void kruskal(struct edge *ed,struct vertex *vt){
	int i,totalCost=0;
	struct vertex *srcSet,*destSet;
	makeSet(vt);
	for(i=0;i<edges;i++){
		srcSet = findSet(&vt[ed[i].src]);
		destSet = findSet(&vt[ed[i].dest]);
		if(srcSet->vrtx != destSet->vrtx){
			unionSets(srcSet,destSet);
			totalCost = totalCost + ed[i].weight;
			printf("%d %d %d\n",ed[i].src,ed[i].dest,ed[i].weight);
		}
	}
	printf("Total Cost: %d\n",totalCost);
}

int main(){
	int i;
	scanf("%d",&vertices);
	scanf("%d",&edges);

	struct vertex *vt = malloc((sizeof(struct vertex)) * vertices);
	struct edge *ed = malloc((sizeof(struct edge)) * edges);

	for(i=0;i<edges;i++){
		scanf("%d",&ed[i].src);
		scanf("%d",&ed[i].dest);
		scanf("%d",&ed[i].weight);
	}

//	qksort(ed,0,edges-1);
	qsort(ed,edges,sizeof(struct edge),cmpfunc);
	kruskal(ed,vt);
	free(vt);
	free(ed);
	return 0;
}
