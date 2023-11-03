## MTRX3760MP
## Overview

The Rescue and Recovery Robot is an autonomous robot designed to enter unexplored buildings to search for fires and individuals in need of assistance. The robot utilizes a combination of LiDAR (Light Detection and Ranging) for mapping and navigation, SLAM (Simultaneous Localization and Mapping) for exploration, and an onboard camera for identifying fires and persons using April tags. The primary objectives of the robot are as follows:

- **Fire Detection and Suppression**: The robot is equipped with a camera that identifies fires using April tags. When a fire is detected, the robot turns toward it and activates an onboard LED to indicate that it's addressing the fire, which may include deploying fire suppression methods.

- **Person Detection and Assistance**: Using the same camera, the robot identifies individuals with April tags. Upon detecting a person, the robot turns toward them and navigates closer. If the person pushes a button to indicate they are conscious and require assistance, the robot guides them safely back to the building's opening. If the button is not pressed, the person's position is flagged for further attention.

## Functionality

The Rescue and Recovery Robot offers the following capabilities:

- **Exploration and Mapping**: The robot employs LiDAR and SLAM techniques to explore and map unexplored environments, ensuring it can navigate effectively in complex spaces.

- **Fire Detection and Suppression**: The robot uses its onboard camera to detect fires equipped with April tags. Upon detection, it turns toward the fire and activates an LED to indicate that it is addressing the situation.

- **Person Detection and Assistance**: Individuals are identified using April tags. When a person is detected, the robot turns toward them, navigates closer, and initiates assistance. If the person presses a button, the robot guides them to safety. If no button press occurs, their location is flagged.

## Dependencies

To run the Rescue and Recovery Robot project, ensure that the following dependencies are installed:

- ROS (Robot Operating System)
- April tag ros package
- move_base package
  
