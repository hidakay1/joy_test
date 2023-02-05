#include <ros/ros.h>
#include <sensor_msgs/Joy.h>

void joy_callback(const sensor_msgs::Joy &joy_msg)
{
  //処理内容を記述
for (int i = 0; i < 12; i++) {
	//	cout <<  i << "\n"; // 0 1 2が出力される
    ROS_INFO("axes[%i]:%f", i,joy_msg.axes[i]);   // スティック0の状態を表示 (-1 ～ 1)
    ROS_INFO("Button[%i]:%d",i, joy_msg.buttons[i]);  // ボタン0の状態を表示 (0 or 1)
	}
  // asxies
}

int main(int argc, char **argv)
{
  ros::init(argc, argv, "joy_sub_node");
  ros::NodeHandle nh;
  ros::Subscriber sub = nh.subscribe("joy", 10, joy_callback);
  ros::Rate loop_rate(10);

  while (ros::ok())
  {
    ros::spinOnce();
    loop_rate.sleep();
  }
  return 0;
}