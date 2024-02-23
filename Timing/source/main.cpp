#include <iostream>
#include <chrono>
#include <vector>
#include <Eigen/Dense>

using Eigen::MatrixXd;
using Eigen::VectorXd;
using std::vector;
typedef std::chrono::steady_clock timingClock;

class Timer
{
public:
    void startTime()
    {
        start_time = timingClock::now();
    }
    void endTime()
    {
        end_time = timingClock::now();
    }
    double getDiffSeconds()
    {
        std::chrono::nanoseconds diff = end_time - start_time;
        double seconds = static_cast<double>(diff.count()) * 1e-9;
        // double seconds = static_cast<double>(diff.count());
        return seconds;
    }

private:
    std::chrono::time_point<timingClock> start_time;
    std::chrono::time_point<timingClock> end_time;
};

int main()
{
    Timer timer;
    timer.startTime();

    MatrixXd m = MatrixXd::Random(3, 3);
    m = (m + MatrixXd::Constant(3, 3, 1.2)) * 50;
    std::cout << "m =" << std::endl
              << m << std::endl;
    VectorXd v(3);
    v << 1, 2, 3;
    std::cout << "m * v =" << std::endl
              << m * v << std::endl;

    timer.endTime();

    std::cout << "Timer runs for: " << timer.getDiffSeconds() << " seconds." << std::endl;
    return 0;
}