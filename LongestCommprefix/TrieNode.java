package dataStructure.LongestCommprefix;

import java.security.cert.TrustAnchor;

public class TrieNode {
    private TrieNode[] links;
    private final  int R=26;
    private boolean isEnd;
    private int size;
    public TrieNode(){
        links=new TrieNode[R];
    }
    public boolean containKey(char ch){
        return links[ch-'a']!=null;
    }
    public TrieNode get(char ch){
        return links[ch-'a'];
    }
    public void put(char ch,TrieNode node){
        links[ch-'a']=node;
        size++;
    }

    public void setEnd() {
        isEnd = true;
    }

    public boolean isEnd() {
        return isEnd;
    }

    public int getLinks() {
        return size;
    }
}
