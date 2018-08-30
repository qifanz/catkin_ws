#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>


class joy_listener
{
public:
  joy_listener();

private:
  void joyCallback(const sensor_msgs::Joy::ConstPtr& joy);

  ros::NodeHandle nh_;

  int linear_, angular_;
  double l_scale_, a_scale_;
  ros::Publisher vel_pub_;
  ros::Subscriber joy_sub_;

};


joy_listener::joy_listener():
  linear_(1),
  angular_(0),
  a_scale_(5),
  l_scale_(1)
{

  nh_.param("axis_linear", linear_, linear_);
  nh_.param("axis_angular", angular_, angular_);
  nh_.param("scale_angular", a_scale_, a_scale_);
  nh_.param("scale_linear", l_scale_, l_scale_);


  vel_pub_ = nh_.advertise<geometry_msgs::Twist>("/vrep/twistCommand", 1);
  joy_sub_ = nh_.subscribe<sensor_msgs::Joy>("joy", 10, &joy_listener::joyCallback, this);

}

void joy_listener::joyCallback(const sensor_msgs::Joy::ConstPtr& joy)
{
 if (joy->buttons[3]) {
     this->l_scale_++;
 }
  geometry_msgs::Twist twist;
  twist.angular.z = a_scale_*joy->axes[angular_];
  twist.linear.x = l_scale_*joy->axes[linear_];
  vel_pub_.publish(twist);
}


int main(int argc, char** argv)
{
  ros::init(argc, argv, "joy_listener");
  joy_listener joy_listener;

  ros::spin();
}