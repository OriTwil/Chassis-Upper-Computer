; Auto-generated. Do not edit!


(cl:in-package mavros_msgs-msg)


;//! \htmlinclude SpeedControlSet_sub.msg.html

(cl:defclass <SpeedControlSet_sub> (roslisp-msg-protocol:ros-message)
  ((vx_set_sub
    :reader vx_set_sub
    :initarg :vx_set_sub
    :type cl:float
    :initform 0.0)
   (vy_set_sub
    :reader vy_set_sub
    :initarg :vy_set_sub
    :type cl:float
    :initform 0.0)
   (vw_set_sub
    :reader vw_set_sub
    :initarg :vw_set_sub
    :type cl:float
    :initform 0.0)
   (x_set_sub
    :reader x_set_sub
    :initarg :x_set_sub
    :type cl:float
    :initform 0.0)
   (y_set_sub
    :reader y_set_sub
    :initarg :y_set_sub
    :type cl:float
    :initform 0.0))
)

(cl:defclass SpeedControlSet_sub (<SpeedControlSet_sub>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SpeedControlSet_sub>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SpeedControlSet_sub)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mavros_msgs-msg:<SpeedControlSet_sub> is deprecated: use mavros_msgs-msg:SpeedControlSet_sub instead.")))

(cl:ensure-generic-function 'vx_set_sub-val :lambda-list '(m))
(cl:defmethod vx_set_sub-val ((m <SpeedControlSet_sub>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:vx_set_sub-val is deprecated.  Use mavros_msgs-msg:vx_set_sub instead.")
  (vx_set_sub m))

(cl:ensure-generic-function 'vy_set_sub-val :lambda-list '(m))
(cl:defmethod vy_set_sub-val ((m <SpeedControlSet_sub>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:vy_set_sub-val is deprecated.  Use mavros_msgs-msg:vy_set_sub instead.")
  (vy_set_sub m))

(cl:ensure-generic-function 'vw_set_sub-val :lambda-list '(m))
(cl:defmethod vw_set_sub-val ((m <SpeedControlSet_sub>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:vw_set_sub-val is deprecated.  Use mavros_msgs-msg:vw_set_sub instead.")
  (vw_set_sub m))

(cl:ensure-generic-function 'x_set_sub-val :lambda-list '(m))
(cl:defmethod x_set_sub-val ((m <SpeedControlSet_sub>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:x_set_sub-val is deprecated.  Use mavros_msgs-msg:x_set_sub instead.")
  (x_set_sub m))

(cl:ensure-generic-function 'y_set_sub-val :lambda-list '(m))
(cl:defmethod y_set_sub-val ((m <SpeedControlSet_sub>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:y_set_sub-val is deprecated.  Use mavros_msgs-msg:y_set_sub instead.")
  (y_set_sub m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SpeedControlSet_sub>) ostream)
  "Serializes a message object of type '<SpeedControlSet_sub>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx_set_sub))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy_set_sub))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vw_set_sub))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'x_set_sub))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'y_set_sub))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SpeedControlSet_sub>) istream)
  "Deserializes a message object of type '<SpeedControlSet_sub>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx_set_sub) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy_set_sub) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vw_set_sub) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'x_set_sub) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'y_set_sub) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SpeedControlSet_sub>)))
  "Returns string type for a message object of type '<SpeedControlSet_sub>"
  "mavros_msgs/SpeedControlSet_sub")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SpeedControlSet_sub)))
  "Returns string type for a message object of type 'SpeedControlSet_sub"
  "mavros_msgs/SpeedControlSet_sub")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SpeedControlSet_sub>)))
  "Returns md5sum for a message object of type '<SpeedControlSet_sub>"
  "ad82db84ef54bcd533c01136895f6b3e")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SpeedControlSet_sub)))
  "Returns md5sum for a message object of type 'SpeedControlSet_sub"
  "ad82db84ef54bcd533c01136895f6b3e")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SpeedControlSet_sub>)))
  "Returns full string definition for message of type '<SpeedControlSet_sub>"
  (cl:format cl:nil "float32 vx_set_sub~%float32 vy_set_sub~%float32 vw_set_sub~%~%float32 x_set_sub~%float32 y_set_sub~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SpeedControlSet_sub)))
  "Returns full string definition for message of type 'SpeedControlSet_sub"
  (cl:format cl:nil "float32 vx_set_sub~%float32 vy_set_sub~%float32 vw_set_sub~%~%float32 x_set_sub~%float32 y_set_sub~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SpeedControlSet_sub>))
  (cl:+ 0
     4
     4
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SpeedControlSet_sub>))
  "Converts a ROS message object to a list"
  (cl:list 'SpeedControlSet_sub
    (cl:cons ':vx_set_sub (vx_set_sub msg))
    (cl:cons ':vy_set_sub (vy_set_sub msg))
    (cl:cons ':vw_set_sub (vw_set_sub msg))
    (cl:cons ':x_set_sub (x_set_sub msg))
    (cl:cons ':y_set_sub (y_set_sub msg))
))
