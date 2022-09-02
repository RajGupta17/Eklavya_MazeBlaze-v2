# Different types of Maze Solving Algos:

### 1) Backtracing:
Tries to take different turns until the right turn is found. If a wrong turn is taken, it would simply remove the turn from its' itenary and will not follow that turn again.

### 2) Tremaux's Algorithm:
When followed a path, every junction is marked which are unvisited and if there are two marks, do not enter that path again. If we come at a junction where there is only 1 mark, turn around and return again marking the junction. But this method doesn't guarantees the shortest path.

### 3) A* (A Star) Algorithm:
It maps the maze and assign the values of cells from where shortest path is found by adding both the cell numbers.

### 4) Flood-Fill Algorithm:
In this algorithm also,the cell numbers are added in order to get the shortest path.

## Flood-fill Algorith in Depth

