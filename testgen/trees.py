#!/usr/bin/python

from random import randint, shuffle, seed, choice

class RandomGraph:
    def __init__(self, n, m, multiple_edges=False, loops=False):
        self.n = n
        self.m = m
        self.multiple_edges = multiple_edges
        self.loops = loops
        if multiple_edges:
            if m > self.max_edges_number():
                raise Exception("Too many edges")

        self.generate();

    def max_edges_number(self):
        n = self.n
        if self.loops:
            return n * (n+1) / 2
        else:
            return n * (n-1) / 2

    def edge_by_index(self, index):
        n = self.n
        if self.loops:
            n += 1

        cand = int((2 * index) ** 0.5) + 1
        while cand * (cand + 1) / 2 > index:
            cand -= 1
        return (cand, index - cand * (cand + 1) / 2 + 
            (self.loops and 0 or 1))
    
    def generate(self):
        edges = []
        if self.multiple_edges:
            edges = [choice(xrange(self.max_edges_number()))
                    for i in range(self.m)]
        else:
            res = set()
            while len(res) < self.m:
                res.update(set(
                    [choice(xrange(self.max_edges_number()))
                        for i in range(self.m)]))
            edges = list(res)
            shuffle(edges)
            edges = edges[:self.m]
        self.edges = [self.edge_by_index(index) for index in edges]

    def print_all(self, offset=1):
        print self.n, self.m
        self.print_only_graph(offset)

    def print_only_graph(self, offset=1):
        for edge in self.edges:
            print edge[1] + offset, edge[0] + offset


