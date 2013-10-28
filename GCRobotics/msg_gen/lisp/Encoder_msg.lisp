; Auto-generated. Do not edit!


(cl:in-package GCRobotics-msg)


;//! \htmlinclude Encoder_msg.msg.html

(cl:defclass <Encoder_msg> (roslisp-msg-protocol:ros-message)
  ((encoder1
    :reader encoder1
    :initarg :encoder1
    :type cl:float
    :initform 0.0)
   (encoder2
    :reader encoder2
    :initarg :encoder2
    :type cl:float
    :initform 0.0)
   (encoder3
    :reader encoder3
    :initarg :encoder3
    :type cl:float
    :initform 0.0)
   (encoder4
    :reader encoder4
    :initarg :encoder4
    :type cl:float
    :initform 0.0)
   (direction1
    :reader direction1
    :initarg :direction1
    :type cl:boolean
    :initform cl:nil)
   (direction2
    :reader direction2
    :initarg :direction2
    :type cl:boolean
    :initform cl:nil)
   (direction3
    :reader direction3
    :initarg :direction3
    :type cl:boolean
    :initform cl:nil)
   (direction4
    :reader direction4
    :initarg :direction4
    :type cl:boolean
    :initform cl:nil))
)

(cl:defclass Encoder_msg (<Encoder_msg>)
  ())

