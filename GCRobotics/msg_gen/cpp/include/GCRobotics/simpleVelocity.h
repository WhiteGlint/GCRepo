/* Auto-generated by genmsg_cpp for file /home/josh/GCRepo/GCRobotics/msg/simpleVelocity.msg */
#ifndef GCROBOTICS_MESSAGE_SIMPLEVELOCITY_H
#define GCROBOTICS_MESSAGE_SIMPLEVELOCITY_H
#include <string>
#include <vector>
#include <map>
#include <ostream>
#include "ros/serialization.h"
#include "ros/builtin_message_traits.h"
#include "ros/message_operations.h"
#include "ros/time.h"

#include "ros/macros.h"

#include "ros/assert.h"


namespace GCRobotics
{
template <class ContainerAllocator>
struct simpleVelocity_ {
  typedef simpleVelocity_<ContainerAllocator> Type;

  simpleVelocity_()
  : speed(0)
  , direction(0)
  {
  }

  simpleVelocity_(const ContainerAllocator& _alloc)
  : speed(0)
  , direction(0)
  {
  }

  typedef int32_t _speed_type;
  int32_t speed;

  typedef int32_t _direction_type;
  int32_t direction;


  typedef boost::shared_ptr< ::GCRobotics::simpleVelocity_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::GCRobotics::simpleVelocity_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct simpleVelocity
typedef  ::GCRobotics::simpleVelocity_<std::allocator<void> > simpleVelocity;

typedef boost::shared_ptr< ::GCRobotics::simpleVelocity> simpleVelocityPtr;
typedef boost::shared_ptr< ::GCRobotics::simpleVelocity const> simpleVelocityConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::GCRobotics::simpleVelocity_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::GCRobotics::simpleVelocity_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace GCRobotics

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::GCRobotics::simpleVelocity_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::GCRobotics::simpleVelocity_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::GCRobotics::simpleVelocity_<ContainerAllocator> > {
  static const char* value() 
  {
    return "c132692a08c074e6ae3270af166b3df3";
  }

  static const char* value(const  ::GCRobotics::simpleVelocity_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xc132692a08c074e6ULL;
  static const uint64_t static_value2 = 0xae3270af166b3df3ULL;
};

template<class ContainerAllocator>
struct DataType< ::GCRobotics::simpleVelocity_<ContainerAllocator> > {
  static const char* value() 
  {
    return "GCRobotics/simpleVelocity";
  }

  static const char* value(const  ::GCRobotics::simpleVelocity_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::GCRobotics::simpleVelocity_<ContainerAllocator> > {
  static const char* value() 
  {
    return "int32 speed\n\
int32 direction\n\
\n\
";
  }

  static const char* value(const  ::GCRobotics::simpleVelocity_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::GCRobotics::simpleVelocity_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::GCRobotics::simpleVelocity_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.speed);
    stream.next(m.direction);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct simpleVelocity_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::GCRobotics::simpleVelocity_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::GCRobotics::simpleVelocity_<ContainerAllocator> & v) 
  {
    s << indent << "speed: ";
    Printer<int32_t>::stream(s, indent + "  ", v.speed);
    s << indent << "direction: ";
    Printer<int32_t>::stream(s, indent + "  ", v.direction);
  }
};


} // namespace message_operations
} // namespace ros

#endif // GCROBOTICS_MESSAGE_SIMPLEVELOCITY_H

