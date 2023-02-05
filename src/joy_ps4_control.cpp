#include <ros/ros.h>
#include <geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

class PS4ControlPublisher{
public:
  PS4ControlPublisher() : nh_() {
    last_joy_.axes = {};
    cmd_pub_ = nh_.advertise<geometry_msgs::Twist>("cmd_vel", 10);
    joy_sub_ = nh_.subscribe("joy", 10, &PS4ControlPublisher::joyCallback, this);
    timer_ = nh_.createTimer(ros::Duration(0.1), &PS4ControlPublisher::timerCallback, this);
  }

  void joyCallback(const sensor_msgs::Joy &joy_msg){
    // ROS_INFO("axes[0]:%f",joy_msg.axes[0]);   // 左スティック左右0の状態を表示 (-1 ～ 1)
    // ROS_INFO("axes[1]:%f",joy_msg.axes[1]);   // 左ティック上下の状態を表示 (-1 ～ 1)
    last_joy_= joy_msg;
  }
  void timerCallback(const ros::TimerEvent& e) {
    geometry_msgs::Twist cmd_vel;
    if(0 < last_joy_.axes.size()){
      cmd_vel.linear.y= last_joy_.axes[0];
    }
    if(1 < last_joy_.axes.size()){
      cmd_vel.linear.x = last_joy_.axes[1];
    }
    cmd_vel.linear.z = 0;
    cmd_pub_.publish(cmd_vel);
  }


  ros::NodeHandle nh_;
  ros::Publisher cmd_pub_;
  ros::Subscriber joy_sub_;
  ros::Timer timer_;
  sensor_msgs::Joy last_joy_;
};


int main(int argc, char **argv)
{

  ros::init(argc, argv, "joy_ps4_control");
  PS4ControlPublisher ps4_control_publisher;
  
  ros::spin();

  return 0;
}