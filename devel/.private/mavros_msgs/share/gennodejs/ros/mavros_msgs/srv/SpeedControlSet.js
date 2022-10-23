// Auto-generated. Do not edit!

// (in-package mavros_msgs.srv)


"use strict";

const _serializer = _ros_msg_utils.Serialize;
const _arraySerializer = _serializer.Array;
const _deserializer = _ros_msg_utils.Deserialize;
const _arrayDeserializer = _deserializer.Array;
const _finder = _ros_msg_utils.Find;
const _getByteLength = _ros_msg_utils.getByteLength;

//-----------------------------------------------------------


//-----------------------------------------------------------

class SpeedControlSetRequest {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.vx_set = null;
      this.vy_set = null;
      this.vw_set = null;
    }
    else {
      if (initObj.hasOwnProperty('vx_set')) {
        this.vx_set = initObj.vx_set
      }
      else {
        this.vx_set = 0.0;
      }
      if (initObj.hasOwnProperty('vy_set')) {
        this.vy_set = initObj.vy_set
      }
      else {
        this.vy_set = 0.0;
      }
      if (initObj.hasOwnProperty('vw_set')) {
        this.vw_set = initObj.vw_set
      }
      else {
        this.vw_set = 0.0;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SpeedControlSetRequest
    // Serialize message field [vx_set]
    bufferOffset = _serializer.float32(obj.vx_set, buffer, bufferOffset);
    // Serialize message field [vy_set]
    bufferOffset = _serializer.float32(obj.vy_set, buffer, bufferOffset);
    // Serialize message field [vw_set]
    bufferOffset = _serializer.float32(obj.vw_set, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SpeedControlSetRequest
    let len;
    let data = new SpeedControlSetRequest(null);
    // Deserialize message field [vx_set]
    data.vx_set = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vy_set]
    data.vy_set = _deserializer.float32(buffer, bufferOffset);
    // Deserialize message field [vw_set]
    data.vw_set = _deserializer.float32(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 12;
  }

  static datatype() {
    // Returns string type for a service object
    return 'mavros_msgs/SpeedControlSetRequest';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return 'c534057ba0143748321db675c6edc6f5';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    float32 vx_set
    float32 vy_set
    float32 vw_set
    
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SpeedControlSetRequest(null);
    if (msg.vx_set !== undefined) {
      resolved.vx_set = msg.vx_set;
    }
    else {
      resolved.vx_set = 0.0
    }

    if (msg.vy_set !== undefined) {
      resolved.vy_set = msg.vy_set;
    }
    else {
      resolved.vy_set = 0.0
    }

    if (msg.vw_set !== undefined) {
      resolved.vw_set = msg.vw_set;
    }
    else {
      resolved.vw_set = 0.0
    }

    return resolved;
    }
};

class SpeedControlSetResponse {
  constructor(initObj={}) {
    if (initObj === null) {
      // initObj === null is a special case for deserialization where we don't initialize fields
      this.send_success = null;
    }
    else {
      if (initObj.hasOwnProperty('send_success')) {
        this.send_success = initObj.send_success
      }
      else {
        this.send_success = false;
      }
    }
  }

  static serialize(obj, buffer, bufferOffset) {
    // Serializes a message object of type SpeedControlSetResponse
    // Serialize message field [send_success]
    bufferOffset = _serializer.bool(obj.send_success, buffer, bufferOffset);
    return bufferOffset;
  }

  static deserialize(buffer, bufferOffset=[0]) {
    //deserializes a message object of type SpeedControlSetResponse
    let len;
    let data = new SpeedControlSetResponse(null);
    // Deserialize message field [send_success]
    data.send_success = _deserializer.bool(buffer, bufferOffset);
    return data;
  }

  static getMessageSize(object) {
    return 1;
  }

  static datatype() {
    // Returns string type for a service object
    return 'mavros_msgs/SpeedControlSetResponse';
  }

  static md5sum() {
    //Returns md5sum for a message object
    return '56d282e179c5c746013c5b1090241cab';
  }

  static messageDefinition() {
    // Returns full string definition for message
    return `
    bool send_success
    
    `;
  }

  static Resolve(msg) {
    // deep-construct a valid message object instance of whatever was passed in
    if (typeof msg !== 'object' || msg === null) {
      msg = {};
    }
    const resolved = new SpeedControlSetResponse(null);
    if (msg.send_success !== undefined) {
      resolved.send_success = msg.send_success;
    }
    else {
      resolved.send_success = false
    }

    return resolved;
    }
};

module.exports = {
  Request: SpeedControlSetRequest,
  Response: SpeedControlSetResponse,
  md5sum() { return '6a0060d83b9d2b0d745139269e8066b7'; },
  datatype() { return 'mavros_msgs/SpeedControlSet'; }
};
