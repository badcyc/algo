package dataStructure.BlockChain;

import org.json.JSONObject;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class BlockChain {

    private List<Map<String,Object>> chain;
    private List<Map<String,Object>> currentTransactions;
    private static BlockChain blockChain=null;
    public BlockChain(){
        this.chain=new ArrayList<Map<String, Object>>();
        this.currentTransactions=new ArrayList<Map<String, Object>>();
        newBlock(100,"0");
    }

    public static BlockChain getInstance(){
        if (blockChain==null){
            synchronized (BlockChain.class){
                if (blockChain==null){
                    blockChain=new BlockChain();
                }
            }
        }
        return blockChain;
    }
    public List<Map<String,Object>> getChain() {
        return chain;
    }

    public void setChain(List<Map<String,Object>> chain) {
        this.chain = chain;
    }

    public List<Map<String,Object>> getCurrentTransactions() {
        return currentTransactions;
    }

    public void setCurrentTransaction(List<Map<String,Object>> currentTransaction) {
        this.currentTransactions = currentTransaction;
    }
    public Map<String, Object> lastBlock(){
        return getChain().get(getChain().size()-1);
    }
    public Map<String,Object> newBlock(long proof,String previous_hash){
        Map<String,Object> block=new HashMap<>();
        block.put("index",getChain().size()+1);
        block.put("timestamp",System.currentTimeMillis());
        block.put("transactions",getCurrentTransactions());
        block.put("proof",proof);
        //如果没有传递上一区块的hash就计算出去快链中最后一个区块的hash
        block.put("previous_hash",previous_hash!=null?previous_hash:hash(getChain().get(getChain().size()-1)));
        setCurrentTransaction(new ArrayList<Map<String, Object>>());
        getChain().add(block);
        return block;
    }

    /**
     * 生成新交易心系，信息将加入到下一个待挖的区块中
     * @param sender
     * 发送方的地址
     * @param recipient
     * 接收方的地址
     * @param amount
     * 交易数量
     * @return
     */
    public int newTransactions(String sender,String recipient,long amount){
        Map<String,Object> transaction=new HashMap<String, Object>();
        transaction.put("sender",sender);
        transaction.put("recipient",recipient);
        transaction.put("amount",amount);

        getCurrentTransactions().add(transaction);
        return 0;
    }

    public static Object hash(Map<String,Object> block){
        return new Encrypt().getSHA256(new JSONObject(block).toString());
    }
}

