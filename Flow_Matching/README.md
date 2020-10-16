# Flow Matching
## Dinic
### Complexity
Though Dinic seems to have large complexity, the actual time comsumed is much less.

| Graph Type   | Time Complexity                             | Space Complexity |
| ------------ | ------------------------------------------- | ---------------- |
| General      | much less than O( EV^2 )                    | O( V + E )       |
| Bipartite    | much less than O( E sqrt(V) )               | O( V + E )       |
| Unit network | much less than O( E min(V^(3/2), sqrt(E)) ) | O( V + E )       |

## 二分圖匹配問題

最大匹配數：給定二分圖 G，在 G 的子圖 M 中，M 的任兩條邊都沒有公共節點，則 M 成為此二分圖的匹配，|EM| 最大的匹配則成為最大匹配。
最小點覆蓋：在 VG 中選取最少的點，形成子集合 V，使 E 為所有與 V 中的點 incident 的邊形成的集合。
最大獨立集：在 VG 中選取最多的點，形成子集合 V，且任兩個 V 中的 vertices 都不相鄰。

Konig 定理：對於任意二分圖，滿足以下兩個條件
1. 最大匹配數 = 最小點覆蓋的頂點數
2. 最大獨立集之頂點數 = 總頂點數 - 最大匹配數
