# Flow Matching
## Dinic
### Complexity
Though Dinic seems to have large complexity, the actual time comsumed is much less.

| Graph Type   | Time Complexity                             | Space Complexity |
| ------------ | ------------------------------------------- | ---------------- |
| General      | much less than O( EV^2 )                    | O( V + E )       |
| Bipartite    | much less than O( E sqrt(V) )               | O( V + E )       |
| Unit network | much less than O( E min(V^(3/2), sqrt(E)) ) | O( V + E )       |