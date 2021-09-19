#include <ros/ros.h>
#include <forward_kinematics_msgs/fk_service.h>
#include <moveit/robot_model_loader/robot_model_loader.h>
#include <moveit/robot_state/robot_state.h>
#include <moveit/robot_state/conversions.h>
#include <moveit_msgs/RobotState.h>
#include <tf2_geometry_msgs/tf2_geometry_msgs.h>

int main(int argc,char **argv){

    ros::init(argc, argv, "fk_service_client");
    ros::NodeHandle nh;

    /*viene istanziato un oggetto di tipo ServiceClient,
    *che riceve in ingresso il nome del servizio.
    */
    ros::ServiceClient client = nh.serviceClient<forward_kinematics_msgs::fk_service>("forward_kinematics");

    forward_kinematics_msgs::fk_service fk_service;
    /*oggetto del tipo RobotModelLoader che cerca il robot description sul parameter server,
    *quando si lancia il demo.launch il robot_description conterrà l'urdf serializzato*/

    robot_model_loader :: RobotModelLoader robot_model_loader("robot_description");
    robot_model::RobotModelConstPtr robot_model = robot_model_loader.getModel();
    moveit::core::RobotState robot_state(robot_model); 


    //viene settata la richiesta

    moveit::core::robotStateToRobotStateMsg(robot_state, fk_service.request.robot_state);
    ROS_INFO_STREAM(fk_service.request.robot_state);
    client.call(fk_service);
    
    return 0;
}