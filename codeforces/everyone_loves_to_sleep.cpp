#include <bits/stdc++.h>
#define lli long long int

using namespace std;

void read_arr() {
    int size;
    cin >> size;

    int initial_hour, initial_minute;
    cin >> initial_hour >> initial_minute;
    int initial_time = initial_hour * 60 + initial_minute;

    int lowest_time = INT_MAX;
    int lowest_ever = INT_MAX;
    for (int i = 0; i < size; i++) {
        int hour, minute;
        cin >> hour >> minute;

        int time = hour * 60 + minute;
        if (time >= initial_time) {
            lowest_time = min(lowest_time, time);
        }

        lowest_ever = min(lowest_ever, time);
    }

    int time_sleeping;
    if (lowest_time == INT_MAX) {
        time_sleeping = 1440 - initial_time + lowest_ever;
    } else {
        time_sleeping = lowest_time - initial_time;
    }

    int hours_sleeping = time_sleeping / 60;
    int minutes_sleeping = time_sleeping % 60;

    cout << hours_sleeping << " " << minutes_sleeping << "\n";
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(0);

    int cases;
    cin >> cases;

    for (int i = 0; i < cases; i++) {
        read_arr();
    }
}