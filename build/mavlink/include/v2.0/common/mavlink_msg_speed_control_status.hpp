// MESSAGE SPEED_CONTROL_STATUS support class

#pragma once

namespace mavlink {
namespace common {
namespace msg {

/**
 * @brief SPEED_CONTROL_STATUS message
 *
 * Speed control system mavlink message
 */
struct SPEED_CONTROL_STATUS : mavlink::Message {
    static constexpr msgid_t MSG_ID = 10;
    static constexpr size_t LENGTH = 12;
    static constexpr size_t MIN_LENGTH = 12;
    static constexpr uint8_t CRC_EXTRA = 240;
    static constexpr auto NAME = "SPEED_CONTROL_STATUS";


    float vx_state; /*<  float */
    float vy_state; /*<  float */
    float vw_state; /*<  float */


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
        ss << "  vx_state: " << vx_state << std::endl;
        ss << "  vy_state: " << vy_state << std::endl;
        ss << "  vw_state: " << vw_state << std::endl;

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << vx_state;                      // offset: 0
        map << vy_state;                      // offset: 4
        map << vw_state;                      // offset: 8
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> vx_state;                      // offset: 0
        map >> vy_state;                      // offset: 4
        map >> vw_state;                      // offset: 8
    }
};

} // namespace msg
} // namespace common
} // namespace mavlink
