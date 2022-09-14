# **Description about the algorithm**
We will be using DFS (for mapping the entire maze ) and Djikstra’s algorithm ( for calculating the shortest path in the maze ) .
***
## **DFS**
We explore the nodes recursively . That is , we start at a node, look at all of its neighbors. We don't explore the current node completely but rather we pick a neighbor (left-most one ) and go there. We follow the same steps unless we reach a dead end OR EXIT or come back to the same node .
We store the outcome respectively and then backtrack to the most recent checkpoint ( incomplete node )  and complete its exploration . For :- 

1) reaching dead end :  we delete the path from the last checkpoint to that node from memory . In other words , we eraze that dead end node as a vertex in graph 
2) Reaching the same node : We backtrack to most recent checkpoint ( as stored in stack )
3) Reaching the end :  We backtrack to most recent checkpoint ( as stored in stack )
