;; Auto-generated. Do not edit!


(when (boundp 'mavros_msgs::Posture)
  (if (not (find-package "MAVROS_MSGS"))
    (make-package "MAVROS_MSGS"))
  (shadow 'Posture (find-package "MAVROS_MSGS")))
(unless (find-package "MAVROS_MSGS::POSTURE")
  (make-package "MAVROS_MSGS::POSTURE"))

(in-package "ROS")
;;//! \htmlinclude Posture.msg.html
(if (not (find-package "STD_MSGS"))
  (ros::roseus-add-msgs "std_msgs"))


(defclass mavros_msgs::Posture
  :super ros::object
  :slots (_pos_x_state _pos_y_state _zangle_state _xangle_state _yangle_state _w_z_state _header ))

(defmethod mavros_msgs::Posture
  (:init
   (&key
    ((:pos_x_state __pos_x_state) 0.0)
    ((:pos_y_state __pos_y_state) 0.0)
    ((:zangle_state __zangle_state) 0.0)
    ((:xangle_state __xangle_state) 0.0)
    ((:yangle_state __yangle_state) 0.0)
    ((:w_z_state __w_z_state) 0.0)
    ((:header __header) (instance std_msgs::Header :init))
    )
   (send-super :init)
   (setq _pos_x_state (float __pos_x_state))
   (setq _pos_y_state (float __pos_y_state))
   (setq _zangle_state (float __zangle_state))
   (setq _xangle_state (float __xangle_state))
   (setq _yangle_state (float __yangle_state))
   (setq _w_z_state (float __w_z_state))
   (setq _header __header)
   self)
  (:pos_x_state
   (&optional __pos_x_state)
   (if __pos_x_state (setq _pos_x_state __pos_x_state)) _pos_x_state)
  (:pos_y_state
   (&optional __pos_y_state)
   (if __pos_y_state (setq _pos_y_state __pos_y_state)) _pos_y_state)
  (:zangle_state
   (&optional __zangle_state)
   (if __zangle_state (setq _zangle_state __zangle_state)) _zangle_state)
  (:xangle_state
   (&optional __xangle_state)
   (if __xangle_state (setq _xangle_state __xangle_state)) _xangle_state)
  (:yangle_state
   (&optional __yangle_state)
   (if __yangle_state (setq _yangle_state __yangle_state)) _yangle_state)
  (:w_z_state
   (&optional __w_z_state)
   (if __w_z_state (setq _w_z_state __w_z_state)) _w_z_state)
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
    ;; float32 _pos_x_state
    4
    ;; float32 _pos_y_state
    4
    ;; float32 _zangle_state
    4
    ;; float32 _xangle_state
    4
    ;; float32 _yangle_state
    4
    ;; float32 _w_z_state
    4
    ;; std_msgs/Header _header
    (send _header :serialization-length)
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _pos_x_state
       (sys::poke _pos_x_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _pos_y_state
       (sys::poke _pos_y_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _zangle_state
       (sys::poke _zangle_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _xangle_state
       (sys::poke _xangle_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _yangle_state
       (sys::poke _yangle_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _w_z_state
       (sys::poke _w_z_state (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; std_msgs/Header _header
       (send _header :serialize s)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _pos_x_state
     (setq _pos_x_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _pos_y_state
     (setq _pos_y_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _zangle_state
     (setq _zangle_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _xangle_state
     (setq _xangle_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _yangle_state
     (setq _yangle_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _w_z_state
     (setq _w_z_state (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; std_msgs/Header _header
     (send _header :deserialize buf ptr-) (incf ptr- (send _header :serialization-length))
   ;;
   self)
  )

(setf (get mavros_msgs::Posture :md5sum-) "9c16718438cf31bb244fa8df603829bf")
(setf (get mavros_msgs::Posture :datatype-) "mavros_msgs/Posture")
(setf (get mavros_msgs::Posture :definition-)
      "float32 pos_x_state
float32 pos_y_state
float32 zangle_state
float32 xangle_state
float32 yangle_state
float32 w_z_state

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



(provide :mavros_msgs/Posture "9c16718438cf31bb244fa8df603829bf")


