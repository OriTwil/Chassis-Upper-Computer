# Underpan-upper-computer
Upper computer for the chassis.
## Project Migration Instructions
#### 1. [Configure the environment and customize MAVLINK messages](https://mavlink.io/zh/getting_started/ros.html)
  - Follow the installation instructions for MAVROS sources to install the official mavlink library specially released for ROS : `mavlink-gbp-release`. You can clone the `/src/mavlink-gbp-release` and `/src/mavros` directories directly without using wstool.

  - Uninstall the MAVlink package for ROS if previously installed.`sudo apt remove ros-${rosversion -d}-mavlink`
    or `source （devel/setup.bash）` of your catkin workspace to override the library directory.

  - In the mavlink-gbp-release, add the new MAVlink message to `common.xml` or add the new dialect dialect_name.xml in the message definitions. Do not checkout your MAVlink branch because it is not the version synced with ROS.`/src/mavlink-gbp-release/message_definitions/common.xml`，note that custom messages for MAVlink 2.0 can only be written in `common.xml`.

  - Use the command `catkin build mavlink` to generate the MAVlink header files (no need to manually generate `.py` files), and the generated header files are in `~/catkin_ws/build/mavlink/include/`.
  
#### 2. Customize MAVROS messages
  - Add the custom message `.msg` file in `/src/mavros/mavros_msg/msg` (service model is in `srv`).
  - Change the CMakeLists.txt file: `add_message_files(SpeedControlStatus.msg)`
 
#### 3. Write message processing plugins
  - Add the plugin path：`/src/mavros/mavros/src/plugins`
  - Reference code:`/src/mavros/mavros/src/plugins/manual_control.cpp`（typical）
  or `speed_control.cpp`
  
#### 4. Add custom plugins to the plugin list
  - Path: `~/catkin_ws/src/mavros/mavros/mavros_plugins.xml`
  - Purpose: Used to automatically load plugins in MAVROS
  
#### 5. Add custom plugins to the plugin list
  - Path: `~/catkin_ws/src/mavros/mavros/CMakeLists.txt`
  - Purpose: Add plugins to the compilation
  - Add the content: `add_library(mavros_plugins src/plugins/crawl_control.cpp)`
  
 #### 6. Write launch execution files
  - Path: `~/catkin_ws/src/mavros/mavros/launch`
  - File contents: `.launch` and `.yaml` files can be written based on `px4.launch`
  - In the `px4.launch` file, you can set the USB interface, baud rate, system id, mavlink version, etc.
  - In `px4_pluginlists.yaml`, you can set a plugin blacklist (plugins not included in the blacklist will be executed by default).
  
 #### 7. Motion control
  - Path：~/catkin_ws/src/mavros/mavros/src/
  - Code content: Refer to `SpeedControlSet_pub.cpp` for details
  - Note that the message frequency should not be too high.
  
 #### 8. Test
  - Test environment: DJI A-board (including custom mavlink 2.0 message receiving and sending, corresponding to the mavlink message ID of the upper computer), ROS, Ubuntu20.04
  - `roscore`
  - Compilation :`catkin build`
  - Fixed world coordinate: `rosrun tf2_ros static_transform_publisher 0 0 0 0 0 0 1 camera_odom_frame `
  - Publish T265 message:`roslaunch realsense2_camera rs_t265.launch `
  - Kalman filtering:`roslaunch robot_pose_ekf robot_pose_ekf.launch`
  - Launch mavros:`roslaunch mavros wtr_tasks_5.launch `
  - Safety settings:Launch xbox：`roslaunch wtr_tasks_3 wtr_tasks_3.launch`
  - Motion control:`rosrun mavros xxx`
  - Visualization:`rqt rviz rqt_graph rqt_tf_tree`等
  - Data visualization:`rosbag` + `plotjugger`
  
 #### 9. tips
  - Note that when creating a workspace, use `catkin build` instead of catkin_make.
  - The motion control code needs to add compilation dependencies, and configure `CMakeLists.txt`.
  
