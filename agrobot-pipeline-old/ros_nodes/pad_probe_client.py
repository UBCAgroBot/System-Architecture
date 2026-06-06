import rclpy
from rclpy.node import Node
from std_srvs.srv import Trigger
import queue
import csv

class PadProbeClient(Node):
    def __init__(self, trigger_queue : queue.Queue):
        super().__init__("pad_probe_client")
        self.trigger_queue = trigger_queue
        self.nav_server_available = False

        ##### Connect to Navigation team's server node #####
        self.cli = self.create_client(Trigger, '/nav/get_robot_position')

        # Check server availability in the background, non-blocking
        self.availability_timer = self.create_timer(2.0, self._check_server_availability)

        ##### Set up CSV file logging #####
        self.csv_file = open('detections.csv', mode='a', newline='')
        self.csv_writer = csv.writer(self.csv_file)

        if self.csv_file.tell() == 0:
            self.csv_writer.writerow(["RowNumber", "Distance"])
            self.csv_file.flush()
        
        ##### Poll queue every 0.05 seconds #####
        self.timer = self.create_timer(0.05, self.check_queue_for_triggers)

        # self.get_logger().info("[ROS 2] Logger Client Ready. Waiting for detections...")
        print("\n[ROS 2] Logger Client Ready. Waiting for detections...")

    def _check_server_availability(self):
        was_available = self.nav_server_available
        self.nav_server_available = self.cli.service_is_ready()

        if self.nav_server_available and not was_available:
            self.get_logger().info("Nav server is ONLINE")
        elif not self.nav_server_available and was_available:
            self.get_logger().info("Nav server went OFFLINE")

    def check_queue_for_triggers(self):
        try:
            _ = self.trigger_queue.get_nowait()
            self.send_nav_request()
        except queue.Empty:
            pass

    def send_nav_request(self):
        if not self.cli.wait_for_service(timeout_sec=1.0):
            self.get_logger().warn("Nav server is offline! Dropping log request")
            return
        
        # Send empty trigger request
        req = Trigger.Request()
        future = self.cli.call_async(req)

        # When server replies, run callback function
        future.add_done_callback(self.write_to_csv_callback)

    def write_to_csv_callback(self, future):
        try:
            response = future.result()
            
            # Unpack the "4,12.5" string from the mock server
            data_string = response.message.split(',')
            row = data_string[0]
            dist = data_string[1]

            # Write it to the CSV!
            self.csv_writer.writerow([row, dist])
            self.csv_file.flush() # Force save to hard drive immediately
            
            print(f">> [CSV LOG] Row: {row} | Distance: {dist}")
            
        except Exception as e:
            self.get_logger().error(f"Service call failed: {e}")


def start_client_thread(trigger_queue: queue.Queue):
    rclpy.init()
    node = PadProbeClient(trigger_queue)
    rclpy.spin(node)
    node.destroy_node()
    rclpy.shutdown()