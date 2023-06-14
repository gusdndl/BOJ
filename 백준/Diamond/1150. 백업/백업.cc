#include <cstdio>
#include <algorithm>
#include <queue>
#include <functional>
#include <utility>
#include <vector>
using namespace std;

const int MAX_NODES=100002;
const int MAX_INFINITY=1e9;
typedef pair<int, int> Pair; // <distance, <start, end>>

int numNodes, numIterations, node1, node2;
int distances[MAX_NODES];
int previousNode[MAX_NODES], nextNode[MAX_NODES];
bool nodeVisited[MAX_NODES];
priority_queue<Pair, vector<Pair>, greater<Pair>> priorityQueue;

int main() {
    scanf("%d%d", &numNodes, &numIterations);

    distances[1] = distances[numNodes+1] = MAX_INFINITY;
    nextNode[1] = 2;
    previousNode[numNodes+1] = numNodes;
    priorityQueue.push({MAX_INFINITY, 1});
    priorityQueue.push({MAX_INFINITY, numNodes+1});

    scanf("%d", &node1);
    for (int i = 2; i <= numNodes; i++) {
        scanf("%d", &node2);
        distances[i] = node2 - node1;
        priorityQueue.push({distances[i], i});
        previousNode[i] = i - 1;
        nextNode[i] = i + 1;
        node1 = node2;
    }
    int result = 0;

    while (numIterations--) {
        while (nodeVisited[priorityQueue.top().second]) priorityQueue.pop();
        int distance = priorityQueue.top().first;
        int index = priorityQueue.top().second;
        priorityQueue.pop();
        result += distance;
        distances[index] = distances[previousNode[index]] + distances[nextNode[index]] - distances[index];
        priorityQueue.push({distances[index], index});
        nodeVisited[previousNode[index]] = nodeVisited[nextNode[index]] = true;
        previousNode[index] = previousNode[previousNode[index]];
        nextNode[index] = nextNode[nextNode[index]];
        nextNode[previousNode[index]] = index;
        previousNode[nextNode[index]] = index;
    }
    printf("%d\n", result);
    return 0;
}
