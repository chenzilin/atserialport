#include <string>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <unistd.h>

#include "SerialPort.h"

using namespace std;
using namespace LibSerial;

int main()
{
    SerialPort serial_port;
    serial_port.Open("/dev/ttyUSB2");
    serial_port.SetBaudRate(BaudRate::BAUD_115200);
    serial_port.SetCharacterSize(CharacterSize::CHAR_SIZE_8);
    serial_port.SetFlowControl(FlowControl::FLOW_CONTROL_NONE);
    serial_port.SetParity(Parity::PARITY_NONE);
    serial_port.SetStopBits(StopBits::STOP_BITS_1);

    std::string read_buffer;
    size_t ms_timeout = 1000; // 100ms

    serial_port.Write("AT\r\n");

    try {
        // Read as many bytes as are available during the timeout period.
        serial_port.Read(read_buffer, 0, ms_timeout);
    } catch (ReadTimeout) {}

    std::cout << read_buffer << std::flush;

    return EXIT_SUCCESS;
}
