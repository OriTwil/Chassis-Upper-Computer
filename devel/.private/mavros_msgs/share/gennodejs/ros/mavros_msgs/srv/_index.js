
"use strict";

let CommandLong = require('./CommandLong.js')
let SetMavFrame = require('./SetMavFrame.js')
let CommandAck = require('./CommandAck.js')
let ParamGet = require('./ParamGet.js')
let WaypointClear = require('./WaypointClear.js')
let LogRequestEnd = require('./LogRequestEnd.js')
let FileRemove = require('./FileRemove.js')
let ParamPush = require('./ParamPush.js')
let CommandTriggerInterval = require('./CommandTriggerInterval.js')
let ParamPull = require('./ParamPull.js')
let CommandVtolTransition = require('./CommandVtolTransition.js')
let FileChecksum = require('./FileChecksum.js')
let ParamSet = require('./ParamSet.js')
let WaypointSetCurrent = require('./WaypointSetCurrent.js')
let SetMode = require('./SetMode.js')
let FileMakeDir = require('./FileMakeDir.js')
let FileOpen = require('./FileOpen.js')
let CommandTriggerControl = require('./CommandTriggerControl.js')
let CommandTOL = require('./CommandTOL.js')
let VehicleInfoGet = require('./VehicleInfoGet.js')
let StreamRate = require('./StreamRate.js')
let WaypointPull = require('./WaypointPull.js')
let FileClose = require('./FileClose.js')
let WaypointPush = require('./WaypointPush.js')
let FileTruncate = require('./FileTruncate.js')
let CommandHome = require('./CommandHome.js')
let FileRead = require('./FileRead.js')
let CommandInt = require('./CommandInt.js')
let FileList = require('./FileList.js')
let FileWrite = require('./FileWrite.js')
let LogRequestList = require('./LogRequestList.js')
let FileRemoveDir = require('./FileRemoveDir.js')
let FileRename = require('./FileRename.js')
let MessageInterval = require('./MessageInterval.js')
let SpeedControlSet = require('./SpeedControlSet.js')
let LogRequestData = require('./LogRequestData.js')
let CommandBool = require('./CommandBool.js')
let MountConfigure = require('./MountConfigure.js')

module.exports = {
  CommandLong: CommandLong,
  SetMavFrame: SetMavFrame,
  CommandAck: CommandAck,
  ParamGet: ParamGet,
  WaypointClear: WaypointClear,
  LogRequestEnd: LogRequestEnd,
  FileRemove: FileRemove,
  ParamPush: ParamPush,
  CommandTriggerInterval: CommandTriggerInterval,
  ParamPull: ParamPull,
  CommandVtolTransition: CommandVtolTransition,
  FileChecksum: FileChecksum,
  ParamSet: ParamSet,
  WaypointSetCurrent: WaypointSetCurrent,
  SetMode: SetMode,
  FileMakeDir: FileMakeDir,
  FileOpen: FileOpen,
  CommandTriggerControl: CommandTriggerControl,
  CommandTOL: CommandTOL,
  VehicleInfoGet: VehicleInfoGet,
  StreamRate: StreamRate,
  WaypointPull: WaypointPull,
  FileClose: FileClose,
  WaypointPush: WaypointPush,
  FileTruncate: FileTruncate,
  CommandHome: CommandHome,
  FileRead: FileRead,
  CommandInt: CommandInt,
  FileList: FileList,
  FileWrite: FileWrite,
  LogRequestList: LogRequestList,
  FileRemoveDir: FileRemoveDir,
  FileRename: FileRename,
  MessageInterval: MessageInterval,
  SpeedControlSet: SpeedControlSet,
  LogRequestData: LogRequestData,
  CommandBool: CommandBool,
  MountConfigure: MountConfigure,
};
