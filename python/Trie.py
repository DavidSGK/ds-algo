class Node:
    def __init__(self, val):
        self.children = {}
        self.eow = False
        self.val = val


class Trie:
    def __init__(self):
        self.root = Node("")

    def addWord(self, word):
        self._add(word, self.root)

    def _add(self, word, node):
        if len(word) == 0:
            node.eow = True
            return
        else:
            if node.children.get(word[0]) is None:
                node.children[word[0]] = Node(word[0])
            self._add(word[1:], node.children[word[0]])

    def contains(self, word):
        return self._contains(word, self.root)

    def _contains(self, word, node):
        if len(word) == 0:
            return True
        else:
            if node.children.get(word[0]) is None:
                return False
            else:
                return self._contains(word[1:], node.children[word[0]])

    def countWords(self, word):
        if not self.contains(word):
            return 0
        else:
            node = self.root
            for c in word:
                node = node.children[c]
            return self._countChildren(node)

    def _countChildren(self, node):
        sum = 0

        if len(node.children.keys()) == 0:
            sum += 1
        elif len(node.children.keys()) != 0:
            if node.eow:
                sum += 1
            for n in node.children:
                sum += self._countChildren(node.children[n])

        return sum