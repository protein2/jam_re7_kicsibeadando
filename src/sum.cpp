#include <chrono>
#include <functional>
#include <memory>
#include <string>

#include "rclcpp/rclcpp.hpp"
#include "std_msgs/msg/float32.hpp"

using std::placeholders::_1;
using namespace std::chrono_literals;

class SumData : public rclcpp::Node
{
public:
    SumData(): Node("gen_node"), count_(0)
    {
        RCLCPP_INFO(this->get_logger(), "Summing numbers");
        pub_out_ = this->create_publisher<std_msgs::msg::Float32>("out", 10);
        sub_cosine_ = this->create_subscription<std_msgs::msg::Float32>("cosine", 10, std::bind(&SumData::cosine_callback, this, _1));
        sub_random_ = this->create_subscription<std_msgs::msg::Float32>("rand", 10, std::bind(&SumData::random_callback, this, _1));
        sub_input_ = this->create_subscription<std_msgs::msg::Float32>("in", 10, std::bind(&SumData::input_callback, this, _1));
        timer_ = this->create_wall_timer(50ms, std::bind(&SumData::timer_callback, this));
    }

private:
    void timer_callback()
    {
        auto message_sum = std_msgs::msg::Float32();
        message_sum.data = cosine_ + random_ + input_;
        pub_out_->publish(message_sum);
    }
    void cosine_callback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        cosine_ = msg->data;
    }
    void random_callback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        random_ = msg->data;
    }
    void input_callback(const std_msgs::msg::Float32::SharedPtr msg)
    {
        input_ = msg->data;
    }
    rclcpp::TimerBase::SharedPtr timer_;
    rclcpp::Publisher<std_msgs::msg::Float32>::SharedPtr pub_out_;
    rclcpp::Subscription<std_msgs::msg::Float32>::SharedPtr sub_cosine_, sub_random_, sub_input_;
    double cosine_, random_, input_;
    size_t count_;
};

int main(int argc, char *argv[])
{
    rclcpp::init(argc, argv);
    rclcpp::spin(std::make_shared<SumData>());
    rclcpp::shutdown();
    return 0;
}
