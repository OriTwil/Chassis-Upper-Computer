;; Auto-generated. Do not edit!


(when (boundp 'mavros_msgs::SpeedControlSet)
  (if (not (find-package "MAVROS_MSGS"))
    (make-package "MAVROS_MSGS"))
  (shadow 'SpeedControlSet (find-package "MAVROS_MSGS")))
(unless (find-package "MAVROS_MSGS::SPEEDCONTROLSET")
  (make-package "MAVROS_MSGS::SPEEDCONTROLSET"))
(unless (find-package "MAVROS_MSGS::SPEEDCONTROLSETREQUEST")
  (make-package "MAVROS_MSGS::SPEEDCONTROLSETREQUEST"))
(unless (find-package "MAVROS_MSGS::SPEEDCONTROLSETRESPONSE")
  (make-package "MAVROS_MSGS::SPEEDCONTROLSETRESPONSE"))

(in-package "ROS")





(defclass mavros_msgs::SpeedControlSetRequest
  :super ros::object
  :slots (_vx_set _vy_set _vw_set ))

(defmethod mavros_msgs::SpeedControlSetRequest
  (:init
   (&key
    ((:vx_set __vx_set) 0.0)
    ((:vy_set __vy_set) 0.0)
    ((:vw_set __vw_set) 0.0)
    )
   (send-super :init)
   (setq _vx_set (float __vx_set))
   (setq _vy_set (float __vy_set))
   (setq _vw_set (float __vw_set))
   self)
  (:vx_set
   (&optional __vx_set)
   (if __vx_set (setq _vx_set __vx_set)) _vx_set)
  (:vy_set
   (&optional __vy_set)
   (if __vy_set (setq _vy_set __vy_set)) _vy_set)
  (:vw_set
   (&optional __vw_set)
   (if __vw_set (setq _vw_set __vw_set)) _vw_set)
  (:serialization-length
   ()
   (+
    ;; float32 _vx_set
    4
    ;; float32 _vy_set
    4
    ;; float32 _vw_set
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _vx_set
       (sys::poke _vx_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy_set
       (sys::poke _vy_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vw_set
       (sys::poke _vw_set (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _vx_set
     (setq _vx_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy_set
     (setq _vy_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vw_set
     (setq _vw_set (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(defclass mavros_msgs::SpeedControlSetResponse
  :super ros::object
  :slots (_send_success ))

(defmethod mavros_msgs::SpeedControlSetResponse
  (:init
   (&key
    ((:send_success __send_success) nil)
    )
   (send-super :init)
   (setq _send_success __send_success)
   self)
  (:send_success
   (&optional (__send_success :null))
   (if (not (eq __send_success :null)) (setq _send_success __send_success)) _send_success)
  (:serialization-length
   ()
   (+
    ;; bool _send_success
    1
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; bool _send_success
       (if _send_success (write-byte -1 s) (write-byte 0 s))
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; bool _send_success
     (setq _send_success (not (= 0 (sys::peek buf ptr- :char)))) (incf ptr- 1)
   ;;
   self)
  )

(defclass mavros_msgs::SpeedControlSet
  :super ros::object
  :slots ())

(setf (get mavros_msgs::SpeedControlSet :md5sum-) "6a0060d83b9d2b0d745139269e8066b7")
(setf (get mavros_msgs::SpeedControlSet :datatype-) "mavros_msgs/SpeedControlSet")
(setf (get mavros_msgs::SpeedControlSet :request) mavros_msgs::SpeedControlSetRequest)
(setf (get mavros_msgs::SpeedControlSet :response) mavros_msgs::SpeedControlSetResponse)

(defmethod mavros_msgs::SpeedControlSetRequest
  (:response () (instance mavros_msgs::SpeedControlSetResponse :init)))

(setf (get mavros_msgs::SpeedControlSetRequest :md5sum-) "6a0060d83b9d2b0d745139269e8066b7")
(setf (get mavros_msgs::SpeedControlSetRequest :datatype-) "mavros_msgs/SpeedControlSetRequest")
(setf (get mavros_msgs::SpeedControlSetRequest :definition-)
      "float32 vx_set
float32 vy_set
float32 vw_set

---
bool send_success
")

(setf (get mavros_msgs::SpeedControlSetResponse :md5sum-) "6a0060d83b9d2b0d745139269e8066b7")
(setf (get mavros_msgs::SpeedControlSetResponse :datatype-) "mavros_msgs/SpeedControlSetResponse")
(setf (get mavros_msgs::SpeedControlSetResponse :definition-)
      "float32 vx_set
float32 vy_set
float32 vw_set

---
bool send_success
")



(provide :mavros_msgs/SpeedControlSet "6a0060d83b9d2b0d745139269e8066b7")


