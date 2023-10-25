# MTRX3760 Major Project Package
This folder contains the main ROS package for the major project  

For unexplored navigation
1) Breadth first search to find unexplored points 
within the (cost map with boundaries around obstacles so that the points are actually reachable) map (boarding the field of unexplored points). (if no points exist, the map exploration is complete)

2) Using the list of unexpored points run a A* cost algorithm to find the closest point by path.  (or use euclid distance, bcus easier)

3) Navigate to unexpored point using the 2D nav goal.

4) go back to step 1.

These steps should be states within the FSM, whilst in these states the turtlebot should be constantly surveying for tags. 



////


1) look at move_base_simple/goal and see what it sends
2) send that message to the thing

3) Start in init state, use odom x,y from this to set as origin point!

4) use turtlebot3_navigation param files and use turtlebot3_slam config files, make launch file!

Run sequence
1. roscore (ROS_IP)
2. turtlebot bringup
3. turtlebot3_nav (export ros_master), (export burger)
4. slam (export ros_master) (export burger)
5. rosrun major_project


