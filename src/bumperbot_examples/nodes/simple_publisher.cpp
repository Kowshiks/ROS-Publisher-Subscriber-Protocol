#include <ros/ros.h>
#include <std_msgs/String.h>
#include <sstream>


int main(int argc, char **argv) 
{

    ros::init(argc, argv, "simple_publisher_cpp"); // Initialize ROS Node
    ros::NodeHandle n; // Create an object of type NodeHandle which allows to publish the new publisher to the ROS Master
    ros::Publisher pub = n.advertise<std_msgs::String>("chatter", 10);
    ros::Rate rate(10); // Used to repeatedly publish the message in the chatter topic with a fixed frequency of 10 Hertz.

    int counter = 0;

    while (ros::ok()) {

        std_msgs::String msg;
        std::stringstream ss;

        ss << "Hello world from C++" << counter;

        msg.data = ss.str();

        pub.publish(msg);

        ros::spinOnce();

        rate.sleep();

        counter++;

    }



    return 0;


}