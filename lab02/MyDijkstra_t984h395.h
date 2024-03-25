#ifndef _MY_DIJKSTRA_H_
#define _MY_DIJKSTRA_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <queue>
#include <climits>
#include <stack>
#include <utility>
#include <set>
#include <algorithm>
#include <limits>

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
    std::vector<WeightType> dist(graph.size(), std::numeric_limits<WeightType>::max());
    std::vector<NodeType> prev(graph.size(), -1);
    std::set<std::pair<WeightType, NodeType>> queue;

    dist[source] = 0;
    queue.insert({0, source});

    while (!queue.empty())
    {
        NodeType u = queue.begin()->second;
        queue.erase(queue.begin());

        if (u == end)
            break;

        for (const auto &neighbor : graph[u])
        {
            NodeType v = neighbor.first;
            WeightType weight = neighbor.second;

            // Check if a shorter path to v exists through u
            if (dist[u] + weight < dist[v])
            {
                queue.erase({dist[v], v});
                dist[v] = dist[u] + weight;
                prev[v] = u;
                queue.insert({dist[v], v});
            }
        }
    }

    // Reconstruct the shortest path
    path_len = dist[end];
    path.clear();
    if (prev[end] != -1 || end == source)
    { // Check if there is a path to end
        for (NodeType at = end; at != -1; at = prev[at])
        {
            path.push_back(at);
        }
        std::reverse(path.begin(), path.end());
    }
    /*------ CODE ENDS ------*/
}

#endif
