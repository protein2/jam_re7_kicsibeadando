# `jam_re7_kicsibeadando` package
ROS 2 C++ package.  [![Static Badge](https://img.shields.io/badge/ROS_2-Humble-34aec5)](https://docs.ros.org/en/humble/)
## Packages and build

It is assumed that the workspace is `~/ros2_ws/`.

### Clone the packages
``` r
cd ~/ros2_ws/src
```
``` r
git clone https://github.com/protein2/jam_re7_kicsibeadando
```

### Build ROS 2 packages
``` r
cd ~/ros2_ws
```
``` r
colcon build --packages-select jam_re7_kicsibeadando --symlink-install
```

<details>
<summary> Don't forget to source before ROS commands.</summary>

``` bash
source ~/ros2_ws/install/setup.bash
```
</details>

``` r
ros2 launch jam_re7_kicsibeadando launch_example1.launch.py
```
``` r
ros2 run jam_re7_kicsibeadando gen_node 
```

``` r
ros2 run jam_re7_kicsibeadando sum_node 
```

## Graph

``` mermaid
graph LR;

gen([ /gen_node]):::red --> sine
gen --> rand[ /rand<br/>std_msgs/Float32]:::light 
sine[ /sine<br/>std_msgs/Float32]:::light --> sum([ /sum_node]):::red
sum --> out[ /out<br/>std_msgs/Float32]:::light 
rand --> sum
in[ /in<br/>std_msgs/Float32]:::light --> sum

classDef light fill:#34aec5,stroke:#152742,stroke-width:2px,color:#152742  
classDef dark fill:#152742,stroke:#34aec5,stroke-width:2px,color:#34aec5
classDef white fill:#ffffff,stroke:#152742,stroke-width:2px,color:#152742
classDef red fill:#ef4638,stroke:#152742,stroke-width:2px,color:#fff
```

![](/home/ajr/ros2_ws/src/jam_re7_kicsibeadando/img/ajr_foxglove_image.png)