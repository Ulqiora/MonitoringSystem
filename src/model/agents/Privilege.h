#pragma once 
#ifdef __APPLE__
enum class Privilege{
    IDLE = 9,
    SYSTEM = 8,
    USER = 7
};
#else
enum class Privilege{
    IDLE = 12,
    SYSTEM = 5,
    USER = 3
};
#endif