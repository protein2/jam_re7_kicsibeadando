from launch import LaunchDescription
from launch_ros.actions import Node

def generate_launch_description():
    return LaunchDescription([
        Node(
            package='jam_re7_kicsibeadando',
            executable='gen_node',
        ),
        Node(
            package='jam_re7_kicsibeadando',
            executable='sum_node',
        ),
    ])