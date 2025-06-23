#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

const long long INF = -1e18; 

void solve() {
    int n;
    cin >> n;

    vector<string> words(n);
    for (int i = 0; i < n; ++i) {
        cin >> words[i];
    }

    vector<vector<long long>> prev_dp(26, vector<long long>(26, INF));
    vector<vector<long long>> current_dp(26, vector<long long>(26, INF));

    char f0 = words[0][0];
    char l0 = words[0][words[0].length() - 1];
    prev_dp[f0 - 'a'][l0 - 'a'] = words[0].length();

    for (int i = 1; i < n; ++i) {
        for (int r = 0; r < 26; ++r) {
            fill(current_dp[r].begin(), current_dp[r].end(), INF);
        }

        char f_curr = words[i][0];
        char l_curr = words[i][words[i].length() - 1];
        long long len_curr = words[i].length();

        for (int prev_first_idx = 0; prev_first_idx < 26; ++prev_first_idx) {
            for (int prev_last_idx = 0; prev_last_idx < 26; ++prev_last_idx) {
                if (prev_dp[prev_first_idx][prev_last_idx] == INF) {
                    continue;
                }

                long long current_combined_len = prev_dp[prev_first_idx][prev_last_idx];
                char prev_first_char = (char)('a' + prev_first_idx);
                char prev_last_char = (char)('a' + prev_last_idx);

                long long new_len_after = current_combined_len + len_curr;
                if (prev_last_char == f_curr) {
                    new_len_after--;
                }
                current_dp[prev_first_idx][l_curr - 'a'] = max(current_dp[prev_first_idx][l_curr - 'a'], new_len_after);

                long long new_len_before = current_combined_len + len_curr;
                if (l_curr == prev_first_char) {
                    new_len_before--;
                }
                current_dp[f_curr - 'a'][prev_last_idx] = max(current_dp[f_curr - 'a'][prev_last_idx], new_len_before);
            }
        }
        prev_dp = current_dp;
    }

    long long max_score = 0;
    for (int i = 0; i < 26; ++i) {
        for (int j = 0; j < 26; ++j) {
            max_score = max(max_score, prev_dp[i][j]);
        }
    }
    cout << max_score << endl;
}

int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);

    solve();

    return 0;
}