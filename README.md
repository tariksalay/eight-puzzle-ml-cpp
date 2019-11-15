This was the very machine learning program I dealt with. I was better at C++ development so tried to solve the puzzle with it. Program takes a simple 3x3 as an input and solves it by calculating the cost with Manhattan(taxicab) Distance.


[Manhattan Distance](https://en.wikipedia.org/wiki/Taxicab_geometry)


![A* logic](https://media.geeksforgeeks.org/wp-content/uploads/puzzle-1.jpg)

For the search method, A-star algorithm has used, which is a graph traversal in order to find efficieny. At each iteration of its main loop, A* needs to determine which of its paths to extend. It does so based on the cost of the path and an estimate of the cost required to extend the path all the way to the goal.


![Cost Graph](https://upload.wikimedia.org/wikipedia/commons/9/98/AstarExampleEn.gif)

To visualize how to calculate the cost.

![Initial vs Goal](https://www.cs.princeton.edu/courses/archive/spr18/cos226/assignments/8puzzle/4moves.png)

Initial vs Goal State

[![Watch the video](https://i.vimeocdn.com/video/831405690_1280x720.jpg)](https://vimeo.com/373321351)
*Watch the video*
