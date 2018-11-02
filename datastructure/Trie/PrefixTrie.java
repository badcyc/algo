package AVLtree.Trie;

import java.io.*;
import java.util.regex.Pattern;

public class PrefixTrie {

    private TrieNode root = new TrieNode('a');

    public void insetWord(String word) {
        TrieNode index = this.root;
        for (char c : word.toLowerCase().toCharArray()) {
            index = index.addChild(c);
            index.addPrefixCount();
        }
        index.addCount();
        return;
    }

    public boolean selectWord(String word) {
        TrieNode index = this.root;
        for (char c : word.toLowerCase().toCharArray()) {
            index = index.getChild(c);
            if (null == index) {
                return false;
            }
        }
        return index.getCount() > 0;
    }

    public int selectPrefixCount(String prefix) {
        TrieNode index = this.root;
        for (char c : prefix.toLowerCase().toCharArray()) {
            index = index.getChild(c);
            if (null == index) {
                return 0;
            }
        }
        return index.getPrefixCount();
    }

    private class TrieNode {
        private final char nodeChar;
        private TrieNode[] childNodes = null;
        private int count = 0;
        private int prefixCount = 0;

        public TrieNode(char nodeChar) {
            super();
            this.nodeChar = nodeChar;
        }

        public TrieNode addChild(char ch) {
            int index = ch - 'a';
            if (null == childNodes) {
                this.childNodes = new TrieNode[26];
            }
            if (null == childNodes[index]) {
                childNodes[index] = new TrieNode(ch);
            }
            return childNodes[index];
        }

        public TrieNode getChild(char ch) {
            int index = ch - 'a';
            if (null == childNodes || null == childNodes[index]) {
                return null;
            }
            return childNodes[index];
        }

        public void addCount() {
            this.count++;
        }

        public int getCount() {
            return count;
        }

        public void addPrefixCount() {
            this.prefixCount++;
        }

        public int getPrefixCount() {
            return prefixCount;
        }

        @Override
        public String toString() {
            return "TrieNode[nodeChar=" + nodeChar + "]";
        }
    }

    public static void main(String[] args) throws IOException {
        PrefixTrie trie;
        Pattern pattern = Pattern.compile("[a-zA-Z]+");
        InputStreamReader reader;
        BufferedReader bufferedReader;
        File  file=new File("C:/Users/cyc20/IdeaProjects/JsoupLearn/src/AVLtree/Trie/words.txt");
        InputStream inputStream=new FileInputStream(file);
        reader = new InputStreamReader(inputStream);
        bufferedReader = new BufferedReader(reader);
        trie = new PrefixTrie();
        String line = null;
        while (null != (line = bufferedReader.readLine())) {
            line = line.trim();
            if (!pattern.matcher(line).matches()) {
                continue;
            }
            trie.insetWord(line);
        }
        String prefix = "vi";
        System.out.println(trie.selectPrefixCount(prefix));
        System.out.println(trie.selectWord("Vicky"));
    }
}
