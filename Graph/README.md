# Graph
## LCA
三種 LCA 都可以查詢 lca 和兩點最短距離。各有優缺點，不存在絕對的可替代性。

| class                         | 時間複雜度     | 空間複雜度 |  離線限制  |
| ----------------------------- | -------------- | ---------- | :--------: |
| SsadpTarjan                   | O(N + Q) 最快      | O(N ^ 2) 很差   | 不需要離線 |
| OfflineTarjan                 | O(N + Q) 最快      | O(N + Q) 最好  |  必須離線  |
| SparseTableTarjan (威達常用) | O(N + Q log N) 普通 | O(N log N) 普通 | 不需要離線 |
