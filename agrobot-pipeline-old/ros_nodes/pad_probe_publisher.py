import rclpy
from rclpy.node import Node
from std_msgs.msg import String
import queue
import json

class PadProbePublisher(Node):
    def __init__(self, bbox_queue : queue.Queue):
        super().__init__("pad_probe_publisher")
        self.bbox_queue = bbox_queue
        
        # Publish to topic 
        self.pub = self.create_publisher(String, '/vision/detections', 10)

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

            msg = String()
            msg.data = json.dumps(data)
            self.pub.publish(msg)

            self.get_logger().info(
                f"[BBOX PUB] Top={data['top']}"
                f"Left={data['left']}"
                f"Width={data['width']}"
                f"Height={data['height']}"
            )


def start_bbox_publisher_thread(bbox_queue: queue.Queue):
    rclpy.init()
    node = PadProbePublisher(bbox_queue)
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()