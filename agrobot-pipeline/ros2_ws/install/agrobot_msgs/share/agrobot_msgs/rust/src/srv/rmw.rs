#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



#[link(name = "agrobot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agrobot_msgs__srv__NavPosition_Request() -> *const std::ffi::c_void;
}

#[link(name = "agrobot_msgs__rosidl_generator_c")]
extern "C" {
    fn agrobot_msgs__srv__NavPosition_Request__init(msg: *mut NavPosition_Request) -> bool;
    fn agrobot_msgs__srv__NavPosition_Request__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavPosition_Request>, size: usize) -> bool;
    fn agrobot_msgs__srv__NavPosition_Request__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavPosition_Request>);
    fn agrobot_msgs__srv__NavPosition_Request__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavPosition_Request>, out_seq: *mut rosidl_runtime_rs::Sequence<NavPosition_Request>) -> bool;
}

// Corresponds to agrobot_msgs__srv__NavPosition_Request
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavPosition_Request {

    // This member is not documented.
    #[allow(missing_docs)]
    pub structure_needs_at_least_one_member: u8,

}



impl Default for NavPosition_Request {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agrobot_msgs__srv__NavPosition_Request__init(&mut msg as *mut _) {
        panic!("Call to agrobot_msgs__srv__NavPosition_Request__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavPosition_Request {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agrobot_msgs__srv__NavPosition_Request__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agrobot_msgs__srv__NavPosition_Request__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agrobot_msgs__srv__NavPosition_Request__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavPosition_Request {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavPosition_Request where Self: Sized {
  const TYPE_NAME: &'static str = "agrobot_msgs/srv/NavPosition_Request";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agrobot_msgs__srv__NavPosition_Request() }
  }
}


#[link(name = "agrobot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_message_type_support_handle__agrobot_msgs__srv__NavPosition_Response() -> *const std::ffi::c_void;
}

#[link(name = "agrobot_msgs__rosidl_generator_c")]
extern "C" {
    fn agrobot_msgs__srv__NavPosition_Response__init(msg: *mut NavPosition_Response) -> bool;
    fn agrobot_msgs__srv__NavPosition_Response__Sequence__init(seq: *mut rosidl_runtime_rs::Sequence<NavPosition_Response>, size: usize) -> bool;
    fn agrobot_msgs__srv__NavPosition_Response__Sequence__fini(seq: *mut rosidl_runtime_rs::Sequence<NavPosition_Response>);
    fn agrobot_msgs__srv__NavPosition_Response__Sequence__copy(in_seq: &rosidl_runtime_rs::Sequence<NavPosition_Response>, out_seq: *mut rosidl_runtime_rs::Sequence<NavPosition_Response>) -> bool;
}

// Corresponds to agrobot_msgs__srv__NavPosition_Response
#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]


// This struct is not documented.
#[allow(missing_docs)]

#[allow(non_camel_case_types)]
#[repr(C)]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct NavPosition_Response {

    // This member is not documented.
    #[allow(missing_docs)]
    pub row: i32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub distance: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub success: bool,


    // This member is not documented.
    #[allow(missing_docs)]
    pub message: rosidl_runtime_rs::String,

}



impl Default for NavPosition_Response {
  fn default() -> Self {
    unsafe {
      let mut msg = std::mem::zeroed();
      if !agrobot_msgs__srv__NavPosition_Response__init(&mut msg as *mut _) {
        panic!("Call to agrobot_msgs__srv__NavPosition_Response__init() failed");
      }
      msg
    }
  }
}

impl rosidl_runtime_rs::SequenceAlloc for NavPosition_Response {
  fn sequence_init(seq: &mut rosidl_runtime_rs::Sequence<Self>, size: usize) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agrobot_msgs__srv__NavPosition_Response__Sequence__init(seq as *mut _, size) }
  }
  fn sequence_fini(seq: &mut rosidl_runtime_rs::Sequence<Self>) {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agrobot_msgs__srv__NavPosition_Response__Sequence__fini(seq as *mut _) }
  }
  fn sequence_copy(in_seq: &rosidl_runtime_rs::Sequence<Self>, out_seq: &mut rosidl_runtime_rs::Sequence<Self>) -> bool {
    // SAFETY: This is safe since the pointer is guaranteed to be valid/initialized.
    unsafe { agrobot_msgs__srv__NavPosition_Response__Sequence__copy(in_seq, out_seq as *mut _) }
  }
}

impl rosidl_runtime_rs::Message for NavPosition_Response {
  type RmwMsg = Self;
  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> { msg_cow }
  fn from_rmw_message(msg: Self::RmwMsg) -> Self { msg }
}

impl rosidl_runtime_rs::RmwMessage for NavPosition_Response where Self: Sized {
  const TYPE_NAME: &'static str = "agrobot_msgs/srv/NavPosition_Response";
  fn get_type_support() -> *const std::ffi::c_void {
    // SAFETY: No preconditions for this function.
    unsafe { rosidl_typesupport_c__get_message_type_support_handle__agrobot_msgs__srv__NavPosition_Response() }
  }
}






#[link(name = "agrobot_msgs__rosidl_typesupport_c")]
extern "C" {
    fn rosidl_typesupport_c__get_service_type_support_handle__agrobot_msgs__srv__NavPosition() -> *const std::ffi::c_void;
}

// Corresponds to agrobot_msgs__srv__NavPosition
#[allow(missing_docs, non_camel_case_types)]
pub struct NavPosition;

impl rosidl_runtime_rs::Service for NavPosition {
    type Request = NavPosition_Request;
    type Response = NavPosition_Response;

    fn get_type_support() -> *const std::ffi::c_void {
        // SAFETY: No preconditions for this function.
        unsafe { rosidl_typesupport_c__get_service_type_support_handle__agrobot_msgs__srv__NavPosition() }
    }
}


