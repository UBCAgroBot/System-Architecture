import rclpy
from rclpy.node import Node
from agrobot_msgs.srv import NavPosition

class MockNavServer(Node):
    def __init__(self):
        super().__init__('mock_nav_server')
        # Create a server at '/nav/get_robot_position'
        self.srv = self.create_service(NavPosition, '/nav/get_robot_position', self.provide_mock_position)
        print("[Mock Nav Server] Online. Waiting for camera triggers...")

    def provide_mock_position(self, request, response):
        # Temporary send data, actual navigation data would be sent through these two variables
        mock_row = 2
        mock_distance = 2

        response.row = mock_row
        response.distance = mock_distance
        response.success = True
        response.message = "Data sent!"
        
        print(f"--> Received Request! Replying with Row: {response.row}, Dist: {response.distance}")
        return response

def main(args=None):
    rclpy.init(args=args)
    node = MockNavServer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()