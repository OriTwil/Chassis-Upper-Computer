# Underpan-upper-computer
底盘的上位机
### 项目移植说明
1. [配置环境并自定义MAVLINK消息](https://mavlink.io/zh/getting_started/ros.html)
  - 按照MAVROS 源安装说明，安装官方专门为ROS发布的mavlink 库——mavlink-gbp-release，可以不用wstool，直接克隆此仓库中/src/mavlink-gbp-release和/src/mavros

  - Uninstall the MAVlink package for ROS if previously installed.（sudo apt-get remove ros-${rosversion -d}-mavlink）
    or source （devel/setup.bash） of your catkin workspace to override the library directory.

  - In the mavlink-gbp-release, add the new MAVlink message to common.xml or add the new dialect dialect_name.xml in the message definitions. Do not checkout your MAVlink branch because it is not the version synced with ROS.在/src/mavlink-gbp-release/message_definitions/common.xml中定义自定义消息，注意2.0版本的mavlink自定义消息只能写在common.xml中

  - 采用命令 catkin build mavlink生成MAVlink的头文件（不需要专门用.py文件手动生成），生成的头文件在~/catkin_ws/build/mavlink/include/中
  
2. 自定义MAVROS消息
  - 在/src/mavros/mavros_msg/msg（服务模型在srv）中添加自定义消息.msg文件
  - 更改CMakeLists.txt文件：“add_message_files(SpeedControlStatus.msg)”
 
3. 编写消息处理插件
  - 添加插件路径：/src/mavros/mavros/src/plugins
  - 参考代码：/src/mavros/mavros/src/plugins/manual_control.cpp（典型）
  或speed_control.cpp
4. 添加自定义插件到插件列表
  - 路径：~/catkin_ws/src/mavros/mavros/mavros_plugins.xml
  - 作用：用于MAVROS自动加载插件
5. 添加至CMakeLists.txt
  - 路径：~/catkin_ws/src/mavros/mavros/CMakeLists.txt
  - 作用：将插件添加至编译
  - 添加内容：add_library(mavros_plugins src/plugins/crawl_control.cpp)
 6. 编写launch执行文件
  - 路径：~/catkin_ws/src/mavros/mavros/launch
  - 文件内容：.launch和.yaml文件可以仿照px4.launch编写
  - 在px4.launch文件中可以设置USB接口、波特率、系统id、mavlink版本等
  - 在px4_pluginlists.yaml中可以设置插件黑名单（不放入黑名单的插件默认执行）
 7. 运动控制代码
  - 路径：~/catkin_ws/src/mavros/mavros/src/
  - 代码内容：可参考SpeedControlSet_pub.cpp（写的不太好）
 8. 测试
  - 测试环境：大疆A板(含自定义mavlink 2.0消息收发，与上位机mavlink消息id对应)、ROS、Ubuntu
  - roscore
  - 编译 ：catkin build
  - 定世界坐标：rosrun tf2_ros static_transform_publisher 0 0 0 0 0 0 1 camera_odom_frame 
  - 发布T265消息：roslaunch realsense2_camera rs_t265.launch 
  - 卡尔曼滤波：roslaunch robot_pose_ekf robot_pose_ekf.launch
  - 启动mavros：roslaunch mavros xxx.launch 
  - 运动控制：rosrun mavros xxx
  - 可视化：rqt rviz rqt_graph rqt_tf_tree等
  - 数据可视化：rosbag + plotjugger
 9. tips
  - 注意创建工作空间的时候，是catkin build
  - 运动控制代码需要添加编译依赖等，配置CMakeLists.txt
10. 用扩展卡尔曼滤波器对imu、里程计 odom、视觉里程计的数据进行融合
  - 说明：卡尔曼滤波的作用与算法实现可以参考[这篇文章](http://www.bzarg.com/p/how-a-kalman-filter-works-in-pictures) 、b站up主"DR_CAN"、up主"421施工队"。在ROS中，可以通过robot_pose_ekf功能包，方便的使用卡尔曼滤波器，具体说明参考[wiki](http://wiki.ros.org/robot_pose_ekf)
  - 安装：安装robot_pose_ekf功能包，我是用二进制安装"sudo apt install ros-xxx-robot_pose_ekf*", 源码安装应该也可以
  - 编译与运行："roscd robot_pose_ekf" “rosmake” "roslaunch robot_pose_ekf.launch"即可对订阅话题中的数据进行处理，并发布
  - remap进行名称重映射：robot_pose_ekf node订阅了imu、里程计 odom、视觉里程计 vo三个传感器源，node可以自动检测可用源，如果想加入自己的传感器，可以用remap进行名称重映射，例如此项目中使用T265视觉里程计，可以将vo重映射到T265视觉里程计发布的话题：/camera/odom ，也可以将imu_data、odom分别重映射，即可对数据融合，进行定位  具体参考[wiki上的说明](http://wiki.ros.org/robot_pose_ekf/Tutorials/AddingGpsSensor)
  - 编写发布者，订阅卡尔曼滤波后的数据：话题名称、消息类型等参考wiki或csdn上的译文
  - 测试：发布T265消息：roslaunch realsense2_camera rs_t265.launch
  卡尔曼滤波：roslaunch robot_pose_ekf robot_pose_ekf.launch 运动控制：rosrun mavros xxx 可以通过plotjugger测试滤波效果
  - tips：①记得添加功能包依赖 ②添加头文件 <geometry_msgs/PoseWithCovarianceStamped.h> ③robot_pose_ekf只适用于平面上的轮式移动机器人
  
### 项目文件说明
### 效果展示
  - 11.16
   ![11.16 y坐标](https://github.com/szf01/Underpan-upper-computer/raw/master/img_storage/df4808fcfc458988658241c942bb094.jpg)
### 优化思路
  11月16日 需要优化控制算法（尝试PI控制器，或PID）、路径规划（不了解）、轨迹优化（结合摩擦系数估算最大加速度，设置加速减速曲线，减少打滑和速度突变）、机械结构优化（减少抖动、精确尺寸）
  
  
