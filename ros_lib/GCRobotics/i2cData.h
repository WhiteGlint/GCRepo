#ifndef _ROS_GCRobotics_i2cData_h
#define _ROS_GCRobotics_i2cData_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace GCRobotics
{

  class i2cData : public ros::Msg
  {
    public:
      uint8_t address;
      uint8_t messageType;
      uint8_t messageData;
      uint8_t messageData2;
      bool expectDataBack;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      *(outbuffer + offset + 0) = (this->address >> (8 * 0)) & 0xFF;
      offset += sizeof(this->address);
      *(outbuffer + offset + 0) = (this->messageType >> (8 * 0)) & 0xFF;
      offset += sizeof(this->messageType);
      *(outbuffer + offset + 0) = (this->messageData >> (8 * 0)) & 0xFF;
      offset += sizeof(this->messageData);
      *(outbuffer + offset + 0) = (this->messageData2 >> (8 * 0)) & 0xFF;
      offset += sizeof(this->messageData2);
      union {
        bool real;
        uint8_t base;
      } u_expectDataBack;
      u_expectDataBack.real = this->expectDataBack;
      *(outbuffer + offset + 0) = (u_expectDataBack.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->expectDataBack);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      this->address =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->address);
      this->messageType =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->messageType);
      this->messageData =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->messageData);
      this->messageData2 =  ((uint8_t) (*(inbuffer + offset)));
      offset += sizeof(this->messageData2);
      union {
        bool real;
        uint8_t base;
      } u_expectDataBack;
      u_expectDataBack.base = 0;
      u_expectDataBack.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->expectDataBack = u_expectDataBack.real;
      offset += sizeof(this->expectDataBack);
     return offset;
    }

    const char * getType(){ return "GCRobotics/i2cData"; };
    const char * getMD5(){ return "d01c895b6711f1c2ae3a87aec070ecb6"; };

  };

}
#endif