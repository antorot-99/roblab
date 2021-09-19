#include <ros/ros.h>
#include<moveit/robot_model_loader/robot_model_loader.h>
#include<moveit/robot_state/robot_state.h>
#include <moveit/robot_state/conversions.h>
#include <moveit/transforms/transforms.h>
#include <eigen_conversions/eigen_msg.h>
#include <Eigen/Geometry>
#include <Eigen/Core>
#include <forward_kinematics_msgs/fk_service.h>


bool forwardkinematics(forward_kinematics_msgs::fk_service::Request &req, forward_kinematics_msgs::fk_service::Response &res){
      /**
    * RobotModelLoader cerca la descrizione del robot sui ROS parameters, quando lanciamo demo.launch di un pacchetto x_moveit_config 
    * nel robot description sarà contenuto l'urdf del robot serializzato, che ne fa della sua descrizione
    */
    
    robot_model_loader ::RobotModelLoader robot_model_loader;
    
    /*viene creato un puntatore al modello cinematico che viene fornito successivamente al robot state che rappresenta lo stato del robot e
    tiene conto della posizione, velocità e accelerazione*/

    robot_model::RobotModelConstPtr robotModelptr = robot_model_loader.getModel();
    moveit::core::RobotState robot_state(robotModelptr);

    /*il robot_state viene aggiornato in base alla richiesta del servizio*/

    moveit::core::robotStateMsgToRobotState(req.robot_state, robot_state);
    
    /*si crea un oggetto JointModelGroup che rappresenta il modello del robot per il particolare gruppo*/

    const robot_state::JointModelGroup* joint_model_group=robot_state.getRobotModel()->getJointModelGroup("fanuc");
    
    /*si leggono i link inerenti al gruppo*/
    std::vector<std::string> linknames=joint_model_group->getLinkModelNames();
    
    /*si calcola la cinematica diretta rispetto all'end effector*/

    const Eigen::Isometry3d forwardkinematics = robot_state.getGlobalLinkTransform(linknames.back());
    /*setta la risposta*/
    
    tf::poseEigenToMsg(forwardkinematics, res.end_effector);

    ROS_INFO_STREAM("Posa inviata\n"<<res.end_effector);

}


int main(int argc, char **argv)
{
    ros::init(argc, argv, "fk_m20ia_server");
    ros::NodeHandle nh;

    /*viene istanziato un oggetto di tipo ServiceServer che riceve in ingresso il nome del servizio e la callback*/

    ROS_INFO("Server started");

    ros::ServiceServer service = nh.advertiseService("forward_kinematics", forwardkinematics);

    ros::spin();

    return 0;
}