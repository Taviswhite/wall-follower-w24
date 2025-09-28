#include <iostream>
#include <cmath>
#include <signal.h>
#include <mbot_bridge/robot.h>
#include <wall_follower/common/utils.h>

bool ctrl_c_pressed = false;

// Signal handler for Ctrl-C
void ctrlc(int)
{
    ctrl_c_pressed = true;
}

int main(int argc, const char* argv[])
{
    signal(SIGINT, ctrlc);   // Catch Ctrl-C
    signal(SIGTERM, ctrlc);

    // Initialize the robot
    mbot_bridge::MBot robot;

    // Lidar scan data
    std::vector<float> ranges;
    std::vector<float> thetas;

    // Wall-following parameters
    const float setpoint = 0.5;     // desired distance from wall (meters)
    const float Kp = 1.0;           // P-controller gain
    const float base_speed = 0.2;   // forward velocity (m/s)

    while (!ctrl_c_pressed) {
        // Get Lidar scan
        robot.readLidarScan(ranges, thetas);

        // Find index of nearest wall
        int idx = findMinDist(ranges);

        if (idx >= 0) {
            float distance = ranges[idx];   // distance to nearest wall

            // Compute error
            float error = distance - setpoint;

            // Simple P-control to adjust turning
            float wz = -Kp * error;    // negative to turn toward wall if too far

            // Drive forward with correction
            robot.drive(base_speed, 0.0, wz);
        } else {
            // No valid Lidar reading, just move forward
            robot.drive(base_speed, 0.0, 0.0);
        }
    }

    // Stop the robot
    robot.stop();
    std::cout << "Stopped wall follower." << std::endl;

    return 0;
}
