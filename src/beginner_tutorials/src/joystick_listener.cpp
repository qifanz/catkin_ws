#include "ros/ros.h"
#include "std_msgs/Float64.h"
#include "sensor_msgs/Joy.h"
ros::Publisher lefwheelpub;
ros::Publisher rightwheelpub;

void chatterCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
    ROS_INFO("B0 [%i]", msg->buttons[0]);
    ROS_INFO("B1 [%i]", msg->buttons[1]);
    ROS_INFO("B2 [%i]", msg->buttons[2]);
    ROS_INFO("B3 [%i]", msg->buttons[3]);
    if (msg->buttons[3]) {
        std_msgs::Float64 toPub;
        toPub.data=1.0;
        lefwheelpub.publish(toPub);
        rightwheelpub.publish(toPub);
    }

}

int main(int argc, char **argv)
{
 
  ros::init(argc, argv, "joystick_listener");    

 
  ros::NodeHandle n;

  ros::Subscriber sub = n.subscribe("joy", 1000, chatterCallback);
    lefwheelpub = n.advertise<std_msgs::Float64>("vrep/leftWheelCommand", 1000);
    rightwheelpub = n.advertise<std_msgs::Float64>("vrep/rightWheelCommand", 1000);




  ros::spin();


  return 0;
}
