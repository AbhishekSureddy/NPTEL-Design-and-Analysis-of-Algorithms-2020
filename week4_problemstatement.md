Padayatra
(IOI Training Camp, 2004)

The exit polls indicate that the sitting MLA is likely to lose the upcoming election. The party high command instructs him to undertake a padayatra through his constituency to boost his popularity. To maximize coverage of the constituency, the party decides that he should choose a circular route that returns to the starting point without using any road twice. The route need not visit all the towns and villages in the constituency.

Being averse to physical exercise, the MLA would like to minimize the distance that he has to walk. He has a helicopter at his disposal, so he can begin the padayatra at any town or village.

The task is to help him find the shortest circular route. You are guaranteed that there is always at least one circular route.

Solution Hint
Given an edge (i,j) with weight W(i,j), the shortest cycle from i to i via j can be found by temporarily deleting the edge (i,j), finding the shortest path from j to i, and then adding W(i,j) to the length of this path. Do this systematically to find the shortest cycle in the graph.

Input format
The first line of input is an integer N, 1 ≤ N ≤ 1000, the number of roads in the constituency. The constituency has no more than 300 towns and villages connected by roads.

The next N lines specify the roads. Each line consists of three space separated integers S, T and D where S is the starting point of the road, T is the ending point and D is the length of the road. Each road is a two-way road and is listed exactly once, in one of the two directions.

Output format
A single line with the integer distance around the shortest possible circular route.

Test data
There are at most 300 towns and villages and at most 1000 roads.

Example
Sample Input
4
3 1 5
1 2 4
3 2 3
1 5 44
Sample output 1
12
