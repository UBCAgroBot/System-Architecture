import rclpy
import rclpy
from rclpy.node import Node
from agrobot_msgs.msg import Detection

class MockNavSubscriber(Node):
    def __init__(self):
        super().__init__('mock_nav_subscriber')
        self.sub = self.create_subscription(
            Detection,
            '/vision/detections',
            self.callback,
            10
        )
        print("[Mock Nav Subscriber] Listening on /vision/detections...")

    def callback(self, msg: Detection):
        print(f"[BBOX] Top={round(msg.top, 2)} | Left={round(msg.left, 2)} | Width={round(msg.width, 2)} | Height={round(msg.height, 2)}")

    
def main():
    rclpy.init()
    node = MockNavSubscriber()
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()

if __name__ == '__main__':
    main()