// Queries mininum path from src to dest in a graph where src and dest are connected.
int dijkstra(int src, int dest, const vector<vector<pii>>& edge) {
    const int N = edge.size();
    bool vis[N] = {0};
    // A comparator may be required.
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (!q.empty()) {
        int v = q.top().second;
        int d = q.top().first;
        q.pop();
        if (v == dest) return d;
        if (vis[v]) continue;
        vis[v] = true;
        for (auto& e : edge[v]) {
            if (!vis[e.second]) {
                // Fit the comparator
                q.emplace(d + e.first, e.second);
            }
        }
    }
    throw "src and dest are not connected.";
}

// Queries minuimum path from src to all the other vertices in a graph where all vertices are connected.
vector<int> dijkstra(int src, const vector<vector<pii>>& edge) {
    const int N = edge.size();
    vector<int> mindist(N, -1);
    int vis = 0;
    // A comparator may be required.
    priority_queue<pii, vector<pii>, greater<pii>> q;
    q.emplace(0, src);
    while (vis < N) {
        if (q.empty()) throw "Not all vertices connected.";
        int v = q.top().second;
        int d = q.top().first;
        q.pop();
        if (mindist[v] != -1) continue;
        mindist[v] = d;
        vis++;
        for (auto& e : edge[v]) {
            if (mindist[e.second] == -1) {
                // Fit the comparator
                q.emplace(d + e.first, e.second);
            }
        }
    }
    return mindist;
}