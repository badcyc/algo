package dataStructure.LongestCommprefix;

public class Trie {
    private TrieNode root;
    public Trie(){
        root=new TrieNode();
    }
    public void insert(String word){
        TrieNode node=root;
        for (int i=0;i<word.length();i++){
            char currentChar=word.charAt(i);
            if (!node.containKey(currentChar)){
                node.put(currentChar,new TrieNode());
            }
            node=node.get(currentChar);
        }
        node.setEnd();
    }

    private TrieNode searchPrefix(String word){
        TrieNode node=root;
        for (int i=0;i<word.length();i++){
            char currentChar=word.charAt(i);
            if (node.containKey(currentChar)){
                node=node.get(currentChar);
            }else {
                return null;
            }
        }
        return node;
    }
    public boolean search(String word){
        TrieNode node=searchPrefix(word);
        return node!=null&&node.isEnd();
    }
    public boolean startWith(String prefix){
        TrieNode node=searchPrefix(prefix);
        return node!=null;
    }

    private String searchLongestPrefix(String word) {
        TrieNode node = root;
        StringBuilder prefix = new StringBuilder();
        for (int i = 0; i < word.length(); i++) {
            char curLetter = word.charAt(i);
            if (node.containKey(curLetter) && (node.getLinks() == 1) && (!node.isEnd())) {
                prefix.append(curLetter);
                node = node.get(curLetter);
            }
            else
                return prefix.toString();

        }
        return prefix.toString();
    }
}
