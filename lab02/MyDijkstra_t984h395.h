#ifndef _MY_DIJKSTRA_H_
#define _MY_DIJKSTRA_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <utility>
#include <algorithm>

typedef unsigned int NodeType;
typedef unsigned int WeightType;
typedef std::vector<std::vector<std::pair<NodeType, WeightType>>> GraphType; // graph as adjacent list

/*------------------------------------------------------------------------------
 ShortestPath_Dijkstra
  Find and print the shortest path from source to end using the Dijkstra's algorithm

 Vairables:
   - graph: the input graph
   - source: the source node
   - end: the target node
   - path_len: the the summation of weights of all edges in the shortest path
   - path: the shortest path represented as a list of nodes

------------------------------------------------------------------------------*/
void ShortestPath_Dijkstra(
    const GraphType &graph,
    const NodeType &source,
    const NodeType &end,
    WeightType &path_len,
    std::vector<NodeType> &path)
{
    /*------ CODE BEGINS ------*/
    std::vector<WeightType> distances(graph.size(), UINT_MAX); // Distance from source to each node
    std::vector<NodeType> previous(graph.size(), UINT_MAX);    // Previous node in the shortest path
    std::vector<bool> visited(graph.size(), false);            // Checks if a node has been visited

    //  Initialize to zero
    distances[source] = 0;
    // Initalize priority queue called pq
    std::priority_queue<std::pair<WeightType, NodeType>,
                        std::vector<std::pair<WeightType, NodeType>>,
                        std::greater<std::pair<WeightType, NodeType>>>
        pq;

    // Push the source node and its distance (0) into the priority queue
    pq.push(std::make_pair(0, source));

    // Dijkstra's algorithm main loop
    while (!pq.empty())
    {
        NodeType u = pq.top().second; // Pop node with the smallest distance from the priority queue
        pq.pop();

        //  Skip if node has been visited before
        if (visited[u])
            continue;
        visited[u] = true; // Mark the current node as visited

        //  Neighbors of the current node
        for (const auto &neighbor : graph[u])
        {
            NodeType v = neighbor.first;         // Neighbor node
            WeightType weight = neighbor.second; // Weight of the edge to the neighbor

            // Update distance if a shorter path is found
            if (distances[u] != UINT_MAX && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                // Add the neighbor to the priority queue with the updated distance
                pq.push(std::make_pair(distances[v], v));
            }
        }
    }

    // Reconstruct the path
    path.clear();
    path_len = distances[end];
    NodeType current = end;
    // Reconstruct the path by backtracking from the end to the source
    while (current != UINT_MAX)
    {
        path.push_back(current);
        current = previous[current];
    }
    std::reverse(path.begin(), path.end()); // Reverse the path to start from the source
                                            /*------ CODE ENDS ------*/
}

#endif