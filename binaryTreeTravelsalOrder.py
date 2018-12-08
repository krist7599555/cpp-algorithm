'''

Finding Satisfy Binary Tree From Tree Traversal Order.
- Pre Order
- In Order
- Post Order

'''

from itertools import zip_longest, product

class BinTree:
    
    def __init__(self, v = None, l = None, r = None):
        self.data = v
        self.child = [l, r]

    def __str__(self):
        if self.data is None:
            return ""
        rt = str(self.data)
        if all(ch is None for ch in self.child):
            return rt
        ch = list(map(str, self.child))
        for i in [0, 1]:
            ch[i] = ch[i].split('\n')
        szl, szm, szr = map(len, (ch[0][0], rt, ch[1][0]))
        s = [
            l.ljust(szl) + ' ' * szm + r.ljust(szr)
            for l, r in zip_longest(*ch, fillvalue="")
        ]
        return '\n'.join([' ' * szl + rt + ' ' * szr] + s)
    
    def _travel(self, merge_func, defaultvalue):
        if self is None or self.data is None:
            return defaultvalue
        else:
            l, r = (BinTree._travel(ch, merge_func, defaultvalue) for ch in self.child)
            return merge_func(l, self.data, r)

    def preord(self): return TreeSeq(0, self._travel(lambda l, m, r: [m] + l + r, []))
    def inord (self): return TreeSeq(1, self._travel(lambda l, m, r: l + [m] + r, []))
    def posord(self): return TreeSeq(2, self._travel(lambda l, m, r: l + r + [m], []))
    def tolist(self): return self._travel(lambda l, m, r: [l, [m], r], None)

class TreeSeq(list):
    BinaryTreeSeqType = {"PRE": 0, "IN": 1, "POS": 2}
    def __init__(self, typ, ls = None):
        if type(typ) == TreeSeq:
            super().__init__(typ)
            self.type = typ.type
        elif type(typ) == list:
            raise "TreeSeq not accept list with out type"
        else:
            super().__init__(ls)
            self.type = typ if type(typ) == int else TreeSeq.BinaryTreeSeqType.get(typ, None)

    
    def _get(self, fnd = None):
        return super().__getitem__(fnd if fnd is not None else slice(None))

    def __repr__(self):
        return f'TreeSeq({repr(["PRE", "IN", "POS"][self.type]).ljust(5)}, {repr(self._get(slice(None)))})'

    def __getitem__(self, fnd):
        return self._get(fnd) if type(fnd) == int else TreeSeq(self.type, self._get(fnd))

    def index(self, val):
        try:
            return next(i for i, v in enumerate(self._get()) if v == val)
        except:
            raise ValueError(f'Could not find {repr(val)} in {self}')
    
    def solve(l, r):
        if type(l) != TreeSeq or type(r) != TreeSeq: raise ValueError(f"Type is wrong [{type(l)}, {type(r)}]\n\t{l}\n\t{r}")
        if l.type == r.type: raise ValueError(f"Both have same type\n\t{l}\n\t{r}")
        if len(l) != len(r): raise ValueError(f"Both not have same length\n\t{l}\n\t{r}\n")
        for t in [l, r]: 
            if len(set(t)) != len(t): raise ValueError(f"Not Unique Element\n\t{t}\n")
        return TreeSeq._solve(l, r)

    def _solve(l, r):
        if not l and not r: return BinTree()
        if not l or not r: return None

        l = TreeSeq(l)  # COPY TREE
        r = TreeSeq(r)

        if len(l) != len(r): raise f"Logic Error\n\t{l}\n\t{r}\nLength not equal"
        if set(l) != set(r): raise f"Logic Error\n\t{l}\n\t{r}\nElement is not same"

        x1 = [0, None, len(l) - 1][l.type] # SELECT TYPE
        x2 = [0, None, len(r) - 1][r.type]
        split1, split2 = None, None
        root = None
        trying_pair = []

        if x1 is None or x2 is None:
            if x1 is None:  # l is IN-OREDER
                x1 = l.index(r[x2])
                root = l[x1]
            if x2 is None:  # r is IN-OREDER
                x2 = r.index(l[x1])
                root = r[x2]
            l.remove(root)
            r.remove(root)
            split1 = (l[:x1], l[x1:])  # CUTTING 2 PART
            split2 = (r[:x1], r[x2:])
            trying_pair.append([split1, split2])
        else:
            # PRE-ORDER & POS-ORDER
            if l[x1] != r[x2]: return None
            root = l[x1]
            l.remove(root)
            r.remove(root)
            for i in range(len(l)):  # TRYING CUTTING 2 PART ALL POSSIBLE WAYS
                if set(l[:i]) == set(r[:i]) and set(r[i:]) == set(r[i:]):
                    trying_pair.append([(l[:i], l[i:]), (r[:i], r[i:])])

        if not l and not r:  # LEAF
            return BinTree(root)

        for (ll, lr), (rl, rr) in trying_pair: # FIND ACCEPT STAGE RECURSIVELY
            if set(ll) != set(rl) or set(lr) != set(rr):
                continue
            rsl = TreeSeq._solve(ll, rl)
            rsr = TreeSeq._solve(lr, rr)
            if rsl is not None and rsr is not None:
                return BinTree(root, rsl, rsr)
        return None


def tryall(*its):
    _t1, _t2 = map(list, its)
    for i, j in product(range(3), repeat=2):
        t1 = TreeSeq(i, _t1)
        t2 = TreeSeq(j, _t2)
        try:
            res = TreeSeq.solve(t1, t2)
            if res is not None:
                al = set(map(str, [res.preord(), res.inord(), res.posord()]))
                st = set(map(str, [t1, t2]))
                print(t1)
                print(t2)
                print(*(al - st), sep='\n')
                return res
            # print(res)
        except Exception as e:
            pass
            # print(str(e), file = sys.stderr)
        # finally:
        #     print('-' * 20)
    return None

if __name__ == "__main__":

    # Test 1 [success]
    t1 = TreeSeq("PRE", "ECABFDGH")
    t2 = TreeSeq("POS", "ABCGDHFE")
    res = TreeSeq.solve(t1, t2)
    print(res.preord())
    print(res.inord())
    print(res.posord())
    print(res)
    print('-' * 10)

    # Test 2 [no solution]
    t1 = TreeSeq("PRE", "ECABFDGH")
    t2 = TreeSeq("POS", "ABCGDHEF")
    res = TreeSeq.solve(t1, t2)
    print(res)
    print('-' * 10)

    # Test 3 [wrong format]
    t1 = TreeSeq("PRE", "ECABFDGH")
    t2 = TreeSeq("POS", "ABCGDHE")
    try:
        res = TreeSeq.solve(t1, t2)
        print(res)
    except Exception as e:
        print(e)
    print('-' * 10)


    # Test 4 [find satisfy]
    print(tryall([1, 4, 3, 2], [3, 2, 4, 1]))