(cl:defmethod cl:initialize-instance :after ((m <Encoder_msg>) cl:&rest args)
  (cl:declare (cl:ignorable args))
  (cl:unless (cl:typep m 'Encoder_msg)
    (roslisp-msg-protocol:msg-deprecation-warning "using old message class name GCRobotics-msg:<Encoder_msg> is deprecated: use GCRobotics-msg:Encoder_msg instead.")))

(cl:ensure-generic-function 'encoder1-val :lambda-list '(m))
(cl:defmethod encoder1-val ((m <Encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:encoder1-val is deprecated.  Use GCRobotics-msg:encoder1 instead.")
  (encoder1 m))

(cl:ensure-generic-function 'encoder2-val :lambda-list '(m))
(cl:defmethod encoder2-val ((m <Encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:encoder2-val is deprecated.  Use GCRobotics-msg:encoder2 instead.")
  (encoder2 m))

(cl:ensure-generic-function 'encoder3-val :lambda-list '(m))
(cl:defmethod encoder3-val ((m <Encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:encoder3-val is deprecated.  Use GCRobotics-msg:encoder3 instead.")
  (encoder3 m))

(cl:ensure-generic-function 'encoder4-val :lambda-list '(m))
(cl:defmethod encoder4-val ((m <Encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:encoder4-val is deprecated.  Use GCRobotics-msg:encoder4 instead.")
  (encoder4 m))

(cl:ensure-generic-function 'direction1-val :lambda-list '(m))
(cl:defmethod direction1-val ((m <Encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:direction1-val is deprecated.  Use GCRobotics-msg:direction1 instead.")
  (direction1 m))

(cl:ensure-generic-function 'direction2-val :lambda-list '(m))
(cl:defmethod direction2-val ((m <Encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:direction2-val is deprecated.  Use GCRobotics-msg:direction2 instead.")
  (direction2 m))

(cl:ensure-generic-function 'direction3-val :lambda-list '(m))
(cl:defmethod direction3-val ((m <Encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:direction3-val is deprecated.  Use GCRobotics-msg:direction3 instead.")
  (direction3 m))

(cl:ensure-generic-function 'direction4-val :lambda-list '(m))
(cl:defmethod direction4-val ((m <Encoder_msg>))
  (roslisp-msg-protocol:msg-deprecation-warning "Using old-style slot reader GCRobotics-msg:direction4-val is deprecated.  Use GCRobotics-msg:direction4 instead.")
  (direction4 m))
(cl:defmethod roslisp-msg-protocol:serialize ((msg <Encoder_msg>) ostream)
  "Serializes a message object of type '<Encoder_msg>"
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'encoder1))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'encoder2))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'encoder3))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:let ((bits (roslisp-utils:encode-double-float-bits (cl:slot-value msg 'encoder4))))
    (cl:write-byte (cl:ldb (cl:byte 8 0) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 8) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 16) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 24) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 32) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 40) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 48) bits) ostream)
    (cl:write-byte (cl:ldb (cl:byte 8 56) bits) ostream))
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'direction1) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'direction2) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'direction3) 1 0)) ostream)
  (cl:write-byte (cl:ldb (cl:byte 8 0) (cl:if (cl:slot-value msg 'direction4) 1 0)) ostream)
)
(cl:defmethod roslisp-msg-protocol:deserialize ((msg <Encoder_msg>) istream)
  "Deserializes a message object of type '<Encoder_msg>"
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder1) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder2) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder3) (roslisp-utils:decode-double-float-bits bits)))
    (cl:let ((bits 0))
      (cl:setf (cl:ldb (cl:byte 8 0) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 8) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 16) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 24) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 32) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 40) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 48) bits) (cl:read-byte istream))
      (cl:setf (cl:ldb (cl:byte 8 56) bits) (cl:read-byte istream))
    (cl:setf (cl:slot-value msg 'encoder4) (roslisp-utils:decode-double-float-bits bits)))
    (cl:setf (cl:slot-value msg 'direction1) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'direction2) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'direction3) (cl:not (cl:zerop (cl:read-byte istream))))
    (cl:setf (cl:slot-value msg 'direction4) (cl:not (cl:zerop (cl:read-byte istream))))
  msg
)
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql '<Encoder_msg>)))
  "Returns string type for a message object of type '<Encoder_msg>"
  "GCRobotics/Encoder_msg")
(cl:defmethod roslisp-msg-protocol:ros-datatype ((msg (cl:eql 'Encoder_msg)))
  "Returns string type for a message object of type 'Encoder_msg"
  "GCRobotics/Encoder_msg")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql '<Encoder_msg>)))
  "Returns md5sum for a message object of type '<Encoder_msg>"
  "1f3c9338c8adf9eef290f5ae7c5d32ec")
(cl:defmethod roslisp-msg-protocol:md5sum ((type (cl:eql 'Encoder_msg)))
  "Returns md5sum for a message object of type 'Encoder_msg"
  "1f3c9338c8adf9eef290f5ae7c5d32ec")
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql '<Encoder_msg>)))
  "Returns full string definition for message of type '<Encoder_msg>"
  (cl:format cl:nil "float64 encoder1~%float64 encoder2~%float64 encoder3~%float64 encoder4~%~%bool direction1~%bool direction2~%bool direction3~%bool direction4~%~%~%"))
(cl:defmethod roslisp-msg-protocol:message-definition ((type (cl:eql 'Encoder_msg)))
  "Returns full string definition for message of type 'Encoder_msg"
  (cl:format cl:nil "float64 encoder1~%float64 encoder2~%float64 encoder3~%float64 encoder4~%~%bool direction1~%bool direction2~%bool direction3~%bool direction4~%~%~%"))
(cl:defmethod roslisp-msg-protocol:serialization-length ((msg <Encoder_msg>))
  (cl:+ 0
     8
     8
     8
     8
     1
     1
     1
     1
))
(cl:defmethod roslisp-msg-protocol:ros-message-to-list ((msg <Encoder_msg>))
  "Converts a ROS message object to a list"
  (cl:list 'Encoder_msg
    (cl:cons ':encoder1 (encoder1 msg))
    (cl:cons ':encoder2 (encoder2 msg))
    (cl:cons ':encoder3 (encoder3 msg))
    (cl:cons ':encoder4 (encoder4 msg))
    (cl:cons ':direction1 (direction1 msg))
    (cl:cons ':direction2 (direction2 msg))
    (cl:cons ':direction3 (direction3 msg))
    (cl:cons ':direction4 (direction4 msg))
))
