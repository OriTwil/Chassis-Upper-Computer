; Auto-generated. Do not edit!


(cl:in-package mavros_msgs-msg)


;//! \htmlinclude Posture.msg.html

(cl:defclass <Posture> (roslisp-msg-protocol:ros-message)
  ((pos_x_state
    :reader pos_x_state
    :initarg :pos_x_state
    :type cl:float
    :initform 0.0)
   (pos_y_state
    :reader pos_y_state
    :initarg :pos_y_state
    :type cl:float
    :initform 0.0)
   (zangle_state
    :reader zangle_state
    :initarg :zangle_state
    :type cl:float
    :initform 0.0)
   (xangle_state
    :reader xangle_state
    :initarg :xangle_state
    :type cl:float
    :initform 0.0)
   (yangle_state
    :reader yangle_state
    :initarg :yangle_state
    :type cl:float
    :initform 0.0)
   (w_z_state
    :reader w_z_state
    :initarg :w_z_state
    :type cl:float
    :initform 0.0)
   (header
    :reader header
    :initarg :header
    :type std_msgs-msg:Header
    :initform (cl:make-instance 'std_msgs-msg:Header)))
)

(cl:defclass Posture (<Posture>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Posture>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Posture)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mavros_msgs-msg:<Posture> is deprecated: use mavros_msgs-msg:Posture instead.")))

(cl:ensure-generic-function 'pos_x_state-val :lambda-list '(m))
(cl:defmethod pos_x_state-val ((m <Posture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:pos_x_state-val is deprecated.  Use mavros_msgs-msg:pos_x_state instead.")
  (pos_x_state m))

(cl:ensure-generic-function 'pos_y_state-val :lambda-list '(m))
(cl:defmethod pos_y_state-val ((m <Posture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:pos_y_state-val is deprecated.  Use mavros_msgs-msg:pos_y_state instead.")
  (pos_y_state m))

(cl:ensure-generic-function 'zangle_state-val :lambda-list '(m))
(cl:defmethod zangle_state-val ((m <Posture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:zangle_state-val is deprecated.  Use mavros_msgs-msg:zangle_state instead.")
  (zangle_state m))

(cl:ensure-generic-function 'xangle_state-val :lambda-list '(m))
(cl:defmethod xangle_state-val ((m <Posture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:xangle_state-val is deprecated.  Use mavros_msgs-msg:xangle_state instead.")
  (xangle_state m))

(cl:ensure-generic-function 'yangle_state-val :lambda-list '(m))
(cl:defmethod yangle_state-val ((m <Posture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:yangle_state-val is deprecated.  Use mavros_msgs-msg:yangle_state instead.")
  (yangle_state m))

(cl:ensure-generic-function 'w_z_state-val :lambda-list '(m))
(cl:defmethod w_z_state-val ((m <Posture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:w_z_state-val is deprecated.  Use mavros_msgs-msg:w_z_state instead.")
  (w_z_state m))

(cl:ensure-generic-function 'header-val :lambda-list '(m))
(cl:defmethod header-val ((m <Posture>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-msg:header-val is deprecated.  Use mavros_msgs-msg:header instead.")
  (header m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Posture>) ostream)
  "Serializes a message object of type '<Posture>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pos_x_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'pos_y_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'zangle_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'xangle_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'yangle_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'w_z_state))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (roslisp-msg-protocol:serialize (cl:slot-value msg 'header) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Posture>) istream)
  "Deserializes a message object of type '<Posture>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pos_x_state) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'pos_y_state) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'zangle_state) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'xangle_state) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'yangle_state) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'w_z_state) (roslisp-utils:decode-single-float-bits bits)))
  (roslisp-msg-protocol:deserialize (cl:slot-value msg 'header) istream)
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Posture>)))
  "Returns string type for a message object of type '<Posture>"
  "mavros_msgs/Posture")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Posture)))
  "Returns string type for a message object of type 'Posture"
  "mavros_msgs/Posture")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Posture>)))
  "Returns md5sum for a message object of type '<Posture>"
  "9c16718438cf31bb244fa8df603829bf")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Posture)))
  "Returns md5sum for a message object of type 'Posture"
  "9c16718438cf31bb244fa8df603829bf")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Posture>)))
  "Returns full string definition for message of type '<Posture>"
  (cl:format cl:nil "float32 pos_x_state~%float32 pos_y_state~%float32 zangle_state~%float32 xangle_state~%float32 yangle_state~%float32 w_z_state~%~%std_msgs/Header header~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Posture)))
  "Returns full string definition for message of type 'Posture"
  (cl:format cl:nil "float32 pos_x_state~%float32 pos_y_state~%float32 zangle_state~%float32 xangle_state~%float32 yangle_state~%float32 w_z_state~%~%std_msgs/Header header~%================================================================================~%MSG: std_msgs/Header~%# Standard metadata for higher-level stamped data types.~%# This is generally used to communicate timestamped data ~%# in a particular coordinate frame.~%# ~%# sequence ID: consecutively increasing ID ~%uint32 seq~%#Two-integer timestamp that is expressed as:~%# * stamp.sec: seconds (stamp_secs) since epoch (in Python the variable is called 'secs')~%# * stamp.nsec: nanoseconds since stamp_secs (in Python the variable is called 'nsecs')~%# time-handling sugar is provided by the client library~%time stamp~%#Frame this data is associated with~%string frame_id~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Posture>))
  (cl:+ 0
     4
     4
     4
     4
     4
     4
     (roslisp-msg-protocol:serialization-length (cl:slot-value msg 'header))
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Posture>))
  "Converts a ROS message object to a list"
  (cl:list 'Posture
    (cl:cons ':pos_x_state (pos_x_state msg))
    (cl:cons ':pos_y_state (pos_y_state msg))
    (cl:cons ':zangle_state (zangle_state msg))
    (cl:cons ':xangle_state (xangle_state msg))
    (cl:cons ':yangle_state (yangle_state msg))
    (cl:cons ':w_z_state (w_z_state msg))
    (cl:cons ':header (header msg))
))
