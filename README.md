# Steps to create Parameter Server, Nodes and Topic through Publisher-Subscriber protocol to make the Robot move in Gazebo


## Basic Publisher Subscriber

Publisher Subscriber communication protocol to publish new message in ROS Topic.
Created a topic called chatter. Messages are published in the chatter topic.
Subscriber node is created to listen to all the messages that the publisher publishes and create event for each message.
ROS Master is started using the roscore command

## Locomotion - URDF

We will be focussing on Differential locomotion where there are 2 wheels acting independently with different motors.
ROS uses URDF - Unified Robot Description Format to structure the Robot through XML tags
The meshes here are used using the STL files

To create the XML model of the robot using the URDF convention:

1) Create a ROS package:

catkin_create_pkg is used to create a package.

2) The XML tags:

<robot> is used to contain all the components of the robot

In the origin “rpy” is the orientation and “xyz” is the position.

base_footprint is in the middle of the robot in the lower point of contact to the ground and base_link is oriented with the base_footprint and intersects the axis of the wheel of the robot.

<joint> is used to connect differnt <link> and type is fixed in the base_footprint and base_link as it cant rotate around the axis.

A joint contains a parent and a child link.

In the wheel joint the type is continuous because the wheel can freely rotate along the axis of the base joint.

## RViz

RViz - ROS Visualization and these are graphical interface that allows us to visualize the content of the ROS messages that are published in different topics.

The way it works - > Uses the Publisher Subscriber communication protocol.

RViz creates a subscriber node that receives messages from one or more ROS topics and displays it in GUI.

Whenever a new message is published on a topic, the RViz subscriber receives it

ROS Parameter Server to store variables. command “rosparam list” is used to list all the params. “rosparam get <name>” is used to get the value. To store a new parameter we use “rosporam set <name> <value>”

![Answer box frame length](/img/rviz.png)



## To visualise the URDF robot model in RViz

First we need to load the URDF model in the parameter server so that it can be retrieved by RViz for visualization.

First start the ROS master using roscore

The loading of the entire file in the parameter server  is done using “rosparam load <urdf_file_path> <param_name>”

To read the content we can use “rosparam get <param_name>”

Before visualizing the robot in RViz we need to execute another node that uses this Robot description parameter to publish the information in the ROS topic. The information includes the distance between the Joint or their angle. This the topic that RViz will be subscribed to show the visualization.

The node that we need to run is the robot_state_publisher

start the rviz node using “rosrun rviz(package) rviz(node)”

TF shows all the links → RobotModel visualizes the URDF model of the robot

To allow the movement of all the non fixed joint of the robot (wheels) we need to start another node of the package joint_state_publisher_gui → after this the wheels will be correctly displayed.

## ROS launch files to make things simpler

Launch files are basically xml files that contains a list of operations

roslaunch command is used to launch all the applications listed in the xml file

<param> tag can load several parameters into the parameter server.

<node> tag can execute several nodes

<include> executes the launch files

## Gazebo

Physics Engine to simulate movement and forces applied on the robot. Rviz interacts with the data from Gazebo which simulates sensor datas and other information of the robot.

<collision> tag is used in the urdf file for the Gazebo interecation. This basically indicates the volume of the parts.

<inertial> is used to add the inertia of the body. This basically contains the inertial matrix

![Answer box frame length](/img/Gazebo_first.png)



## Control

For controller, the library called ROS Controller is used.

To activate the moving joint of the robot.

Publish the message for the left and right wheels to rotate.
