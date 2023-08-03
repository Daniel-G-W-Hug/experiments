#ifndef HD_DI8JOY_HPP
#define HD_DI8JOY_HPP

#include <cstddef> // size_t
#include <string>

namespace hd
{

class js // class for joysticks using direct input on windows
{
  public:

    static constexpr std::size_t max_nJoystick = 8; // max. number of supported joysticks
    static constexpr std::size_t max_nButton = 128; // max. number of supported buttons
    static constexpr std::size_t max_nPOV = 4;      // max. number of supported POV hats
    static constexpr std::size_t max_nAxis = 8;     // max. number of supported axes

    static constexpr unsigned int X = 0x10000000;  // X axis        (+128)
    static constexpr unsigned int Y = 0x01000000;  // Y axis        (+64)
    static constexpr unsigned int Z = 0x00100000;  // Z axis        (+32)
    static constexpr unsigned int Rx = 0x00010000; // Rx axis       (+16)
    static constexpr unsigned int Ry = 0x00001000; // Ry axis       (+8)
    static constexpr unsigned int Rz = 0x00000100; // Rz axis       (+4)
    static constexpr unsigned int S0 = 0x00000010; // Slider axis 0 (+2)
    static constexpr unsigned int S1 = 0x00000001; // Slider axis 1 (+1)

    struct dev_id // joystick device id
    {
        // assigned properties either user provided or defaulted to enumeration sequence
        unsigned int a_id{0};    // internal unique reference to map to capabilities
                                 // (used for internal referencing in input files)
        unsigned int a_index{0}; // internal unique index [0..nJoystick)
                                 // (used for defining the device sequence)
        std::string a_name{};    // internal name, typically convenient short version of sys_name

        // system assigned values obtained from direct input
        std::string sys_name{"no joystick"}; // name of the joystick
        unsigned int sys_product_id{0};      // product identifier
        unsigned int sys_vendor_id{0};       // manufacturer identifier
    };

    struct dev_cap // joystick device capabilities
    {
        unsigned int axis_flags{0}; // flags indicate which of the 8 axis are supported
        std::string axis_string{};  // show supported axes as string
        unsigned int nAxis{0};      // actual number of axis (max. 8)
        unsigned int nButton{0};    // actual number of buttons supported by the joystick (max. 128)
        unsigned int nPOV{0};       // actual number of pov hats (max. 4)
    };

    struct dev // joystick device
    {
        dev_id id;   // device id (user + system provided)
        dev_cap cap; // device capabilities
    };

    struct dev_button // maps button number to button name
    {
        unsigned int index{0}; // button index [0..nButton)
        std::string name{};    // button name (defaults to button_no, if not user-provided via mapping)
        // button number not defined here, because it defaults to index + 1
    };

    struct dev_button_action
    {
        unsigned int a_id{0};  // reference to device
        unsigned int index{0}; // reference to button of device
        unsigned int mode{};   // 0: immediate mode (default), 1: timed mode
    };

    ///////////////////////////
    // rest of class goes here
    ///////////////////////////

}; // class js

} // namespace hd

#endif // HD_DI8JOY_HPP