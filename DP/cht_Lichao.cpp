
//reference from https://github.com/justiceHui/AlgorithmImplement/blob/master/DataStructure/LiChaoTree.cpp
struct Line {
    LL a, b;
    LL get(LL x)
    {
        return a * x + b;
    }
};

struct Node
{
    int l, r;
    LL s, e;
    Line line;
};

struct Li_Chao {
	vector<Node> tree;

	void init(LL s, LL e) {
		tree.push_back({ -1, -1, s, e, { 0, LNF } });
	}

	void update(int node, Line v) {
		LL s = tree[node].s, e = tree[node].e;
		LL m = s + e >> 1;

		Line low = tree[node].line, high = v;

		if (low.get(s) > high.get(s)) swap(low, high);

		if (low.get(e) <= high.get(e)) {
			tree[node].line = low; return;
		}

		if (low.get(m) < high.get(m)) {
			tree[node].line = low;
			if (tree[node].r == -1) {
				tree[node].r = tree.size();
				tree.push_back({ -1, -1, m + 1, e, { 0, INF } });
			}
			update(tree[node].r, high);
		}
		else {
			tree[node].line = high;
			if (tree[node].l == -1) {
				tree[node].l = tree.size();
				tree.push_back({ -1, -1, s, m, { 0, INF } });
			}
			update(tree[node].l, low);
		}
	}

	LL get(int node, LL x) {
		if (node == -1) return LNF;
		LL s = tree[node].s, e = tree[node].e;
		LL m = s + e >> 1;
		if (x <= m) return min(tree[node].line.get(x), get(tree[node].l, x));
		else return min(tree[node].line.get(x), get(tree[node].r, x));
	}
};
