;; Auto-generated. Do not edit!


(when (boundp 'mavros_msgs::SpeedControlSet_sub)
  (if (not (find-package "MAVROS_MSGS"))
    (make-package "MAVROS_MSGS"))
  (shadow 'SpeedControlSet_sub (find-package "MAVROS_MSGS")))
(unless (find-package "MAVROS_MSGS::SPEEDCONTROLSET_SUB")
  (make-package "MAVROS_MSGS::SPEEDCONTROLSET_SUB"))

(in-package "ROS")
;;//! \htmlinclude SpeedControlSet_sub.msg.html


(defclass mavros_msgs::SpeedControlSet_sub
  :super ros::object
  :slots (_vx_set_sub _vy_set_sub _vw_set_sub ))

(defmethod mavros_msgs::SpeedControlSet_sub
  (:init
   (&key
    ((:vx_set_sub __vx_set_sub) 0.0)
    ((:vy_set_sub __vy_set_sub) 0.0)
    ((:vw_set_sub __vw_set_sub) 0.0)
    )
   (send-super :init)
   (setq _vx_set_sub (float __vx_set_sub))
   (setq _vy_set_sub (float __vy_set_sub))
   (setq _vw_set_sub (float __vw_set_sub))
   self)
  (:vx_set_sub
   (&optional __vx_set_sub)
   (if __vx_set_sub (setq _vx_set_sub __vx_set_sub)) _vx_set_sub)
  (:vy_set_sub
   (&optional __vy_set_sub)
   (if __vy_set_sub (setq _vy_set_sub __vy_set_sub)) _vy_set_sub)
  (:vw_set_sub
   (&optional __vw_set_sub)
   (if __vw_set_sub (setq _vw_set_sub __vw_set_sub)) _vw_set_sub)
  (:serialization-length
   ()
   (+
    ;; float32 _vx_set_sub
    4
    ;; float32 _vy_set_sub
    4
    ;; float32 _vw_set_sub
    4
    ))
  (:serialize
   (&optional strm)
   (let ((s (if strm strm
              (make-string-output-stream (send self :serialization-length)))))
     ;; float32 _vx_set_sub
       (sys::poke _vx_set_sub (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vy_set_sub
       (sys::poke _vy_set_sub (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;; float32 _vw_set_sub
       (sys::poke _vw_set_sub (send s :buffer) (send s :count) :float) (incf (stream-count s) 4)
     ;;
     (if (null strm) (get-output-stream-string s))))
  (:deserialize
   (buf &optional (ptr- 0))
   ;; float32 _vx_set_sub
     (setq _vx_set_sub (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vy_set_sub
     (setq _vy_set_sub (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;; float32 _vw_set_sub
     (setq _vw_set_sub (sys::peek buf ptr- :float)) (incf ptr- 4)
   ;;
   self)
  )

(setf (get mavros_msgs::SpeedControlSet_sub :md5sum-) "09372848c4245dfd0a6169928f0d8a97")
(setf (get mavros_msgs::SpeedControlSet_sub :datatype-) "mavros_msgs/SpeedControlSet_sub")
(setf (get mavros_msgs::SpeedControlSet_sub :definition-)
      "float32 vx_set_sub
float32 vy_set_sub
float32 vw_set_sub
")



(provide :mavros_msgs/SpeedControlSet_sub "09372848c4245dfd0a6169928f0d8a97")


