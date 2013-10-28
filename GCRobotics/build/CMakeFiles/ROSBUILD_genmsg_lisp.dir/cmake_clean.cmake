FILE(REMOVE_RECURSE
  "../msg_gen"
  "../msg_gen"
  "../src/GCRobotics/msg"
  "CMakeFiles/ROSBUILD_genmsg_lisp"
  "../msg_gen/lisp/i2cData.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_i2cData.lisp"
  "../msg_gen/lisp/Encoder_msg.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_Encoder_msg.lisp"
  "../msg_gen/lisp/simpleVelocity.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_simpleVelocity.lisp"
  "../msg_gen/lisp/Pose_msg.lisp"
  "../msg_gen/lisp/_package.lisp"
  "../msg_gen/lisp/_package_Pose_msg.lisp"
)

# Per-language clean rules from dependency scanning.
FOREACH(lang)
  INCLUDE(CMakeFiles/ROSBUILD_genmsg_lisp.dir/cmake_clean_${lang}.cmake OPTIONAL)
ENDFOREACH(lang)
