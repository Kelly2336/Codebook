// Find mininum path from src to dest.
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
    throw "Source and destination are not connected.";
}

// Find minuimum path from src to all the other vertices.
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