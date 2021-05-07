#include <ros/ros.h>
#include <std_msgs/String.h>
#include <trajectory_msgs/JointTrajectory.h>

int main(int argc, char **argv){
    ros::init(argc,argv, "publisher");
    ros::NodeHandle nh;
    ros::Publisher chatterPublisher=nh.advertise<trajectory_msgs::JointTrajectoryPoint>("chatter",1);
    ros::Rate loopRate(10);

    trajectory_msgs::JointTrajectoryPoint msg;
    
    msg.positions.resize(6);

            
    unsigned int count = 0;
    while (ros::ok())
     {
      
      
      msg.positions[1]=rand();
      msg.positions[2]=rand();

      msg.positions[3]=rand();
      msg.positions[4]=rand();


      msg.positions[5]=rand();
      msg.positions[6]=rand();

      ROS_INFO_STREAM(msg);
      chatterPublisher.publish(msg);
      
      ros::spinOnce();
      loopRate.sleep();
      count++;
    }

  ros::shutdown();
  return 0;
}