#include <moveit/move_group_interface/move_group_interface.h>
#include <moveit/planning_scene_interface/planning_scene_interface.h>
#include <moveit_msgs/DisplayRobotState.h>
#include <moveit_msgs/DisplayTrajectory.h>
#include <moveit_msgs/AttachedCollisionObject.h>
#include <moveit_msgs/CollisionObject.h>
#include <moveit_visual_tools/moveit_visual_tools.h>


int main(int argc, char **argv)
{
    ros::init(argc, argv, "move_group_interface_tutorial");
    ros::NodeHandle node_handle;
    ros::AsyncSpinner spinner(0);
    spinner.start(); 

    static const std::string PLANNING_GROUP = "robot_arm";
    moveit::planning_interface::MoveGroupInterface

    move_group(PLANNING_GROUP); // loading move_group
    const robot_state::JointModelGroup *joint_model_group = move_group.getCurrentState()->getJointModelGroup(PLANNING_GROUP); //For joint control

    geometry_msgs::PoseStamped current_pose;
    geometry_msgs::PoseStamped target_pose; // Pose in ROS is implemented using geometry_msgs::PoseStamped, google what is the type of this msg
    current_pose = move_group.getCurrentPose(); /* Retrieving the information about the current position and orientation of the end effector*/
    target_pose = current_pose;
    target_pose.pose.position.x = target_pose.pose.position.x - 0.14; /* Basically our target pose is the same as current, except that we want to move it a little bit along x-axis*/
    
    
    ros::Rate loop_rate(50); //Frequency


    while (ros::ok()){
        move_group.setApproximateJointValueTarget(target_pose); // To calculate the trajectory
        move_group.move(); // Move the robot
        current_pose = move_group.getCurrentPose();
        if (abs(current_pose.pose.position.x - target_pose.pose.position.x) < 0.1)
        {
            break; // Basically, check if we reached the desired position
        }
        loop_rate.sleep();
    }

    ROS_INFO("Done");
    ros::shutdown();
    return 0;
}