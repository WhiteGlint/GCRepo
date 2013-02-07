; Auto-generated. Do not edit!


(cl:in-package GCRobotics-msg)


;//! \htmlinclude i2cData.msg.html

(cl:defclass <i2cData> (roslisp-msg-protocol:ros-message)
  ((address
    :reader address
    :initarg :address
    :type cl:fixnum
    :initform 0)
   (messageType
    :reader messageType
    :initarg :messageType
    :type cl:fixnum
    :initform 0)
   (messageData
    :reader messageData
    :initarg :messageData
    :type cl:fixnum
    :initform 0))
)

(cl:defclass i2cData (<i2cData>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <i2cData>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'i2cData)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name GCRobotics-msg:<i2cData> is deprecated: use GCRobotics-msg:i2cData instead.")))

(cl:ensure-generic-function 'address-val :lambda-list '(m))
(cl:defmethod address-val ((m <i2cData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:address-val is deprecated.  Use GCRobotics-msg:address instead.")
  (address m))

(cl:ensure-generic-function 'messageType-val :lambda-list '(m))
(cl:defmethod messageType-val ((m <i2cData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:messageType-val is deprecated.  Use GCRobotics-msg:messageType instead.")
  (messageType m))

(cl:ensure-generic-function 'messageData-val :lambda-list '(m))
(cl:defmethod messageData-val ((m <i2cData>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:messageData-val is deprecated.  Use GCRobotics-msg:messageData instead.")
  (messageData m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <i2cData>) ostream)
  "Serializes a message object of type '<i2cData>"
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'address)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'messageType)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'messageData)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <i2cData>) istream)
  "Deserializes a message object of type '<i2cData>"
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'address)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'messageType)) (cl:read-byte istream))
    (cl:setf (cl:ldb (cl:byte 8 0) (cl:slot-value msg 'messageData)) (cl:read-byte istream))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<i2cData>)))
  "Returns string type for a message object of type '<i2cData>"
  "GCRobotics/i2cData")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'i2cData)))
  "Returns string type for a message object of type 'i2cData"
  "GCRobotics/i2cData")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<i2cData>)))
  "Returns md5sum for a message object of type '<i2cData>"
  "b4597ca3548c510333f2e2d836183e5b")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'i2cData)))
  "Returns md5sum for a message object of type 'i2cData"
  "b4597ca3548c510333f2e2d836183e5b")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<i2cData>)))
  "Returns full string definition for message of type '<i2cData>"
  (cl:format cl:nil "uint8 address~%uint8 messageType~%uint8 messageData~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'i2cData)))
  "Returns full string definition for message of type 'i2cData"
  (cl:format cl:nil "uint8 address~%uint8 messageType~%uint8 messageData~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <i2cData>))
  (cl:+ 0
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <i2cData>))
  "Converts a ROS message object to a list"
  (cl:list 'i2cData
    (cl:cons ':address (address msg))
    (cl:cons ':messageType (messageType msg))
    (cl:cons ':messageData (messageData msg))
))
