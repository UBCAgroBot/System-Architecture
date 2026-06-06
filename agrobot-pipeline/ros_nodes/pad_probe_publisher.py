import rclpy
from rclpy.node import Node
import queue
from agrobot_msgs.msg import Detection

class PadProbePublisher(Node):
    def __init__(self, bbox_queue : queue.Queue):
        super().__init__("pad_probe_publisher")
        self.bbox_queue = bbox_queue
        
        # Publish to topic 
        self.pub = self.create_publisher(Detection, '/vision/detections', 10)

        # Poll queue every 0.05 seconds
        self.timer = self.create_timer(0.05, self.check_queue_for_data)

        # self.get_logger().info("[ROS2] BBoxPublisher ready. Publishing on /vision/detections")
        print("[ROS2] BBoxPublisher ready. Publishing on /vision/detections")

    def check_queue_for_data(self):
        while True:
            try:
                data = self.bbox_queue.get_nowait()
            except queue.Empty:
                break

            msg = Detection()
            msg.top = float(data['top'])
            msg.left = float(data['left'])
            msg.width = float(data['width'])
            msg.height = float(data['height'])

            self.pub.publish(msg)

            self.get_logger().info(
                f"\n\n------------\n"
                f"|[BBOX PUB]\n"
                f"|Top={round(data['top'], 2)}\n"
                f"|Left={round(data['left'], 2)}\n"
                f"|Width={round(data['width'], 2)}\n"
                f"|Height={round(data['height'], 2)}\n"
                f"------------"
            )


def start_bbox_publisher_thread(bbox_queue: queue.Queue):
    rclpy.init()
    node = PadProbePublisher(bbox_queue)
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()