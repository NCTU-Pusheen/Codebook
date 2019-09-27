# Graph
## LCA
All three LCA Tarjan classes supports querying least commom ancestor and minimal distance from any node to one another, while time and space complexities vary.

| class | Time complexity | Space complexity | Offline required |
| --- | --- | --- | :---: |
| SsadpTarjan                          | O(N + Q)       | O(N ^ 2)   | No  |
| OfflineTarjan                        | O(N + Q)       | O(N + Q)   | Yes |
| SparseTableTarjan (Ud commonly used) | O(N + Q log N) | O(N log N) | No  |