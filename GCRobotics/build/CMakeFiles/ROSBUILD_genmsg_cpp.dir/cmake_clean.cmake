FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/GCRobotics/msg"
  "CMakeFiles/ROSBUILD_genmsg_cpp"
  "../msg_gen/cpp/include/GCRobotics/i2cData.h"
  "../msg_gen/cpp/include/GCRobotics/simpleVelocity.h"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_cpp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
