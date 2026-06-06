import rclpy
from rclpy.node import Node
from std_srvs.srv import Trigger

class MockNavServer(Node):
    def __init__(self):
        super().__init__('mock_nav_server')
        # Create a server at '/nav/get_robot_position'
        self.srv = self.create_service(Trigger, '/nav/get_robot_position', self.provide_mock_position)
        print("[Mock Nav Server] Online. Waiting for camera triggers...")

    def provide_mock_position(self, request, response):
        """This runs every time your camera sees a new weed."""
        # Temporary send data, actual navigation data would be sent through these two variables
        mock_row = 2
        mock_distance = 2

        response.success = True
        response.message = f"{mock_row},{mock_distance}"
        
        print(f"--> Received Request! Replying with Row: {mock_row}, Dist: {mock_distance}")
        return response

def main(args=None):
    rclpy.init(args=args)
    node = MockNavServer()
    rclpy.spin(node)
    rclpy.shutdown()

if __name__ == '__main__':
    main()