# Create a node
class BTreeNode:
    def __init__(self, leaf=False):
        self.leaf = leaf
        self.keys = []
        self.child = []
        self.n = 0


# Tree
class BTree:
    def __init__(self, t):
        self.r = BTreeNode(True)
        self.t = t

    # def __getattr__(self, name):
    #     if name == 'n':
    #         return len(self.r.keys)

    def splt(self, x, i):
        """
        :param BTreeNode x:
        :param int i:
        :return:
        """
        z = BTreeNode()
        y = x.child[i]
        z.leaf = y.leaf
        z.n = self.t - 1
        # for j in range(self.t - 1):
        #     z.keys[j] = y.keys[j + self.t]
        z.keys = y.keys[self.t - 1:]

        if not y.leaf:
            # for j in range(self.t):
            #     z.child[j] = y.child[j + self.t]
            z.child=y.child[self.t:]

        y.n = self.t - 1
        # for j in range(x.n, i, -1):
        #     x.child[j + 1] = x.child[j]
        # x.child[i + 1] = z
        x.child[i+2:]=x.child[i+1:]
        x.child[i+1]=z

        for j in range(x.n - 1, i - 1):
            x.keys[j + 1] = x.keys[j]
        x.keys[i] = y.keys[self.t - 1]
        x.n += 1

    def insert(self, k):
        r = self.r
        if r.n == 2 * self.t - 1:
            s = BTreeNode()
            self.r = s
            s.leaf = False
            s.n = 0
            s.child.append(r)


def main():
    btr = BTree(2)
    print(btr.r.n)


if __name__ == '__main__':
    main()
