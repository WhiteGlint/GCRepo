FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/GCRobotics/msg"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/GCRobotics/i2cData.h"
  "../msg_gen/cpp/include/GCRobotics/Encoder_msg.h"
  "../msg_gen/cpp/include/GCRobotics/simpleVelocity.h"
  "../msg_gen/cpp/include/GCRobotics/Pose_msg.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
