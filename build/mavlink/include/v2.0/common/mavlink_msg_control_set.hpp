// MESSAGE CONTROL_SET support class

#pragma once

namespace mavlink {
namespace common {
namespace msg {

/**
 * @brief CONTROL_SET message
 *
 * 接收来自上位机的消息
 */
struct CONTROL_SET : mavlink::Message {
    static constexpr msgid_t MSG_ID = 9;
    static constexpr size_t LENGTH = 24;
    static constexpr size_t MIN_LENGTH = 24;
    static constexpr uint8_t CRC_EXTRA = 207;
    static constexpr auto NAME = "CONTROL_SET";


    float vx_set; /*<  x 方向速度 */
    float vy_set; /*<  y 方向速度 */
    float vw_set; /*<  z 方向角速度 */
    float x_set; /*<  x 方向速度 */
    float y_set; /*<  y 方向速度 */
    float w_set; /*<  z 方向角速度 */


    inline std::string get_name(void) const override
    {
            return NAME;
    }

    inline Info get_message_info(void) const override
    {
            return { MSG_ID, LENGTH, MIN_LENGTH, CRC_EXTRA };
    }

    inline std::string to_yaml(void) const override
    {
        std::stringstream ss;

        ss << NAME << ":" << std::endl;
        ss << "  vx_set: " << vx_set << std::endl;
        ss << "  vy_set: " << vy_set << std::endl;
        ss << "  vw_set: " << vw_set << std::endl;
        ss << "  x_set: " << x_set << std::endl;
        ss << "  y_set: " << y_set << std::endl;
        ss << "  w_set: " << w_set << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << vx_set;                        // offset: 0
        map << vy_set;                        // offset: 4
        map << vw_set;                        // offset: 8
        map << x_set;                         // offset: 12
        map << y_set;                         // offset: 16
        map << w_set;                         // offset: 20
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> vx_set;                        // offset: 0
        map >> vy_set;                        // offset: 4
        map >> vw_set;                        // offset: 8
        map >> x_set;                         // offset: 12
        map >> y_set;                         // offset: 16
        map >> w_set;                         // offset: 20
    }
};

} // namespace msg
} // namespace common
} // namespace mavlink
