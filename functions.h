//struct that save information for each vertex in the interval family
typedef struct interval
{
	int begin;
	int end;
	int color;
	int deg;
}Interval;

//global variables
static int chromatic = 1;
static int degMaxG = 0;
static int degMinG;

//function declaration
void GreedyColoring();
Interval ** inputIntervals(int);
void printIntervalFamily(Interval **, int);
void swap(Interval *, Interval *);
int partition(Interval **, int, int);
void quick_sort(Interval **a, int, int);
int isConnected(Interval *, Interval *);
int sumEdges(Interval **, int);
int findColor(Interval **, int, int);
Interval ** buildNeighborArr(Interval **, int, int);
void setColors(Interval **, int);
void printColorArray(Interval **, int);