#include <ros/ros.h>
#include<tf/tf.h>
#include<tf2_ros/transform_listener.h>
#include<geometry_msgs/TransformStamped.h>
#include<tf2/utils.h>

void print_rotEuAx(double x, double y, double z, double w){
    tf2::Quaternion quaternion(x,y,z,w);
    
    tf2::Matrix3x3 MatrixRot(quaternion);

    double Matrix [3][3];
    for (int i = 0; i < 3; i++)
    {
        Matrix[0][i]=MatrixRot.getRow(0)[i];
        Matrix[1][i]=MatrixRot.getRow(1)[i];
        Matrix[2][i]=MatrixRot.getRow(2)[i];
    }
    
    ROS_INFO("Matrice di Rotazione:");
    for (int i = 0; i < 3; i++)
    {
        ROS_INFO_STREAM("\t["<<Matrix[i][0]<<", "<<Matrix[i][1]<<", "<<Matrix[i][2]<<"]");
    }
    

    //ROLL-PITCH-YAW
    double roll,pitch,yaw;
    MatrixRot.getRPY(roll,pitch,yaw);
    ROS_INFO_STREAM("\nAngolo di Eulero:\nroll:\t"<<roll<<"\npitch:\t"<<pitch<<"\nyaw:\t"<< yaw);

    //ASSE ANGOLO
    tf2::Vector3 axis = quaternion.getAxis();
    double tetha = quaternion.getAngle();

    ROS_INFO_STREAM("\nAsse-Angolo:\nr:\t[" << axis[0] << " " << axis[1] << " " << axis[2] << "], tetha: " << tetha<<"\n");

}

int main(int argc, char** argv) {
    ros::init(argc, argv, "tf2_listener");
    ros::NodeHandle nodeHandle;
    tf2_ros::Buffer tfBuffer;
    tf2_ros::TransformListener tfListener(tfBuffer);
    ros::Rate rate(10.0);

    while (ros::ok) {
        std::vector<geometry_msgs::TransformStamped> transform(7);
        try {
                transform[0] = tfBuffer.lookupTransform("base_link", "flange", ros::Time(0));
                transform[1] = tfBuffer.lookupTransform("link1", "flange", ros::Time(0));
                transform[2] = tfBuffer.lookupTransform("link2", "flange", ros::Time(0));
                transform[3] = tfBuffer.lookupTransform("link3", "flange", ros::Time(0));
                transform[4] = tfBuffer.lookupTransform("link4", "flange", ros::Time(0));
                transform[5] = tfBuffer.lookupTransform("link5", "flange", ros::Time(0));
                transform[6] = tfBuffer.lookupTransform("link6", "flange", ros::Time(0));
            }
        catch (tf2::TransformException &exception) {
                ROS_WARN("%s", exception.what());
                ros::Duration(1.0).sleep();
                continue;
        }
               for (int i = 0; i < transform.size(); i++)
               {
                double x=transform[i].transform.rotation.x;
                double y=transform[i].transform.rotation.y;
                double z=transform[i].transform.rotation.z;
                double w=transform[i].transform.rotation.w;
                geometry_msgs::Vector3 t;
                t=transform[i].transform.translation;
                ROS_INFO_STREAM("\n\nChild frame id:\t"<<transform[i].child_frame_id<<"\nFrame id:\t"<<transform[i].header.frame_id<<"\n"<<
                "\nQuaternion:\t["<<x<<", "<<y<<", "<<z<<", "<<w<<"]\n"<<
                "\nTranslation:\t["<<t.x<<", "<<t.y<<", "<<t.z<<"]\n");
                print_rotEuAx(x,y,z,w);
               }
        
        rate.sleep();
    }
    return 0;
};