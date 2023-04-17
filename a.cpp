#include <bits/stdc++.h>
#define pb push_back
#define INF INT_MAX
#define all(x) (x).begin(), (x).end()
#ifdef LOCAL
#define eprintf(...) { fprintf(stderr, __VA_ARGS__); fflush(stderr); }
#else
#define eprintf(...) 42
#endif

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> pi;
typedef map<int, int> mi;

double START, END;

vi lin, bin, fab;

vector<ll> fib;

int cnt = 5;

void initial (int a) {
    lin.clear();
    bin.clear();
    fab.clear();
    int x;
    for (int i = 0; i < a; i ++) {
        x = rand() % 65536 + 1;
        lin.pb(x);
        bin.pb(x);
        fab.pb(x);
    }
    sort(all(bin));
    sort(all(fab));
}

int linear_search (int x, int k) {
    START = clock();
    for (int i = 0; i < k; i ++) {
        if (lin[i] == x) return i;
    }
    return -1;
}

int binary_search (int x, int l, int r) {
    START = clock();
    int mid;
    while (l <= r) {
        mid = (l + r) >> 1;
        if (bin[mid] == x) return mid;
        if (bin[mid] > x) r = mid - 1;
        else l = mid + 1;
    }
    return -1;
}

int fibona_search (int x, int n) {
    int l = 0;
    int h = n - 1;
    int k = 0;
    int mid;
    while (h > fib[k] - 1) k ++;
    while (fab.size() < fib[k] - 1) {
        fab.pb(fab[h]);
    }
    START = clock();
    while (l <= h) {
        mid = l + fib[k - 1] - 1;
        if (x < fab[mid]) {
            h = mid - 1;
            k --;
        }else if (x > fab[mid]) {
            l = mid + 1;
            k -= 2;
        }else {
            if (mid <= h) return mid;
            else return h;
        }
    }
    return -1;
}

double avg_lin, avg_bin, avg_fab;


int main (int argc, const char* argv[]) {
    cin.tie(NULL);
    ios_base::sync_with_stdio(false);
    srand(time(NULL));
    fib.resize(100);
    fib[0] = 1;
    fib[1] = 1;
    for (int i = 2; i < 35; i ++) {
        fib[i] = fib[i - 2] + fib[i - 1];
    }
    for (int i = 10; i <= 1000; i += 10) {
        cout << "n: " << i << "->\n";
        initial(i);
        cout << "Linear search: \n";
        cnt = 5;
        while (cnt --) {
            int Find = rand() % 65536;
            cout << "  " << 5 - cnt << ": " << linear_search(Find, i) << "\n";
            END = clock();
            avg_lin += END - START;
        }
        cnt = 5;
        cout << "Binary search: \n";
        while (cnt --) {
            int Find = rand() % 65536;
            cout << "  " << 5 - cnt << ": " << binary_search(Find, 0, i - 1) << "\n";
            END = clock();
            avg_bin += END - START;
        }
        cnt = 5;
        cout << "Fibonacci search: \n";
        while (cnt --) {
            int Find = rand() % 65536;
            cout << "  " << 5 - cnt << ": " << fibona_search(Find, i) << "\n";
            END = clock();
            avg_fab += END - START;
        }
        avg_lin /= 5;
        avg_bin /= 5;
        avg_fab /= 5;
        cout << "Mean execution time Linear search: " << avg_lin / CLOCKS_PER_SEC << " s\n";
        cout << "Mean execution time Binary search: " << avg_bin / CLOCKS_PER_SEC << " s\n";
        cout << "Mean execution time Fibonacci search: " << avg_fab / CLOCKS_PER_SEC << " s\n";
    }
    return 0;
}