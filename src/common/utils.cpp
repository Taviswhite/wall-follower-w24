#include <wall_follower/common/utils.h>
#include <limits>   // for std::numeric_limits

std::vector<float> crossProduct(const std::vector<float>& v1, const std::vector<float>& v2)
{
    std::vector<float> res(3, 0.0f);  // initialize with 3 zeros

    // Make sure both vectors have 3 elements
    if (v1.size() == 3 && v2.size() == 3) {
        // Standard 3D cross product formula
        res[0] = v1[1] * v2[2] - v1[2] * v2[1];  // x
        res[1] = v1[2] * v2[0] - v1[0] * v2[2];  // y
        res[2] = v1[0] * v2[1] - v1[1] * v2[0];  // z
    }

    return res;
}

int findMinDist(const std::vector<float>& ranges)
{
    int min_idx = -1;  // -1 means "not found"
    float min_val = std::numeric_limits<float>::max();

    for (size_t i = 0; i < ranges.size(); i++) {
        float dist = ranges[i];
        // Skip invalid rays (distance = 0)
        if (dist > 0 && dist < min_val) {
            min_val = dist;
            min_idx = static_cast<int>(i);
        }
    }

    return min_idx;
}
