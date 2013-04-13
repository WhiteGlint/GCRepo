#ifndef _ROS_GCRobotics_Encoder_msg_h
#define _ROS_GCRobotics_Encoder_msg_h

#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include "ros/msg.h"

namespace GCRobotics
{

  class Encoder_msg : public ros::Msg
  {
    public:
      float encoder1;
      float encoder2;
      float encoder3;
      float encoder4;
      bool direction1;
      bool direction2;
      bool direction3;
      bool direction4;

    virtual int serialize(unsigned char *outbuffer) const
    {
      int offset = 0;
      int32_t * val_encoder1 = (int32_t *) &(this->encoder1);
      int32_t exp_encoder1 = (((*val_encoder1)>>23)&255);
      if(exp_encoder1 != 0)
        exp_encoder1 += 1023-127;
      int32_t sig_encoder1 = *val_encoder1;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_encoder1<<5) & 0xff;
      *(outbuffer + offset++) = (sig_encoder1>>3) & 0xff;
      *(outbuffer + offset++) = (sig_encoder1>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_encoder1<<4) & 0xF0) | ((sig_encoder1>>19)&0x0F);
      *(outbuffer + offset++) = (exp_encoder1>>4) & 0x7F;
      if(this->encoder1 < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_encoder2 = (int32_t *) &(this->encoder2);
      int32_t exp_encoder2 = (((*val_encoder2)>>23)&255);
      if(exp_encoder2 != 0)
        exp_encoder2 += 1023-127;
      int32_t sig_encoder2 = *val_encoder2;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_encoder2<<5) & 0xff;
      *(outbuffer + offset++) = (sig_encoder2>>3) & 0xff;
      *(outbuffer + offset++) = (sig_encoder2>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_encoder2<<4) & 0xF0) | ((sig_encoder2>>19)&0x0F);
      *(outbuffer + offset++) = (exp_encoder2>>4) & 0x7F;
      if(this->encoder2 < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_encoder3 = (int32_t *) &(this->encoder3);
      int32_t exp_encoder3 = (((*val_encoder3)>>23)&255);
      if(exp_encoder3 != 0)
        exp_encoder3 += 1023-127;
      int32_t sig_encoder3 = *val_encoder3;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_encoder3<<5) & 0xff;
      *(outbuffer + offset++) = (sig_encoder3>>3) & 0xff;
      *(outbuffer + offset++) = (sig_encoder3>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_encoder3<<4) & 0xF0) | ((sig_encoder3>>19)&0x0F);
      *(outbuffer + offset++) = (exp_encoder3>>4) & 0x7F;
      if(this->encoder3 < 0) *(outbuffer + offset -1) |= 0x80;
      int32_t * val_encoder4 = (int32_t *) &(this->encoder4);
      int32_t exp_encoder4 = (((*val_encoder4)>>23)&255);
      if(exp_encoder4 != 0)
        exp_encoder4 += 1023-127;
      int32_t sig_encoder4 = *val_encoder4;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = 0;
      *(outbuffer + offset++) = (sig_encoder4<<5) & 0xff;
      *(outbuffer + offset++) = (sig_encoder4>>3) & 0xff;
      *(outbuffer + offset++) = (sig_encoder4>>11) & 0xff;
      *(outbuffer + offset++) = ((exp_encoder4<<4) & 0xF0) | ((sig_encoder4>>19)&0x0F);
      *(outbuffer + offset++) = (exp_encoder4>>4) & 0x7F;
      if(this->encoder4 < 0) *(outbuffer + offset -1) |= 0x80;
      union {
        bool real;
        uint8_t base;
      } u_direction1;
      u_direction1.real = this->direction1;
      *(outbuffer + offset + 0) = (u_direction1.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction1);
      union {
        bool real;
        uint8_t base;
      } u_direction2;
      u_direction2.real = this->direction2;
      *(outbuffer + offset + 0) = (u_direction2.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction2);
      union {
        bool real;
        uint8_t base;
      } u_direction3;
      u_direction3.real = this->direction3;
      *(outbuffer + offset + 0) = (u_direction3.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction3);
      union {
        bool real;
        uint8_t base;
      } u_direction4;
      u_direction4.real = this->direction4;
      *(outbuffer + offset + 0) = (u_direction4.base >> (8 * 0)) & 0xFF;
      offset += sizeof(this->direction4);
      return offset;
    }

    virtual int deserialize(unsigned char *inbuffer)
    {
      int offset = 0;
      uint32_t * val_encoder1 = (uint32_t*) &(this->encoder1);
      offset += 3;
      *val_encoder1 = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_encoder1 |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_encoder1 |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_encoder1 |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_encoder1 = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_encoder1 |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_encoder1 !=0)
        *val_encoder1 |= ((exp_encoder1)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->encoder1 = -this->encoder1;
      uint32_t * val_encoder2 = (uint32_t*) &(this->encoder2);
      offset += 3;
      *val_encoder2 = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_encoder2 |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_encoder2 |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_encoder2 |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_encoder2 = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_encoder2 |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_encoder2 !=0)
        *val_encoder2 |= ((exp_encoder2)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->encoder2 = -this->encoder2;
      uint32_t * val_encoder3 = (uint32_t*) &(this->encoder3);
      offset += 3;
      *val_encoder3 = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_encoder3 |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_encoder3 |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_encoder3 |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_encoder3 = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_encoder3 |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_encoder3 !=0)
        *val_encoder3 |= ((exp_encoder3)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->encoder3 = -this->encoder3;
      uint32_t * val_encoder4 = (uint32_t*) &(this->encoder4);
      offset += 3;
      *val_encoder4 = ((uint32_t)(*(inbuffer + offset++))>>5 & 0x07);
      *val_encoder4 |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<3;
      *val_encoder4 |= ((uint32_t)(*(inbuffer + offset++)) & 0xff)<<11;
      *val_encoder4 |= ((uint32_t)(*(inbuffer + offset)) & 0x0f)<<19;
      uint32_t exp_encoder4 = ((uint32_t)(*(inbuffer + offset++))&0xf0)>>4;
      exp_encoder4 |= ((uint32_t)(*(inbuffer + offset)) & 0x7f)<<4;
      if(exp_encoder4 !=0)
        *val_encoder4 |= ((exp_encoder4)-1023+127)<<23;
      if( ((*(inbuffer+offset++)) & 0x80) > 0) this->encoder4 = -this->encoder4;
      union {
        bool real;
        uint8_t base;
      } u_direction1;
      u_direction1.base = 0;
      u_direction1.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->direction1 = u_direction1.real;
      offset += sizeof(this->direction1);
      union {
        bool real;
        uint8_t base;
      } u_direction2;
      u_direction2.base = 0;
      u_direction2.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->direction2 = u_direction2.real;
      offset += sizeof(this->direction2);
      union {
        bool real;
        uint8_t base;
      } u_direction3;
      u_direction3.base = 0;
      u_direction3.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->direction3 = u_direction3.real;
      offset += sizeof(this->direction3);
      union {
        bool real;
        uint8_t base;
      } u_direction4;
      u_direction4.base = 0;
      u_direction4.base |= ((uint8_t) (*(inbuffer + offset + 0))) << (8 * 0);
      this->direction4 = u_direction4.real;
      offset += sizeof(this->direction4);
     return offset;
    }

    const char * getType(){ return "GCRobotics/Encoder_msg"; };
    const char * getMD5(){ return "1f3c9338c8adf9eef290f5ae7c5d32ec"; };

  };

}
#endif