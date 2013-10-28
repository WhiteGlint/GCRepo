/* Auto-generated by genmsg_cpp for file /home/scott/GCRepo/GCRobotics/msg/Pose_msg.msg */
#ifndef GCROBOTICS_MESSAGE_POSE_MSG_H
#define GCROBOTICS_MESSAGE_POSE_MSG_H
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
struct Pose_msg_ {
  typedef Pose_msg_<ContainerAllocator> Type;

  Pose_msg_()
  : x(0.0)
  , y(0.0)
  , z(0.0)
  , heading(0.0)
  {
  }

  Pose_msg_(const ContainerAllocator& _alloc)
  : x(0.0)
  , y(0.0)
  , z(0.0)
  , heading(0.0)
  {
  }

  typedef double _x_type;
  double x;

  typedef double _y_type;
  double y;

  typedef double _z_type;
  double z;

  typedef double _heading_type;
  double heading;


  typedef boost::shared_ptr< ::GCRobotics::Pose_msg_<ContainerAllocator> > Ptr;
  typedef boost::shared_ptr< ::GCRobotics::Pose_msg_<ContainerAllocator>  const> ConstPtr;
  boost::shared_ptr<std::map<std::string, std::string> > __connection_header;
}; // struct Pose_msg
typedef  ::GCRobotics::Pose_msg_<std::allocator<void> > Pose_msg;

typedef boost::shared_ptr< ::GCRobotics::Pose_msg> Pose_msgPtr;
typedef boost::shared_ptr< ::GCRobotics::Pose_msg const> Pose_msgConstPtr;


template<typename ContainerAllocator>
std::ostream& operator<<(std::ostream& s, const  ::GCRobotics::Pose_msg_<ContainerAllocator> & v)
{
  ros::message_operations::Printer< ::GCRobotics::Pose_msg_<ContainerAllocator> >::stream(s, "", v);
  return s;}

} // namespace GCRobotics

namespace ros
{
namespace message_traits
{
template<class ContainerAllocator> struct IsMessage< ::GCRobotics::Pose_msg_<ContainerAllocator> > : public TrueType {};
template<class ContainerAllocator> struct IsMessage< ::GCRobotics::Pose_msg_<ContainerAllocator>  const> : public TrueType {};
template<class ContainerAllocator>
struct MD5Sum< ::GCRobotics::Pose_msg_<ContainerAllocator> > {
  static const char* value() 
  {
    return "a0c8bbbba51f36b9c247a3a067516a8a";
  }

  static const char* value(const  ::GCRobotics::Pose_msg_<ContainerAllocator> &) { return value(); } 
  static const uint64_t static_value1 = 0xa0c8bbbba51f36b9ULL;
  static const uint64_t static_value2 = 0xc247a3a067516a8aULL;
};

template<class ContainerAllocator>
struct DataType< ::GCRobotics::Pose_msg_<ContainerAllocator> > {
  static const char* value() 
  {
    return "GCRobotics/Pose_msg";
  }

  static const char* value(const  ::GCRobotics::Pose_msg_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator>
struct Definition< ::GCRobotics::Pose_msg_<ContainerAllocator> > {
  static const char* value() 
  {
    return "float64 x\n\
float64 y\n\
float64 z\n\
float64 heading\n\
\n\
";
  }

  static const char* value(const  ::GCRobotics::Pose_msg_<ContainerAllocator> &) { return value(); } 
};

template<class ContainerAllocator> struct IsFixedSize< ::GCRobotics::Pose_msg_<ContainerAllocator> > : public TrueType {};
} // namespace message_traits
} // namespace ros

namespace ros
{
namespace serialization
{

template<class ContainerAllocator> struct Serializer< ::GCRobotics::Pose_msg_<ContainerAllocator> >
{
  template<typename Stream, typename T> inline static void allInOne(Stream& stream, T m)
  {
    stream.next(m.x);
    stream.next(m.y);
    stream.next(m.z);
    stream.next(m.heading);
  }

  ROS_DECLARE_ALLINONE_SERIALIZER;
}; // struct Pose_msg_
} // namespace serialization
} // namespace ros

namespace ros
{
namespace message_operations
{

template<class ContainerAllocator>
struct Printer< ::GCRobotics::Pose_msg_<ContainerAllocator> >
{
  template<typename Stream> static void stream(Stream& s, const std::string& indent, const  ::GCRobotics::Pose_msg_<ContainerAllocator> & v) 
  {
    s << indent << "x: ";
    Printer<double>::stream(s, indent + "  ", v.x);
    s << indent << "y: ";
    Printer<double>::stream(s, indent + "  ", v.y);
    s << indent << "z: ";
    Printer<double>::stream(s, indent + "  ", v.z);
    s << indent << "heading: ";
    Printer<double>::stream(s, indent + "  ", v.heading);
  }
};


} // namespace message_operations
} // namespace ros

#endif // GCROBOTICS_MESSAGE_POSE_MSG_H

