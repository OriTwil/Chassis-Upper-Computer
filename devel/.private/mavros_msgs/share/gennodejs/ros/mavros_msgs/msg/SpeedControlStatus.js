// Auto-generated. Do not edit!

// (in-package mavros_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;
let std_msgs = _finder('std_msgs');

//-----------------------------------------------------------

class SpeedControlStatus {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vx_state = null;
      this.vy_state = null;
      this.vw_state = null;
      this.header = null;
    }
    else {
      if (initObj.hasOwnProperty('vx_state')) {
        this.vx_state = initObj.vx_state
      }
      else {
        this.vx_state = 0.0;
      }
      if (initObj.hasOwnProperty('vy_state')) {
        this.vy_state = initObj.vy_state
      }
      else {
        this.vy_state = 0.0;
      }
      if (initObj.hasOwnProperty('vw_state')) {
        this.vw_state = initObj.vw_state
      }
      else {
        this.vw_state = 0.0;
      }
      if (initObj.hasOwnProperty('header')) {
        this.header = initObj.header
      }
      else {
        this.header = new std_msgs.msg.Header();
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SpeedControlStatus
    // Serialize message field [vx_state]
    bufferOffset = _serializer.float32(obj.vx_state, buffer, bufferOffset);
    // Serialize message field [vy_state]
    bufferOffset = _serializer.float32(obj.vy_state, buffer, bufferOffset);
    // Serialize message field [vw_state]
    bufferOffset = _serializer.float32(obj.vw_state, buffer, bufferOffset);
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SpeedControlStatus
    let len;
    let data = new SpeedControlStatus(null);
    // Deserialize message field [vx_state]
    data.vx_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vy_state]
    data.vy_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vw_state]
    data.vw_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 12;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mavros_msgs/SpeedControlStatus';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '345bbbfcdfc76f6def5475842d240947';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 vx_state
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SpeedControlStatus(null);
    if (msg.vx_state !== undefined) {
      resolved.vx_state = msg.vx_state;
    }
    else {
      resolved.vx_state = 0.0
    }

    if (msg.vy_state !== undefined) {
      resolved.vy_state = msg.vy_state;
    }
    else {
      resolved.vy_state = 0.0
    }

    if (msg.vw_state !== undefined) {
      resolved.vw_state = msg.vw_state;
    }
    else {
      resolved.vw_state = 0.0
    }

    if (msg.header !== undefined) {
      resolved.header = std_msgs.msg.Header.Resolve(msg.header)
    }
    else {
      resolved.header = new std_msgs.msg.Header()
    }

    return resolved;
    }
};

module.exports = SpeedControlStatus;
