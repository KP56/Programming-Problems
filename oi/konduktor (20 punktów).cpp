#include <bits/stdc++.h>

using namespace std;

#define int long long int

int solve(vector<pair<int,int>> tracks) {
    // procedura zachłanna polegająca na obserwacji, że zawsze opłaca się brać jak najdalsze (wynika z programowania dynamicznego)

    int result = 0;
    int last = -1;
    for (int i = 0; i < tracks.size(); i++) {
        if (tracks[i].first > last) {
            result++;
            last = tracks[i].second-1;
        }
    }

    return result;
}

int min_val = INT_MAX;
int combinations = 0;
void generate_bruteforce(int m, vector<pair<int,int>> &tracks, vector<bool> &current) {
    if (current.size() == m) {
        bool found_for_all = true;
        for (int i = 0; i < tracks.size(); i++) {
            bool found = false;
            for (int j = tracks[i].first; j < tracks[i].second; j++) {
                if (current[j]) {
                    found = true;
                    break;
                }
            }

            if (!found) {
                found_for_all = false;
                break;
            }
        }

        if (found_for_all) {
            int val = 0;
            for (bool b : current) {
                val += b;
            }

            if (val < min_val) {
                combinations = 1;
            } else if (val == min_val) {
                combinations++;
            }

            min_val = min(val,min_val);
        }

        return;
    }

    vector<bool> cp = current;
    cp.push_back(false);

    generate_bruteforce(m,tracks,cp);

    vector<bool> cp2 = current;
    cp2.push_back(true);

    generate_bruteforce(m,tracks,cp2);
}

int minimum_bruteforce(int m, vector<pair<int,int>> tracks) {
    vector<bool> current;
    generate_bruteforce(m,tracks,current);

    return min_val;
}

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    srand(time(NULL));

    int z;
    cin >> z;

    for (int i = 0; i < z; i++) {
        min_val = INT_MAX;
        combinations = 0;

        //int m = rand() % 5 + 2,n = rand() % 5 + 1;
        int m,n;
        cin >> m >> n;

        vector<pair<int,int>> tracks; 
        for (int j = 0; j < n; j++) {
            //int a = rand() % (m-1) + 1,b = rand() % (m-a) + a + 1;
            int a,b;
            cin >> a >> b;

            a--;
            b--;

            tracks.push_back({b,a});
        }

        sort(tracks.begin(),tracks.end());

        vector<pair<int,int>> actual_tracks;
        for (auto i : tracks) {
            actual_tracks.push_back({i.second,i.first});
        }

        int res = solve(actual_tracks);
        //int brute_res = minimum_bruteforce(m,actual_tracks);

        /*if (res != brute_res) {
            int test = 0;
        }*/

        cout << res << " " << combinations << "\n";
    }
}
