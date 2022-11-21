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

class Posture {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.pos_x_state = null;
      this.pos_y_state = null;
      this.zangle_state = null;
      this.xangle_state = null;
      this.yangle_state = null;
      this.w_z_state = null;
      this.header = null;
    }
    else {
      if (initObj.hasOwnProperty('pos_x_state')) {
        this.pos_x_state = initObj.pos_x_state
      }
      else {
        this.pos_x_state = 0.0;
      }
      if (initObj.hasOwnProperty('pos_y_state')) {
        this.pos_y_state = initObj.pos_y_state
      }
      else {
        this.pos_y_state = 0.0;
      }
      if (initObj.hasOwnProperty('zangle_state')) {
        this.zangle_state = initObj.zangle_state
      }
      else {
        this.zangle_state = 0.0;
      }
      if (initObj.hasOwnProperty('xangle_state')) {
        this.xangle_state = initObj.xangle_state
      }
      else {
        this.xangle_state = 0.0;
      }
      if (initObj.hasOwnProperty('yangle_state')) {
        this.yangle_state = initObj.yangle_state
      }
      else {
        this.yangle_state = 0.0;
      }
      if (initObj.hasOwnProperty('w_z_state')) {
        this.w_z_state = initObj.w_z_state
      }
      else {
        this.w_z_state = 0.0;
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
    // Serializes a message object of type Posture
    // Serialize message field [pos_x_state]
    bufferOffset = _serializer.float32(obj.pos_x_state, buffer, bufferOffset);
    // Serialize message field [pos_y_state]
    bufferOffset = _serializer.float32(obj.pos_y_state, buffer, bufferOffset);
    // Serialize message field [zangle_state]
    bufferOffset = _serializer.float32(obj.zangle_state, buffer, bufferOffset);
    // Serialize message field [xangle_state]
    bufferOffset = _serializer.float32(obj.xangle_state, buffer, bufferOffset);
    // Serialize message field [yangle_state]
    bufferOffset = _serializer.float32(obj.yangle_state, buffer, bufferOffset);
    // Serialize message field [w_z_state]
    bufferOffset = _serializer.float32(obj.w_z_state, buffer, bufferOffset);
    // Serialize message field [header]
    bufferOffset = std_msgs.msg.Header.serialize(obj.header, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type Posture
    let len;
    let data = new Posture(null);
    // Deserialize message field [pos_x_state]
    data.pos_x_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [pos_y_state]
    data.pos_y_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [zangle_state]
    data.zangle_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [xangle_state]
    data.xangle_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [yangle_state]
    data.yangle_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [w_z_state]
    data.w_z_state = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [header]
    data.header = std_msgs.msg.Header.deserialize(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    let length = 0;
    length += std_msgs.msg.Header.getMessageSize(object.header);
    return length + 24;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mavros_msgs/Posture';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '9c16718438cf31bb244fa8df603829bf';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 pos_x_state
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
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new Posture(null);
    if (msg.pos_x_state !== undefined) {
      resolved.pos_x_state = msg.pos_x_state;
    }
    else {
      resolved.pos_x_state = 0.0
    }

    if (msg.pos_y_state !== undefined) {
      resolved.pos_y_state = msg.pos_y_state;
    }
    else {
      resolved.pos_y_state = 0.0
    }

    if (msg.zangle_state !== undefined) {
      resolved.zangle_state = msg.zangle_state;
    }
    else {
      resolved.zangle_state = 0.0
    }

    if (msg.xangle_state !== undefined) {
      resolved.xangle_state = msg.xangle_state;
    }
    else {
      resolved.xangle_state = 0.0
    }

    if (msg.yangle_state !== undefined) {
      resolved.yangle_state = msg.yangle_state;
    }
    else {
      resolved.yangle_state = 0.0
    }

    if (msg.w_z_state !== undefined) {
      resolved.w_z_state = msg.w_z_state;
    }
    else {
      resolved.w_z_state = 0.0
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

module.exports = Posture;
