; Auto-generated. Do not edit!


(cl:in-package mavros_msgs-msg)


;//! \htmlinclude SpeedControlStatus.msg.html

(cl:defclass <SpeedControlStatus> (roslisp-msg-protocol:ros-message)
  ((vx_state
    :reader vx_state
    :initarg :vx_state
    :type cl:float
    :initform 0.0)
   (vy_state
    :reader vy_state
    :initarg :vy_state
    :type cl:float
    :initform 0.0)
   (vw_state
    :reader vw_state
    :initarg :vw_state
    :type cl:float
    :initform 0.0)
   (header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header)))
)

(cl:defclass SpeedControlStatus (<SpeedControlStatus>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SpeedControlStatus>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SpeedControlStatus)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mavros_msgs-msg:<SpeedControlStatus> is deprecated: use mavros_msgs-msg:SpeedControlStatus instead.")))

(cl:ensure-generic-function 'vx_state-val :lambda-list '(m))
(cl:defmethod vx_state-val ((m <SpeedControlStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:vx_state-val is deprecated.  Use mavros_msgs-msg:vx_state instead.")
  (vx_state m))

(cl:ensure-generic-function 'vy_state-val :lambda-list '(m))
(cl:defmethod vy_state-val ((m <SpeedControlStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:vy_state-val is deprecated.  Use mavros_msgs-msg:vy_state instead.")
  (vy_state m))

(cl:ensure-generic-function 'vw_state-val :lambda-list '(m))
(cl:defmethod vw_state-val ((m <SpeedControlStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:vw_state-val is deprecated.  Use mavros_msgs-msg:vw_state instead.")
  (vw_state m))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <SpeedControlStatus>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:header-val is deprecated.  Use mavros_msgs-msg:header instead.")
  (header m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SpeedControlStatus>) ostream)
  "Serializes a message object of type '<SpeedControlStatus>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vw_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SpeedControlStatus>) istream)
  "Deserializes a message object of type '<SpeedControlStatus>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx_state) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy_state) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vw_state) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SpeedControlStatus>)))
  "Returns string type for a message object of type '<SpeedControlStatus>"
  "mavros_msgs/SpeedControlStatus")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SpeedControlStatus)))
  "Returns string type for a message object of type 'SpeedControlStatus"
  "mavros_msgs/SpeedControlStatus")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SpeedControlStatus>)))
  "Returns md5sum for a message object of type '<SpeedControlStatus>"
  "345bbbfcdfc76f6def5475842d240947")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SpeedControlStatus)))
  "Returns md5sum for a message object of type 'SpeedControlStatus"
  "345bbbfcdfc76f6def5475842d240947")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SpeedControlStatus>)))
  "Returns full string definition for message of type '<SpeedControlStatus>"
  (cl:format cl:nil "float32 vx_state~%float32 vy_state~%float32 vw_state~%~%~%std_msgs/Header header~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SpeedControlStatus)))
  "Returns full string definition for message of type 'SpeedControlStatus"
  (cl:format cl:nil "float32 vx_state~%float32 vy_state~%float32 vw_state~%~%~%std_msgs/Header header~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SpeedControlStatus>))
  (cl:+ 0
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SpeedControlStatus>))
  "Converts a ROS message object to a list"
  (cl:list 'SpeedControlStatus
    (cl:cons ':vx_state (vx_state msg))
    (cl:cons ':vy_state (vy_state msg))
    (cl:cons ':vw_state (vw_state msg))
    (cl:cons ':header (header msg))
))
