// MESSAGE POSTURE support class

#pragma once

namespace mavlink {
namespace common {
namespace msg {

/**
 * @brief POSTURE message
 *
 * 把轮式平面定位系统的数据发到上位机
 */
struct POSTURE : mavlink::Message {
    static constexpr msgid_t MSG_ID = 12;
    static constexpr size_t LENGTH = 24;
    static constexpr size_t MIN_LENGTH = 24;
    static constexpr uint8_t CRC_EXTRA = 139;
    static constexpr auto NAME = "POSTURE";


    float pos_x; /*<  x 坐标 */
    float pos_y; /*<  y 位置 */
    float zangle; /*<  航向角 */
    float xangle; /*<  横滚角 */
    float yangle; /*<  俯仰角 */
    float w_z; /*<  航向角速度 */


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
        ss << "  pos_x: " << pos_x << std::endl;
        ss << "  pos_y: " << pos_y << std::endl;
        ss << "  zangle: " << zangle << std::endl;
        ss << "  xangle: " << xangle << std::endl;
        ss << "  yangle: " << yangle << std::endl;
        ss << "  w_z: " << w_z << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << pos_x;                         // offset: 0
        map << pos_y;                         // offset: 4
        map << zangle;                        // offset: 8
        map << xangle;                        // offset: 12
        map << yangle;                        // offset: 16
        map << w_z;                           // offset: 20
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> pos_x;                         // offset: 0
        map >> pos_y;                         // offset: 4
        map >> zangle;                        // offset: 8
        map >> xangle;                        // offset: 12
        map >> yangle;                        // offset: 16
        map >> w_z;                           // offset: 20
    }
};

} // namespace msg
} // namespace common
} // namespace mavlink
