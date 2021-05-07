#include <ros/ros.h>
#include <std_msgs/String.h>
#include <trajectory_msgs/JointTrajectory.h>

void chatterCallback(const trajectory_msgs::JointTrajectoryPoint& msg){
    ROS_INFO_STREAM("I heard"<<msg);
}

int main(int argc, char **argv){
    ros::init(argc, argv, "subscriber");
    ros::NodeHandle nodeHandle;

    ros::Subscriber subscriber=nodeHandle.subscribe("chatter",10, chatterCallback);
    ros::spin();
    return 0;
}