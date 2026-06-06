#[cfg(feature = "serde")]
use serde::{Deserialize, Serialize};



// Corresponds to agrobot_msgs__msg__Detection

// This struct is not documented.
#[allow(missing_docs)]

#[cfg_attr(feature = "serde", derive(Deserialize, Serialize))]
#[derive(Clone, Debug, PartialEq, PartialOrd)]
pub struct Detection {

    // This member is not documented.
    #[allow(missing_docs)]
    pub top: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub left: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub width: f32,


    // This member is not documented.
    #[allow(missing_docs)]
    pub height: f32,

}



impl Default for Detection {
  fn default() -> Self {
    <Self as rosidl_runtime_rs::Message>::from_rmw_message(super::msg::rmw::Detection::default())
  }
}

impl rosidl_runtime_rs::Message for Detection {
  type RmwMsg = super::msg::rmw::Detection;

  fn into_rmw_message(msg_cow: std::borrow::Cow<'_, Self>) -> std::borrow::Cow<'_, Self::RmwMsg> {
    match msg_cow {
      std::borrow::Cow::Owned(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
        top: msg.top,
        left: msg.left,
        width: msg.width,
        height: msg.height,
      }),
      std::borrow::Cow::Borrowed(msg) => std::borrow::Cow::Owned(Self::RmwMsg {
      top: msg.top,
      left: msg.left,
      width: msg.width,
      height: msg.height,
      })
    }
  }

  fn from_rmw_message(msg: Self::RmwMsg) -> Self {
    Self {
      top: msg.top,
      left: msg.left,
      width: msg.width,
      height: msg.height,
    }
  }
}


