
(cl:in-package :asdf)

(defsystem "GCRobotics-msg"
  :depends-on (:roslisp-msg-protocol :roslisp-utils )
  :components ((:file "_package")
    (:file "i2cData" :depends-on ("_package_i2cData"))
    (:file "_package_i2cData" :depends-on ("_package"))
    (:file "Encoder_msg" :depends-on ("_package_Encoder_msg"))
    (:file "_package_Encoder_msg" :depends-on ("_package"))
    (:file "simpleVelocity" :depends-on ("_package_simpleVelocity"))
    (:file "_package_simpleVelocity" :depends-on ("_package"))
    (:file "Pose_msg" :depends-on ("_package_Pose_msg"))
    (:file "_package_Pose_msg" :depends-on ("_package"))
  ))