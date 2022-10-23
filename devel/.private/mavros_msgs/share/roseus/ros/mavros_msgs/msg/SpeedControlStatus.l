;; Auto-generated. Do not edit!


(when (boundp 'mavros_msgs::SpeedControlStatus)
  (if (not (find-package "MAVROS_MSGS"))
    (make-package "MAVROS_MSGS"))
  (shadow 'SpeedControlStatus (find-package "MAVROS_MSGS")))
(unless (find-package "MAVROS_MSGS::SPEEDCONTROLSTATUS")
  (make-package "MAVROS_MSGS::SPEEDCONTROLSTATUS"))

(in-package "ROS")
;;//! \htmlinclude SpeedControlStatus.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mavros_msgs::SpeedControlStatus
  :super ros::object
  :slots (_vx_state _vy_state _vw_state _header ))

(defmethod mavros_msgs::SpeedControlStatus
  (:init
   (&key
    ((:vx_state __vx_state) 0.0)
    ((:vy_state __vy_state) 0.0)
    ((:vw_state __vw_state) 0.0)
    ((:header __header) (instance std_msgs::Header :init))
    )
   (send-super :init)
   (setq _vx_state (float __vx_state))
   (setq _vy_state (float __vy_state))
   (setq _vw_state (float __vw_state))
   (setq _header __header)
   self)
  (:vx_state
   (&optional __vx_state)
   (if __vx_state (setq _vx_state __vx_state)) _vx_state)
  (:vy_state
   (&optional __vy_state)
   (if __vy_state (setq _vy_state __vy_state)) _vy_state)
  (:vw_state
   (&optional __vw_state)
   (if __vw_state (setq _vw_state __vw_state)) _vw_state)
  (:header
   (&rest __header)
   (if (keywordp (car __header))
       (send* _header __header)
     (progn
       (if __header (setq _header (car __header)))
       _header)))
  (:serialization-length
   ()
   (+
    ;; float32 _vx_state
    4
    ;; float32 _vy_state
    4
    ;; float32 _vw_state
    4
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _vx_state
       (sys::poke _vx_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy_state
       (sys::poke _vy_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vw_state
       (sys::poke _vw_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _vx_state
     (setq _vx_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy_state
     (setq _vy_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vw_state
     (setq _vw_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;;
   self)
  )

(setf (get mavros_msgs::SpeedControlStatus :md5sum-) "345bbbfcdfc76f6def5475842d240947")
(setf (get mavros_msgs::SpeedControlStatus :datatype-) "mavros_msgs/SpeedControlStatus")
(setf (get mavros_msgs::SpeedControlStatus :definition-)
      "float32 vx_state
float32 vy_state
float32 vw_state


std_msgs/Header header
================================================================================
MSG: std_msgs/Header
# Standard metadata for higher-level stamped data types.
# This is generally used to communicate timestamped data 
# in a particular coordinate frame.
# 
# sequence ID: consecutively increasing ID 
uint32 seq
#Two-integer timestamp that is expressed as:
# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')
# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')
# time-handling sugar is provided by the client library
time stamp
#Frame this data is associated with
string frame_id

")



(provide :mavros_msgs/SpeedControlStatus "345bbbfcdfc76f6def5475842d240947")


