#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using namespace std::chrono_literals;

class GenCosAndRand : public rclcpp::Node
{
public:
    GenCosAndRand(): Node("gen_node"), count_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Generating cosine and random numbers");
        pub_cos_ = this->create_publisher<std_msgs::msg::Float32>("cosine", 10);
        pub_rand_ = this->create_publisher<std_msgs::msg::Float32>("rand", 10);
        timer_ = this->create_wall_timer(50ms, std::bind(&GenCosAndRand::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto message_cos = std_msgs::msg::Float32();
        auto message_rand = std_msgs::msg::Float32();
        message_cos.data = cos(count_++ / 50.0) * 100;
        message_rand.data = rand() % 5;
        pub_cos_->publish(message_cos);
        pub_rand_->publish(message_rand);
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_cos_, pub_rand_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<GenCosAndRand>());
    rclcpp::shutdown();
    return 0;
}