// Auto-generated. Do not edit!

// (in-package mavros_msgs.msg)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------

class SpeedControlSet_sub {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vx_set_sub = null;
      this.vy_set_sub = null;
      this.vw_set_sub = null;
      this.x_set_sub = null;
      this.y_set_sub = null;
    }
    else {
      if (initObj.hasOwnProperty('vx_set_sub')) {
        this.vx_set_sub = initObj.vx_set_sub
      }
      else {
        this.vx_set_sub = 0.0;
      }
      if (initObj.hasOwnProperty('vy_set_sub')) {
        this.vy_set_sub = initObj.vy_set_sub
      }
      else {
        this.vy_set_sub = 0.0;
      }
      if (initObj.hasOwnProperty('vw_set_sub')) {
        this.vw_set_sub = initObj.vw_set_sub
      }
      else {
        this.vw_set_sub = 0.0;
      }
      if (initObj.hasOwnProperty('x_set_sub')) {
        this.x_set_sub = initObj.x_set_sub
      }
      else {
        this.x_set_sub = 0.0;
      }
      if (initObj.hasOwnProperty('y_set_sub')) {
        this.y_set_sub = initObj.y_set_sub
      }
      else {
        this.y_set_sub = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SpeedControlSet_sub
    // Serialize message field [vx_set_sub]
    bufferOffset = _serializer.float32(obj.vx_set_sub, buffer, bufferOffset);
    // Serialize message field [vy_set_sub]
    bufferOffset = _serializer.float32(obj.vy_set_sub, buffer, bufferOffset);
    // Serialize message field [vw_set_sub]
    bufferOffset = _serializer.float32(obj.vw_set_sub, buffer, bufferOffset);
    // Serialize message field [x_set_sub]
    bufferOffset = _serializer.float32(obj.x_set_sub, buffer, bufferOffset);
    // Serialize message field [y_set_sub]
    bufferOffset = _serializer.float32(obj.y_set_sub, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SpeedControlSet_sub
    let len;
    let data = new SpeedControlSet_sub(null);
    // Deserialize message field [vx_set_sub]
    data.vx_set_sub = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vy_set_sub]
    data.vy_set_sub = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vw_set_sub]
    data.vw_set_sub = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [x_set_sub]
    data.x_set_sub = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [y_set_sub]
    data.y_set_sub = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 20;
  }

  static datatype() {
    // Returns string type for a message object
    return 'mavros_msgs/SpeedControlSet_sub';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'ad82db84ef54bcd533c01136895f6b3e';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 vx_set_sub
    float32 vy_set_sub
    float32 vw_set_sub
    
    float32 x_set_sub
    float32 y_set_sub
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SpeedControlSet_sub(null);
    if (msg.vx_set_sub !== undefined) {
      resolved.vx_set_sub = msg.vx_set_sub;
    }
    else {
      resolved.vx_set_sub = 0.0
    }

    if (msg.vy_set_sub !== undefined) {
      resolved.vy_set_sub = msg.vy_set_sub;
    }
    else {
      resolved.vy_set_sub = 0.0
    }

    if (msg.vw_set_sub !== undefined) {
      resolved.vw_set_sub = msg.vw_set_sub;
    }
    else {
      resolved.vw_set_sub = 0.0
    }

    if (msg.x_set_sub !== undefined) {
      resolved.x_set_sub = msg.x_set_sub;
    }
    else {
      resolved.x_set_sub = 0.0
    }

    if (msg.y_set_sub !== undefined) {
      resolved.y_set_sub = msg.y_set_sub;
    }
    else {
      resolved.y_set_sub = 0.0
    }

    return resolved;
    }
};

module.exports = SpeedControlSet_sub;
