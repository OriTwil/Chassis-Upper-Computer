
"use strict";

let CommandCode = require('./CommandCode.js');
let WaypointList = require('./WaypointList.js');
let HilStateQuaternion = require('./HilStateQuaternion.js');
let Mavlink = require('./Mavlink.js');
let PositionTarget = require('./PositionTarget.js');
let AttitudeTarget = require('./AttitudeTarget.js');
let GPSRAW = require('./GPSRAW.js');
let WheelOdomStamped = require('./WheelOdomStamped.js');
let ESCStatusItem = require('./ESCStatusItem.js');
let ExtendedState = require('./ExtendedState.js');
let OnboardComputerStatus = require('./OnboardComputerStatus.js');
let RTCM = require('./RTCM.js');
let RCIn = require('./RCIn.js');
let Waypoint = require('./Waypoint.js');
let EstimatorStatus = require('./EstimatorStatus.js');
let MountControl = require('./MountControl.js');
let DebugValue = require('./DebugValue.js');
let ManualControl = require('./ManualControl.js');
let TerrainReport = require('./TerrainReport.js');
let OpticalFlowRad = require('./OpticalFlowRad.js');
let BatteryStatus = require('./BatteryStatus.js');
let CamIMUStamp = require('./CamIMUStamp.js');
let HilSensor = require('./HilSensor.js');
let RCOut = require('./RCOut.js');
let ESCStatus = require('./ESCStatus.js');
let MagnetometerReporter = require('./MagnetometerReporter.js');
let GPSRTK = require('./GPSRTK.js');
let Trajectory = require('./Trajectory.js');
let TimesyncStatus = require('./TimesyncStatus.js');
let CellularStatus = require('./CellularStatus.js');
let VFR_HUD = require('./VFR_HUD.js');
let Thrust = require('./Thrust.js');
let GPSINPUT = require('./GPSINPUT.js');
let CompanionProcessStatus = require('./CompanionProcessStatus.js');
let HilGPS = require('./HilGPS.js');
let State = require('./State.js');
let SpeedControlStatus = require('./SpeedControlStatus.js');
let Tunnel = require('./Tunnel.js');
let WaypointReached = require('./WaypointReached.js');
let RTKBaseline = require('./RTKBaseline.js');
let ESCInfo = require('./ESCInfo.js');
let ESCTelemetry = require('./ESCTelemetry.js');
let Altitude = require('./Altitude.js');
let StatusText = require('./StatusText.js');
let LogEntry = require('./LogEntry.js');
let NavControllerOutput = require('./NavControllerOutput.js');
let OverrideRCIn = require('./OverrideRCIn.js');
let LandingTarget = require('./LandingTarget.js');
let Vibration = require('./Vibration.js');
let ESCInfoItem = require('./ESCInfoItem.js');
let HilActuatorControls = require('./HilActuatorControls.js');
let FileEntry = require('./FileEntry.js');
let GlobalPositionTarget = require('./GlobalPositionTarget.js');
let ESCTelemetryItem = require('./ESCTelemetryItem.js');
let ActuatorControl = require('./ActuatorControl.js');
let RadioStatus = require('./RadioStatus.js');
let HomePosition = require('./HomePosition.js');
let VehicleInfo = require('./VehicleInfo.js');
let Param = require('./Param.js');
let ParamValue = require('./ParamValue.js');
let PlayTuneV2 = require('./PlayTuneV2.js');
let CameraImageCaptured = require('./CameraImageCaptured.js');
let LogData = require('./LogData.js');
let ADSBVehicle = require('./ADSBVehicle.js');
let HilControls = require('./HilControls.js');

module.exports = {
  CommandCode: CommandCode,
  WaypointList: WaypointList,
  HilStateQuaternion: HilStateQuaternion,
  Mavlink: Mavlink,
  PositionTarget: PositionTarget,
  AttitudeTarget: AttitudeTarget,
  GPSRAW: GPSRAW,
  WheelOdomStamped: WheelOdomStamped,
  ESCStatusItem: ESCStatusItem,
  ExtendedState: ExtendedState,
  OnboardComputerStatus: OnboardComputerStatus,
  RTCM: RTCM,
  RCIn: RCIn,
  Waypoint: Waypoint,
  EstimatorStatus: EstimatorStatus,
  MountControl: MountControl,
  DebugValue: DebugValue,
  ManualControl: ManualControl,
  TerrainReport: TerrainReport,
  OpticalFlowRad: OpticalFlowRad,
  BatteryStatus: BatteryStatus,
  CamIMUStamp: CamIMUStamp,
  HilSensor: HilSensor,
  RCOut: RCOut,
  ESCStatus: ESCStatus,
  MagnetometerReporter: MagnetometerReporter,
  GPSRTK: GPSRTK,
  Trajectory: Trajectory,
  TimesyncStatus: TimesyncStatus,
  CellularStatus: CellularStatus,
  VFR_HUD: VFR_HUD,
  Thrust: Thrust,
  GPSINPUT: GPSINPUT,
  CompanionProcessStatus: CompanionProcessStatus,
  HilGPS: HilGPS,
  State: State,
  SpeedControlStatus: SpeedControlStatus,
  Tunnel: Tunnel,
  WaypointReached: WaypointReached,
  RTKBaseline: RTKBaseline,
  ESCInfo: ESCInfo,
  ESCTelemetry: ESCTelemetry,
  Altitude: Altitude,
  StatusText: StatusText,
  LogEntry: LogEntry,
  NavControllerOutput: NavControllerOutput,
  OverrideRCIn: OverrideRCIn,
  LandingTarget: LandingTarget,
  Vibration: Vibration,
  ESCInfoItem: ESCInfoItem,
  HilActuatorControls: HilActuatorControls,
  FileEntry: FileEntry,
  GlobalPositionTarget: GlobalPositionTarget,
  ESCTelemetryItem: ESCTelemetryItem,
  ActuatorControl: ActuatorControl,
  RadioStatus: RadioStatus,
  HomePosition: HomePosition,
  VehicleInfo: VehicleInfo,
  Param: Param,
  ParamValue: ParamValue,
  PlayTuneV2: PlayTuneV2,
  CameraImageCaptured: CameraImageCaptured,
  LogData: LogData,
  ADSBVehicle: ADSBVehicle,
  HilControls: HilControls,
};
