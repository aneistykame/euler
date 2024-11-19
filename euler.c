#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 100 // Maximálny počet vrcholov v grafe
#define MAX_EDGES 500 // Maximálny počet hrán v grafe

// Štruktúra pre zoznam susedov (adjacency list)
typedef struct Edge
{
   int to;
   bool used;
   struct Edge *next;
} Edge;

Edge *graph[MAX_NODES]; // Zoznam susedov pre každý vrchol
int degree[MAX_NODES];  // Stupeň vrcholov
int stack[MAX_EDGES];   // Pomocný stack pre Hierholzerov algoritmus
int top = -1;

void addEdge(int from, int to)
{
   Edge *edge = (Edge *)malloc(sizeof(Edge));
   edge->to = to;
   edge->used = false;
   edge->next = graph[from];
   graph[from] = edge;
}

bool isEulerian(int *startNode)
{
   int oddDegreeCount = 0;
   *startNode = -1;
   for (int i = 0; i < MAX_NODES; i++)
   {
      if (degree[i] % 2 != 0)
      {
         oddDegreeCount++;
         *startNode = i; // Začni v uzle so stupňom 1
      }
      if (degree[i] > 0 && *startNode == -1)
      {
         *startNode = i; // Ak žiaden uzol nemá nepárny stupeň, začni v akomkoľvek so stupňom > 0
      }
   }
   return (oddDegreeCount == 0 || oddDegreeCount == 2); // Platí pre Eulerov okruh (0) alebo cestu (2)
}

void findEulerPath(int startNode)
{
   top = 0;
   stack[top] = startNode; // Začiatočný uzol
   int path[MAX_EDGES];
   int pathLen = 0;
   while (top >= 0)
   {
      int node = stack[top];
      Edge *edge = graph[node];
      // Nájdite nepoužitú hranu
      while (edge != NULL && edge->used)
      {
         edge = edge->next;
      }
      if (edge != NULL)
      {
         // Označ hranu ako použitú a presuň sa na susedný vrchol
         edge->used = true;
         stack[++top] = edge->to;
      }
      else
      {
         // Vraciame sa po ceste
         path[pathLen++] = node;
         top--;
      }
   }
   // Výpis výslednej cesty
   printf("Eulerova cesta alebo okruh: ");
   for (int i = pathLen - 1; i >= 0; i--)
   {
      printf("%d%s", path[i], (i == 0 ? "\n" : " -> "));
   }
}

int main()
{
   int numEdges, from, to;
   // Inicializácia grafu
   memset(graph, 0, sizeof(graph));
   memset(degree, 0, sizeof(degree));
   printf("Zadajte pocet hran: ");
   scanf("%d", &numEdges);
   printf("Zadajte hrany (od, do):\n");
   for (int i = 0; i < numEdges; i++)
   {
      scanf("%d %d", &from, &to);
      addEdge(from, to);
      addEdge(to, from); // Neorientovaný graf
      degree[from]++;
      degree[to]++;
   }
   int startNode;
   if (!isEulerian(&startNode))
   {
      printf("Eulerova cesta alebo okruh neexistuje.\n");
   }
   else
   {
      findEulerPath(startNode);
   }
   return 0;
}
