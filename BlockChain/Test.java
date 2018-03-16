package dataStructure.BlockChain;

import org.json.JSONObject;

import java.util.HashMap;
import java.util.Map;

public class Test {
    public static void main(String[] args){
        BlockChain blockChain=BlockChain.getInstance();
        Map<String,Object> block=blockChain.newBlock(300,null);
        System.out.println(new JSONObject(block));

        blockChain.newTransactions("123","222",33);
        Map<String,Object> block1=blockChain.newBlock(500,null);
        System.out.println(new JSONObject(block1));

        blockChain.newTransactions("321","555",133);
        blockChain.newTransactions("000","111",10);
        blockChain.newTransactions("789","369",65);
        Map<String,Object> block2=blockChain.newBlock(600,null);
        System.out.println(new JSONObject(block2));

        Map<String,Object> chain=new HashMap<>();
        chain.put("chain",blockChain.getChain());
        chain.put("length",blockChain.getChain().size());
        System.out.println(new JSONObject(chain));
    }
}
