# MTRX3760 Major Project Package
This folder contains the main ROS package for the major project  

For unexplored navigation
1) Breadth first search to find unexplored points 
within the (cost map with boundaries around obstacles so that the points are actually reachable) map (boarding the field of unexplored points). (if no points exist, the map exploration is complete)

2) Using the list of unexpored points run a A* cost algorithm to find the closest point by path. 

3) Navigate to unexpored point using the 2D nav goal.

4) go back to step 1.

These steps should be states within the FSM, whilst in these states the turtlebot should be constantly surveying for tags. 