#include <iostream>
#include <cmath>

#include <mbot_bridge/robot.h>
#include <wall_follower/common/utils.h>


int main(int argc, const char *argv[])
{
    // Initialize the robot.
    mbot_bridge::MBot robot;

     // Drive in a square 3 times
    for (int lap = 0; lap < 3; lap++) {
        std::cout << "Starting square " << lap + 1 << std::endl;

        for (int side = 0; side < 4; side++) {
            // Drive forward
            robot.drive(0.2, 0.0, 0.0);   // move forward at 0.2 m/s
            sleepFor(2.0);                // drive for 2 seconds (adjust if needed)
            robot.stop();

            // Turn 90 degrees
            robot.drive(0.0, 0.0, 0.5);   // rotate at 0.5 rad/s
            sleepFor(3.14 / 2 / 0.5);     // turn 90 degrees = pi/2 radians
            robot.stop();
        }
    }

    // Stop the robot.
    std::cout << "Stopping the robot!!" << std::endl;
    robot.stop();
    return 0;
}
