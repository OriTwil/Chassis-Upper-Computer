; Auto-generated. Do not edit!


(cl:in-package mavros_msgs-srv)


;//! \htmlinclude SpeedControlSet-request.msg.html

(cl:defclass <SpeedControlSet-request> (roslisp-msg-protocol:ros-message)
  ((vx_set
    :reader vx_set
    :initarg :vx_set
    :type cl:float
    :initform 0.0)
   (vy_set
    :reader vy_set
    :initarg :vy_set
    :type cl:float
    :initform 0.0)
   (vw_set
    :reader vw_set
    :initarg :vw_set
    :type cl:float
    :initform 0.0))
)

(cl:defclass SpeedControlSet-request (<SpeedControlSet-request>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SpeedControlSet-request>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SpeedControlSet-request)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mavros_msgs-srv:<SpeedControlSet-request> is deprecated: use mavros_msgs-srv:SpeedControlSet-request instead.")))

(cl:ensure-generic-function 'vx_set-val :lambda-list '(m))
(cl:defmethod vx_set-val ((m <SpeedControlSet-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-srv:vx_set-val is deprecated.  Use mavros_msgs-srv:vx_set instead.")
  (vx_set m))

(cl:ensure-generic-function 'vy_set-val :lambda-list '(m))
(cl:defmethod vy_set-val ((m <SpeedControlSet-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-srv:vy_set-val is deprecated.  Use mavros_msgs-srv:vy_set instead.")
  (vy_set m))

(cl:ensure-generic-function 'vw_set-val :lambda-list '(m))
(cl:defmethod vw_set-val ((m <SpeedControlSet-request>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-srv:vw_set-val is deprecated.  Use mavros_msgs-srv:vw_set instead.")
  (vw_set m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SpeedControlSet-request>) ostream)
  "Serializes a message object of type '<SpeedControlSet-request>"
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vx_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vy_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-single-float-bits (cl:slot-value msg 'vw_set))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream))
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SpeedControlSet-request>) istream)
  "Deserializes a message object of type '<SpeedControlSet-request>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vx_set) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vy_set) (roslisp-utils:decode-single-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'vw_set) (roslisp-utils:decode-single-float-bits bits)))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SpeedControlSet-request>)))
  "Returns string type for a service object of type '<SpeedControlSet-request>"
  "mavros_msgs/SpeedControlSetRequest")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SpeedControlSet-request)))
  "Returns string type for a service object of type 'SpeedControlSet-request"
  "mavros_msgs/SpeedControlSetRequest")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SpeedControlSet-request>)))
  "Returns md5sum for a message object of type '<SpeedControlSet-request>"
  "6a0060d83b9d2b0d745139269e8066b7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SpeedControlSet-request)))
  "Returns md5sum for a message object of type 'SpeedControlSet-request"
  "6a0060d83b9d2b0d745139269e8066b7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SpeedControlSet-request>)))
  "Returns full string definition for message of type '<SpeedControlSet-request>"
  (cl:format cl:nil "float32 vx_set~%float32 vy_set~%float32 vw_set~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SpeedControlSet-request)))
  "Returns full string definition for message of type 'SpeedControlSet-request"
  (cl:format cl:nil "float32 vx_set~%float32 vy_set~%float32 vw_set~%~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SpeedControlSet-request>))
  (cl:+ 0
     4
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SpeedControlSet-request>))
  "Converts a ROS message object to a list"
  (cl:list 'SpeedControlSet-request
    (cl:cons ':vx_set (vx_set msg))
    (cl:cons ':vy_set (vy_set msg))
    (cl:cons ':vw_set (vw_set msg))
))
;//! \htmlinclude SpeedControlSet-response.msg.html

(cl:defclass <SpeedControlSet-response> (roslisp-msg-protocol:ros-message)
  ((send_success
    :reader send_success
    :initarg :send_success
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass SpeedControlSet-response (<SpeedControlSet-response>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <SpeedControlSet-response>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'SpeedControlSet-response)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name mavros_msgs-srv:<SpeedControlSet-response> is deprecated: use mavros_msgs-srv:SpeedControlSet-response instead.")))

(cl:ensure-generic-function 'send_success-val :lambda-list '(m))
(cl:defmethod send_success-val ((m <SpeedControlSet-response>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader mavros_msgs-srv:send_success-val is deprecated.  Use mavros_msgs-srv:send_success instead.")
  (send_success m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <SpeedControlSet-response>) ostream)
  "Serializes a message object of type '<SpeedControlSet-response>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'send_success) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <SpeedControlSet-response>) istream)
  "Deserializes a message object of type '<SpeedControlSet-response>"
    (cl:setf (cl:slot-value msg 'send_success) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<SpeedControlSet-response>)))
  "Returns string type for a service object of type '<SpeedControlSet-response>"
  "mavros_msgs/SpeedControlSetResponse")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SpeedControlSet-response)))
  "Returns string type for a service object of type 'SpeedControlSet-response"
  "mavros_msgs/SpeedControlSetResponse")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<SpeedControlSet-response>)))
  "Returns md5sum for a message object of type '<SpeedControlSet-response>"
  "6a0060d83b9d2b0d745139269e8066b7")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'SpeedControlSet-response)))
  "Returns md5sum for a message object of type 'SpeedControlSet-response"
  "6a0060d83b9d2b0d745139269e8066b7")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<SpeedControlSet-response>)))
  "Returns full string definition for message of type '<SpeedControlSet-response>"
  (cl:format cl:nil "bool send_success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'SpeedControlSet-response)))
  "Returns full string definition for message of type 'SpeedControlSet-response"
  (cl:format cl:nil "bool send_success~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <SpeedControlSet-response>))
  (cl:+ 0
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <SpeedControlSet-response>))
  "Converts a ROS message object to a list"
  (cl:list 'SpeedControlSet-response
    (cl:cons ':send_success (send_success msg))
))
(cl:defmethod roslisp-msg-protocol:service-request-type ((msg (cl:eql 'SpeedControlSet)))
  'SpeedControlSet-request)
(cl:defmethod roslisp-msg-protocol:service-response-type ((msg (cl:eql 'SpeedControlSet)))
  'SpeedControlSet-response)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'SpeedControlSet)))
  "Returns string type for a service object of type '<SpeedControlSet>"
  "mavros_msgs/SpeedControlSet")