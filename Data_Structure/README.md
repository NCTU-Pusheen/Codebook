# Data Structure

## BIT / 線段樹
### 操作支援
可單點修改必可單點增值；可單點增值必可單點修改。

| class                  | 設值範圍 | 加值範圍 | 查詢區間和 | 查詢區間極值 | 查詢區間特殊值 <br/> (lcm, gcd, etc) |
| ---------------------- | :------: | :------: | :--------: | :----------: | :--------------------------------: |
| BIT                    |   單點   |   單點   |     可     |     不可     |                不可                |
| RangeUpdateBIT         |   單點   |   區間   |     可     |     不可     |                不可                |
| BIT2D                  |   單點   |   單點   |   可(2D)   |     不可     |                不可                |
| SegmentTree            |   單點   |   單點   |     可     |      可      |                 可                 |
| RangeUpdateSegmentTree |   區間   |   區間   |     可     |      可      |                不可                |
| SparseTable            |   不可   |   不可   |    不可    |      可      |                不可                |

### 複雜度
* BIT2D = O((A+Q)*log(A)) ，A 為矩形面積。
* RangeUpdate = small-o(N*log(Q))。
* 其餘 O(Q*log(N))

### 結論
* 初始化後不修改，只求極值 > SparseTable
* 只有區間求和，優先用 BIT
  * 1D
    * 只有單點修改或增值 > BIT
    * 只有區間增值 > RangeUpdateBIT
    * 涉及區間設值必須用 RangeUpdateSegmentTree
  * 2D
    * 只有單點修改或增值 > BIT2D
    * 矩陣面積若夠小，可以開 BIT 或線段樹陣列
    * 否則沒救了
* 其餘才用線段樹
  * 只有單點修改或增值 > SegmentTree
  * 其餘 > RangeUpdateBIT
  * 這份模板沒有二維線段樹，但可以用一維自己刻
