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
    std::vector<WeightType> distances(graph.size(), UINT_MAX);
    std::vector<NodeType> previous(graph.size(), UINT_MAX);
    std::vector<bool> visited(graph.size(), false);

    distances[source] = 0;
    std::priority_queue<std::pair<WeightType, NodeType>,
                        std::vector<std::pair<WeightType, NodeType>>,
                        std::greater<std::pair<WeightType, NodeType>>>
        pq;

    pq.push(std::make_pair(0, source));

    while (!pq.empty())
    {
        NodeType u = pq.top().second;
        pq.pop();

        if (visited[u])
            continue;
        visited[u] = true;

        for (const auto &neighbor : graph[u])
        {
            NodeType v = neighbor.first;
            WeightType weight = neighbor.second;

            if (distances[u] != UINT_MAX && distances[u] + weight < distances[v])
            {
                distances[v] = distances[u] + weight;
                previous[v] = u;
                pq.push(std::make_pair(distances[v], v));
            }
        }
    }

    path.clear();
    path_len = distances[end];
    NodeType current = end;
    while (current != UINT_MAX)
    {
        path.push_back(current);
        current = previous[current];
    }
    std::reverse(path.begin(), path.end());
    /*------ CODE ENDS ------*/
}

#endif