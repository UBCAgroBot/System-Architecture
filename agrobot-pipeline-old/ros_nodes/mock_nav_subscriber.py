import rclpy
import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import json

class MockNavSubscriber(Node):
    def __init__(self):
        super().__init__('mock_nav_subscriber')
        self.sub = self.create_subscription(
            String,
            '/vision/detections',
            self.callback,
            10
        )
        print("[Mock Nav Subscriber] Listening on /vision/detections...")

    def callback(self, msg: String):
        data = json.loads(msg.data)
        print(f"[BBOX] Top={data['top']} | Left={data['left']} | Width={data['width']} | Height={data['height']}")

    
def main():
    rclpy.init()
    node = MockNavSubscriber()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()