#### 10. Fusion of IMU, odometer, and visual odometer data with extended Kalman filter
  - Description: The function and algorithm implementation of Kalman filter can be referred to [this article](http://www.bzarg.com/p/how-a-kalman-filter-works-in-pictures),  up "DR_CAN", up host "421 construction team". In ROS, the Kalman filter can be conveniently used through the `robot_pose_ekf` package. For specific instructions, please refer to [wiki](http://wiki.ros.org/robot_pose_ekf).
  - Installation: Install the robot_pose_ekf package. I used binary installation `sudo apt install ros-xxx-robot_pose_ekf*`, and source code installation should also be possible.
  - Compilation and running: `roscd robot_pose_ekf` `rosmake` `roslaunch robot_pose_ekf.launch` can process and publish data in subscribed topics.
  - Remap for name remapping: The robot_pose_ekf node subscribes to three sensor sources: IMU, odometer, and visual odometer vo. The node can automatically detect available sources. If you want to add your own sensors, you can use remap for name remapping. For example, in this project, T265 visual odometer is used, you can remap vo to the topic published by T265 visual odometer: /camera/odom, and imu_data and odom can also be remapped separately to perform data fusion for positioning. For specific instructions, please refer to [wiki](http://wiki.ros.org/robot_pose_ekf/Tutorials/AddingGpsSensor).
  - Write a publisher to subscribe to the filtered data: For topic names, message types, etc., please refer to the wiki or translated articles on CSDN.
  - Testing: Publish T265 message: `roslaunch realsense2_camera rs_t265.launch` Kalman filtering: `roslaunch robot_pose_ekf robot_pose_ekf.launch` Motion control: `rosrun mavros xxx You can use plotjugger` to test the filtering effect.
  - Tips: 1. Remember to add package dependencies. 2.Add the header file `<geometry_msgs/PoseWithCovarianceStamped.h>`. 3. `robot_pose_ekf` is only suitable for wheeled mobile robots on a plane.
#### 11. Velocity Profile Planning
  - Explanation: The S-shaped acceleration and deceleration curve is relatively smooth, which can reduce the impact during the control process and make the interpolation process more flexible. The theory and program implementation can be referred to [this article](https://blog.csdn.net/u010632165/article/details/104951091), and there are many resources available.
  - Function Usage: When calling the function, parameters (current time, initial velocity, final velocity, target distance, target velocity, target acceleration, target deceleration, target jerk) need to be passed in, and the return value can be modified as needed.
  - Function Purpose: Automatically generate an S-curve based on the parameters. If the parameters are not appropriate, the function can automatically generate the appropriate maximum speed to complete point-to-point trajectory planning. However, because binary search is used to determine the maximum speed, real-time results cannot be provided. Setting the jerk too small may cause the function to fail to work, reflecting the system's flexibility.
  - The target velocity depends on the system's motion capability, the target acceleration depends on the system's maximum acceleration, and the target jerk reflects the system's shock resistance, reflecting the system's flexibility.
#### 12. Use of Wheel Localization System(OPS-9)

#### 13. Use of DT35 Distance Sensor
## Project File Description
## Effect presentation
  - 11.16 Translation: Added Kalman filtering, but since the coordinate jitter is not significant, the effect is not very obvious.
  
  ![11.16 y](https://github.com/szf01/Underpan-upper-computer/raw/master/img_storage/df4808fcfc458988658241c942bb094.jpg)
  - 11.18 Plan the velocity in the x direction.
  
  ![11.18 x](https://github.com/szf01/Underpan-Upper-Computer/blob/master/img_storage/S_curve_2_x.png)
  
  ![11.18 y](https://github.com/szf01/Underpan-Upper-Computer/blob/master/img_storage/S_curve_2_y.png)
  
## Optimization Ideas and Progress
  - Nov. 16: Need to optimize control algorithms (try PI controllers or PID), path planning (unknown), trajectory optimization (estimate maximum acceleration, set acceleration and deceleration curves to reduce slip and speed jumps), mechanical structure optimization (reduce jitter, precise dimensions).
  - Nov. 18: Use S-shaped velocity curve to plan velocity, and adjust parameters according to actual site and needs to reduce speed jumps and slip.
  - Nov. 27: Navigation (global and local path planning) is basically solved, and stability should be considered when making chassis for the mechanical structure. Assembling of localization system, calibration of wheel odometer, IMU, and distance sensors, and laser radar should be considered for localization.
  
  
