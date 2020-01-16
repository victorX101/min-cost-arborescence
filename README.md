# min-cost-arborescence
C++ code for computing minimum cost spanning tree in a directed graph by implementing edmond's Algorithm. 

we use the property of directed spanning trees that each node has except source has 1 indegree thus we use a global array parent[n] to 
represent the arborescence at each point







------ Input Format -----------------------------------------------------------------

First line: Number of Test Cases T and then follows their description
For each test case, first row indicate N s (single space separated) where N is number of vertices in directed graph where vertices are labelled 1 to N and s is the index of source vertex
Second row mentions the number of edges M
And then M rows mentioning  u v w(u,v)


------ Output Format ----------------------------------------------------------------


T rows corresponding to T test cases 
Output row for each test case has 2N+1+1 entries (all single space separated)
where first entry is the  total sum of min cost arborescence 
and then N entries corresponding to vertices V1, V2, V3..., VN providing the distance of i-th vertex from the source vertex s. (Indicate -1 if unreachable)
and then Symbol #
and then N entries (corresponding to vertices V1, V2, V3..., VN) providing the label of the parent node through which one reaches i-th vertex (basically second last node in path from source vertex to that i-th vertex.



----------------NOTE that it shows a message when all the vertices are not reachable from source as arborescence is defined only when all nodes are reachable ---------------------------------------
