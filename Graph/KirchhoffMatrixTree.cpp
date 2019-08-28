// D : degree-matrix
// A : adjacent-matrix
// 無向圖
    // (u,v)
    // A[u][v]++, A[v][u]++
    // D[u][u]++, D[v][v]++
    // G = D-A
    // abs(det(G去掉i-col和i-row))
    // 生成樹的數量
// 有向圖
    // A[u][v]++
    // D[v][v]++ (in-deg)
    // 以i為root的樹形圖數量
    // 所有節點都能到達root
