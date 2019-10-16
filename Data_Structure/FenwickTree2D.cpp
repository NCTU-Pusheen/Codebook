/**
 * Support single element increment
 * 			and range sum query in 2D.
 * Time Complexity: O(RlogR * ClogC)
 * Space Complexity: O(RC)
 */
class BIT2D {
   private:
    int r, c;
    vector<vector<ll>> a;

    ll sum(int x, int y) {
        ll r = 0;
        for (int i = x; i; i -= (i & -i))
        	for (int j = y; j; j -= (j & -j))
        		r += a[i][j];
        return r;
    }

   public:
    // Constructs a 2D BIT with all value initialized to 0;
	// r/c is count of rows/column of matrix
    BIT2D(int r, int c) : r(r), c(c) {
		a.assign(r + 1, vector<ll>(c + 1, 0)); }
    // Increases element at coordinates (x, y) by value v, 
	// where x in [1, r] and y in [1, c]
    void add(int x, int y, ll v) {
    	for (int i = x; i <= r; i += (i & -i))
    		for (int j = y; j <= c; j += (j & -j))
    			a[i][j] += v;
    }
    // Queries sum of matrix
	// from (x0, y0) (inclusive) to(x1, y1) (inclusive) 
	// where x in [1, r] and y in [1, c]
	ll sum(int x0, int yo, int x1, int yl) {
		if (x0 > x1)
			swap(x0, x1);
		if (yo > yl)
			swap(yo, yl);
		return sum(x1, yl) - sum(x0 - 1, yl)
			 - sum(x1, yo - 1) + sum(x0 - 1, yo - 1);}
}; 
