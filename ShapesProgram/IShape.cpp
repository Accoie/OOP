#include "IShape.h"

std::string IShape::ColorToHex(uint32_t color) const
{
    std::stringstream ss;
    ss << std::setfill('0') << std::setw(6) << std::hex << color;

    return ss.str();
}