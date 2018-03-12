# leetcode刷题

> URL: https://leetcode.com/

## 3/5 

### findMedianSortedArray 
> https://github.com/badcyc/dataStructure/blob/algo/FindMedianSortedArrays.java

          left_A             |        right_A
    A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]

    left_B             |        right_B
    B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]

         left_part          |        right_part
    A[0], A[1], ..., A[i-1]  |  A[i], A[i+1], ..., A[m-1]
    B[0], B[1], ..., B[j-1]  |  B[j], B[j+1], ..., B[n-1]
 
### longestPalindrome 
> https://github.com/badcyc/dataStructure/blob/algo/LongestPalindrome.java
    
    
## 3/9

- autoi

- palindromeNumber

revert half of origin(condition: origin<revertNumber)
> https://leetcode/problems/palindrome-number/solution/


## 3/12
- longestCommonPrefix

 Further Thoughts / Follow up
 Let's take a look at a slightly different problem:
 
> Given a set of keys S={S1,S2,S3...Sn} find the longest common prefix 
among a string q and S. This LCP query will be called frequently.
 
 We could optimize LCP queries by storing the set of keys S in a Trie. For more information about Trie, please see this article Implement a trie (Prefix trie). In a Trie, each node descending from the root represents a common prefix of some keys. But we need to find the longest common prefix of a string q and all key strings. This means that we have to find the deepest path from the root, which satisfies the following conditions: it is prefix of query string q each node along the path must contain only one child element. Otherwise the found path will not be a common prefix among all strings. * the path doesn't comprise of nodes which are marked as end of key. Otherwise the path couldn't be a prefix a of key which is shorter than itself.
 
 **Algorithm**
 
 The only question left, is how to find the deepest path in the Trie, that fulfills the requirements above. The most effective way is to build a trie from [S_1 \ldots S_n][S
{S1,S2,S3..Sn} strings. Then find the prefix of query string q in the Trie. We traverse the Trie from the root, till it is impossible to continue the path in the Trie because one of the conditions above is not satisfied.
 ![pic1](img/1.png)
 
 Finding the longest common prefix using Trie
 
 Figure 4. Finding the longest common prefix of strings using Trie
 
 Java
 
 public String longestCommonPrefix(String q, String[] strs) {
     if (strs == null || strs.length == 0)
          return "";  
     if (strs.length == 1)
          return strs[0];
     Trie trie = new Trie();      
     for (int i = 1; i < strs.length ; i++) {
         trie.insert(strs[i]);
     }
     return trie.searchLongestPrefix(q);
 }
 
 class TrieNode {
 
     // R links to node children
     private TrieNode[] links;
 
     private final int R = 26;
 
     private boolean isEnd;
 
     // number of children non null links
     private int size;    
     public void put(char ch, TrieNode node) {
         links[ch -'a'] = node;
         size++;
     }
 
     public int getLinks() {
         return size;
     }
     //assume methods containsKey, isEnd, get, put are implemented as it is described
    //in  https://leetcode.com/articles/implement-trie-prefix-tree/)
 }
 
 public class Trie {
 
     private TrieNode root;
 
     public Trie() {
         root = new TrieNode();
     }
 
 //assume methods insert, search, searchPrefix are implemented as it is described
 //in  https://leetcode.com/articles/implement-trie-prefix-tree/)
     private String searchLongestPrefix(String word) {
         TrieNode node = root;
         StringBuilder prefix = new StringBuilder();
         for (int i = 0; i < word.length(); i++) {
             char curLetter = word.charAt(i);
             if (node.containsKey(curLetter) && (node.getLinks() == 1) && (!node.isEnd())) {
                 prefix.append(curLetter);
                 node = node.get(curLetter);
             }
             else
                 return prefix.toString();
 
          }
          return prefix.toString();
     }
 }


> https://leetcode.com/problems/longest-common-prefix/solution/