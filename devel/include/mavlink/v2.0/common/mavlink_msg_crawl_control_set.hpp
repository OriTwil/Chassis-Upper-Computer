// MESSAGE CRAWL_CONTROL_SET support class

#pragma once

namespace mavlink {
namespace common {
namespace msg {

/**
 * @brief CRAWL_CONTROL_SET message
 *
 * Speed control system set param mavlink message
 */
struct CRAWL_CONTROL_SET : mavlink::Message {
    static constexpr msgid_t MSG_ID = 500;
    static constexpr size_t LENGTH = 12;
    static constexpr size_t MIN_LENGTH = 12;
    static constexpr uint8_t CRC_EXTRA = 203;
    static constexpr auto NAME = "CRAWL_CONTROL_SET";


    float vx_set; /*<  float */
    float vy_set; /*<  float */
    float vw_set; /*<  float */


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

        return ss.str();
    }

    inline void serialize(mavlink::MsgMap &map) const override
    {
        map.reset(MSG_ID, LENGTH);

        map << vx_set;                        // offset: 0
        map << vy_set;                        // offset: 4
        map << vw_set;                        // offset: 8
    }

    inline void deserialize(mavlink::MsgMap &map) override
    {
        map >> vx_set;                        // offset: 0
        map >> vy_set;                        // offset: 4
        map >> vw_set;                        // offset: 8
    }
};

} // namespace msg
} // namespace common
} // namespace mavlink
