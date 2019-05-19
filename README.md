Flight-Simulator-Problem-Solver is a Server, handles various clients parallel.

The problem given from the client, is finding shortest path in a graph (more precisley a matrix Graph, given a start and a goal, the matrix filled with costs of every "step" which is sent line by line (creating the matrix of costs) by the client.

We implemented few algorithm for finding shorthest path A*, BEST FIRST SEARCH, classic DFS and BFS also. by doing An empirical experiment we learned that A* is the best algorithm to solve our client problems and the program use this algorithm.

When running our server using the main supllied by us (for example using our makefile), it expects a command line argument indicating the port number the server will be opened on (in our makefile's run target we pass 5400).

Now the clients can send matrix and get the the soulution for the specific problem.

The server waits for the stop method, you can do it by sending "stop".
