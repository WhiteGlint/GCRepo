; Auto-generated. Do not edit!


(cl:in-package GCRobotics-msg)


;//! \htmlinclude simpleVelocity.msg.html

(cl:defclass <simpleVelocity> (roslisp-msg-protocol:ros-message)
  ((speed
    :reader speed
    :initarg :speed
    :type cl:integer
    :initform 0)
   (direction
    :reader direction
    :initarg :direction
    :type cl:integer
    :initform 0))
)

(cl:defclass simpleVelocity (<simpleVelocity>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <simpleVelocity>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'simpleVelocity)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name GCRobotics-msg:<simpleVelocity> is deprecated: use GCRobotics-msg:simpleVelocity instead.")))

(cl:ensure-generic-function 'speed-val :lambda-list '(m))
(cl:defmethod speed-val ((m <simpleVelocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:speed-val is deprecated.  Use GCRobotics-msg:speed instead.")
  (speed m))

(cl:ensure-generic-function 'direction-val :lambda-list '(m))
(cl:defmethod direction-val ((m <simpleVelocity>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:direction-val is deprecated.  Use GCRobotics-msg:direction instead.")
  (direction m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <simpleVelocity>) ostream)
  "Serializes a message object of type '<simpleVelocity>"
  (cl:let* ((signed (cl:slot-value msg 'speed)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
  (cl:let* ((signed (cl:slot-value msg 'direction)) (unsigned (cl:if (cl:< signed 0) (cl:+ signed 4294967296) signed)))
    (cl:write-byte (cl:ldb (cl:byte 8 0) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) unsigned) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) unsigned) ostream)
    )
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <simpleVelocity>) istream)
  "Deserializes a message object of type '<simpleVelocity>"
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'speed) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
    (cl:let ((unsigned 0))
      (cl:setf (cl:ldb (cl:byte 8 0) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) unsigned) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) unsigned) (cl:read-byte istream))
      (cl:setf (cl:slot-value msg 'direction) (cl:if (cl:< unsigned 2147483648) unsigned (cl:- unsigned 4294967296))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<simpleVelocity>)))
  "Returns string type for a message object of type '<simpleVelocity>"
  "GCRobotics/simpleVelocity")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'simpleVelocity)))
  "Returns string type for a message object of type 'simpleVelocity"
  "GCRobotics/simpleVelocity")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<simpleVelocity>)))
  "Returns md5sum for a message object of type '<simpleVelocity>"
  "c132692a08c074e6ae3270af166b3df3")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'simpleVelocity)))
  "Returns md5sum for a message object of type 'simpleVelocity"
  "c132692a08c074e6ae3270af166b3df3")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<simpleVelocity>)))
  "Returns full string definition for message of type '<simpleVelocity>"
  (cl:format cl:nil "int32 speed~%int32 direction~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'simpleVelocity)))
  "Returns full string definition for message of type 'simpleVelocity"
  (cl:format cl:nil "int32 speed~%int32 direction~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <simpleVelocity>))
  (cl:+ 0
     4
     4
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <simpleVelocity>))
  "Converts a ROS message object to a list"
  (cl:list 'simpleVelocity
    (cl:cons ':speed (speed msg))
    (cl:cons ':direction (direction msg))
))
