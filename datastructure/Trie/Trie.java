package AVLtree.Trie;

public class Trie {

    protected TrieNode root=new TrieNode('a');

    public void insertWord(String word){
        TrieNode index=this.root;
        for (char c:word.toLowerCase().toCharArray()){
            index=index.addChild(c);
        }
    }

    private class TrieNode{
        private final char nodeChar;
        private TrieNode[] childNodes=null;

        public TrieNode(char nodeChar){
            super();
            this.nodeChar=nodeChar;
        }
        public TrieNode addChild(char c){
            int index=c-'a';
            if (null==childNodes){
                this.childNodes=new TrieNode[26];
            }
            if (null==childNodes[index]){
                childNodes[index]=new TrieNode(c);
            }
            return childNodes[index];
        }

        @Override
        public String toString() {
            return "TrieNode[nodechar="+nodeChar+']';
        }
    }
}
