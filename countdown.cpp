#include <chrono>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <fstream>
#include <thread>

using namespace std::chrono_literals;

int main(int argc, char** argv) {
    int tgt_hour = 20;
    int tgt_minute = 0;
    if (argc >= 2) {
        tgt_hour = std::atoi(argv[1]);
    }
    if (argc >= 3) {
        tgt_minute = std::atoi(argv[2]);
    }

    while (1) {
        auto t = std::time(nullptr);
        auto* tm = std::localtime(&t);

        auto day_seconds = 3600 * (tm->tm_hour + 0) + 60 * tm->tm_min + tm->tm_sec;
        auto target_seconds = tgt_hour * 3600 + tgt_minute * 60;

        auto seconds_left = target_seconds - day_seconds;
        bool past_due = seconds_left < 0;
        seconds_left = std::abs(seconds_left);


        auto hours = seconds_left / 3600;
        seconds_left %= 3600;
        auto minutes = seconds_left / 60;
        auto seconds = seconds_left % 60;

        std::fstream fs("countdown_8pm.txt", std::fstream::out | std::fstream::trunc);
        fs << (past_due ? "-" : "")
            << std::setw(2) << std::setfill('0') << hours << ":"
            << std::setw(2) << std::setfill('0') << minutes << ":"
            << std::setw(2) << std::setfill('0') << seconds << std::endl;
        fs.close();
        std::this_thread::sleep_for(1s);
    }
}
