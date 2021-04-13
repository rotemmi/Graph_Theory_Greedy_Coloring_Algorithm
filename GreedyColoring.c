#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include "functions.h"

void main()
{
	GreedyColoring(); // calling greedy coloring function
}

void GreedyColoring()
{
	//calling for each funtion
	int k, i, numOfEdges;
	Interval ** arr;
	printf("Please input k\n");
	scanf("%d", &k);
	arr = inputIntervals(k);
	printIntervalFamily(arr, k);
	quick_sort(arr, 0, k - 1);
	numOfEdges = sumEdges(arr, k);
	printf("G Edges = %d\n", numOfEdges);
	printf("Maximum Degree of G = %d\n", degMaxG);
	printf("Minimum Degree of G = %d\n", degMinG);
	setColors(arr, k);
	printf("Chromatic Number of G = %d\n", chromatic);
	printf("G's Complements Edges = %d\n", ((k*(k - 1)) / 2) - numOfEdges);
	printf("Maximum Degree of G's Complements = %d\n", k - 1 - degMinG);
	printf("Minimum Degree of G's Complements = %d\n", k - 1 - degMaxG);
	printColorArray(arr, k);
	printf("\n");
}

//return a pointer to a family of intervals
Interval ** inputIntervals(int size)
{
	int i;
	Interval ** arr;
	arr = (Interval **)malloc(sizeof(Interval*)*size);
	printf("You will now be asked to insert a family of %d intervals\n", size);
	for (i = 0; i < size; i++)
	{
		printf("%dth Interval: ", i + 1);
		arr[i] = (Interval *)malloc(sizeof(Interval));
		scanf("%d%d", &(arr[i]->begin), &(arr[i]->end));
		arr[i]->color = 0;
		arr[i]->deg = 0;
	}
	return arr;
}

//Function will print family of interval, as asked
void printIntervalFamily(Interval ** arr, int size)
{
	int i;
	printf("The Intervals family is:\n");
	for (i = 0; i < size - 1; i++)
	{
		printf("[%d,%d],", (arr[i]->begin), (arr[i]->end));
	}
	printf("[%d,%d]\n", (arr[i]->begin), (arr[i]->end));
}

//Function will get 2 intervals as parameters, and swap between them
void swap(Interval *a, Interval *b)
{
	Interval t = *a;
	*a = *b;
	*b = t;
}

//the function is used at quick sort function to sort array of intervals
int partition(Interval **a, int left, int right)
{
	int i, last = left; //pivot=a[left]
	if (left < right)
	{
		for (i = left + 1; i <= right; i++)
			if (a[i]->begin <= a[left]->begin)
				swap(a[++last], a[i]);
		swap(a[left], a[last]);
	}
	return last;
}

//function that sort the array of intervals, by using the partition function - essential for greedy coloring
void quick_sort(Interval **a, int first, int last)
{
	int pos;
	if (first < last)
	{
		pos = partition(a, first, last);
		quick_sort(a, first, pos - 1);
		quick_sort(a, pos + 1, last);
	}
}

//returning 1 or 0 if two intervals are connected to each other
int isConnected(Interval * a, Interval * b)
{
	if (a->begin < b->begin)
	{
		if (b->begin <= a->end)
		{
			return 1;
		}
		return 0;
	}
	else if (a->begin > b->begin)
	{
		if (a->begin <= b->end)
		{
			return 1;
		}
		return 0;
	}
	return 1;
}

//funciton get pointer to pointer of intervals array, and calculate max, min degree, and number of edges (returns it)
int sumEdges(Interval **arr, int size)
{
	int i, j, total = 0;
	degMinG = size - 1;
	for (i = 0; i < size - 1; i++)
	{
		for (j = i + 1; j < size; j++)
		{
			if (isConnected(arr[i], arr[j]))
			{
				(arr[i]->deg)++;
				(arr[j]->deg)++;
			}
		}
		degMaxG = (arr[i]->deg > degMaxG) ? arr[i]->deg : degMaxG;
		degMinG = (arr[i]->deg < degMinG) ? arr[i]->deg : degMinG;
		total += arr[i]->deg;
	}
	degMaxG = (arr[i]->deg > degMaxG) ? arr[i]->deg : degMaxG;
	degMinG = (arr[i]->deg < degMinG) ? arr[i]->deg : degMinG;
	total += arr[i]->deg;
	return total / 2;
}

//return 1 if the neighbors of vertex has the same color as the color we get in the function
int findColor(Interval **neigh, int size, int color)
{
	int i;
	for (i = 0; i < size; i++)
	{
		if (neigh[i]->color == color)
			return 1;
	}
	return 0;
}

//function return a pointer to array of neighbors vertex
Interval ** buildNeighborArr(Interval **arr, int index, int k)
{
	int i, j = arr[index]->deg;
	Interval **neighbors = (Interval **)malloc(sizeof(Interval *)*(j));

	if (!(arr[index]->deg))
		return NULL;

	for (i = k - 1; i >= 0 && j >= 0; i--)
	{
		if (isConnected(arr[index], arr[i]))
		{
			neighbors[j--] = arr[i];
		}
	}
	return neighbors;
}

//function gives colors to each vertex in the inteval family
void setColors(Interval **arr, int size)
{
	int i, colortemp;
	Interval ** neighbors;
	for (i = 0; i < size; i++)
	{
		colortemp = 1;
		neighbors = buildNeighborArr(arr, i, size);
		if (!neighbors)
			arr[i]->color = 1;
		else
		{
			while (colortemp <= chromatic)
			{
				if ((!findColor(neighbors, arr[i]->deg, colortemp)))
				{
					arr[i]->color = colortemp;
					break;
				}
				colortemp++;
			}
			if (colortemp > chromatic)
				arr[i]->color = ++chromatic;
		}
	}
}

//printing optional coloring for interval family
void printColorArray(Interval **arr, int size)
{
	int i, j, k = 0, *countTimes = (int*)calloc(chromatic, sizeof(int)), colorTemp = 1;
	printf("Optional Coloring: ");
	for (i = 0; i < size; i++)
	{
		countTimes[arr[i]->color - 1]++;
	}
	for (i = 0; i < chromatic - 1; i++)
	{
		printf("{");
		for (j = 0; j < countTimes[i] - 1; j++)
		{
			while (arr[k]->color != i + 1) k++;
			printf("[%d,%d],", arr[k]->begin, arr[k]->end, i + 1);
			k++;
		}
		while (arr[k]->color != i + 1) k++;
		printf("[%d,%d]} = %d, ", arr[k]->begin, arr[k]->end, i + 1);
		k = 0;
	}
	printf("{");
	for (j = 0; j < countTimes[i] - 1; j++)
	{
		while (arr[k]->color != i + 1) k++;
		printf("[%d,%d],", arr[k]->begin, arr[k]->end, i + 1);
		k++;
	}
	while (arr[k]->color != i + 1) k++;
	printf("[%d,%d]} = %d", arr[k]->begin, arr[k]->end, i + 1);
	free(countTimes);
}
