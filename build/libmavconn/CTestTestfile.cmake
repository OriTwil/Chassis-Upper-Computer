# CMake generated Testfile for 
# Source directory: /home/szf/ROS/catkin_ws_3/src/mavros/libmavconn
# Build directory: /home/szf/ROS/catkin_ws_3/build/libmavconn
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(_ctest_libmavconn_gtest_mavconn-test "/home/szf/ROS/catkin_ws_3/build/libmavconn/catkin_generated/env_cached.sh" "/usr/bin/python3" "/opt/ros/noetic/share/catkin/cmake/test/run_tests.py" "/home/szf/ROS/catkin_ws_3/build/libmavconn/test_results/libmavconn/gtest-mavconn-test.xml" "--return-code" "/home/szf/ROS/catkin_ws_3/devel/.private/libmavconn/lib/libmavconn/mavconn-test --gtest_output=xml:/home/szf/ROS/catkin_ws_3/build/libmavconn/test_results/libmavconn/gtest-mavconn-test.xml")
set_tests_properties(_ctest_libmavconn_gtest_mavconn-test PROPERTIES  _BACKTRACE_TRIPLES "/opt/ros/noetic/share/catkin/cmake/test/tests.cmake;160;add_test;/opt/ros/noetic/share/catkin/cmake/test/gtest.cmake;98;catkin_run_tests_target;/opt/ros/noetic/share/catkin/cmake/test/gtest.cmake;37;_catkin_add_google_test;/home/szf/ROS/catkin_ws_3/src/mavros/libmavconn/CMakeLists.txt;109;catkin_add_gtest;/home/szf/ROS/catkin_ws_3/src/mavros/libmavconn/CMakeLists.txt;0;")
subdirs("gtest")
