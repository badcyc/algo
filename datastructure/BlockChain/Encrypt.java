package dataStructure.datastructure.BlockChain;

import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

public class Encrypt {
    /**
     * 传入字符串，返回SHA-256加密字符串
     * @param strText
     * @return
     */

    public String getSHA256(final String strText){
        return SHA(strText,"SHA-256");
    }
    public String getSHA512(final String strText){
        return SHA(strText,"SHA-512");
    }

    public String getMD5(final String strText){
        return SHA(strText,"SHA_512");
    }

    public String SHA(final String strText,final String strType){
        String strResult=null;
        if (strText!=null&&strText.length()>0){
            try {

                //SHA加密
                //创建加密对象，传入加密类型
                MessageDigest messageDigest=MessageDigest.getInstance(strType);
                //传入要加密的字符串
                messageDigest.update(strText.getBytes());
                //得到byte数组
                byte byteBuffer[]= messageDigest.digest();
                //将byte数组转换String类型
                StringBuffer strHexString=new StringBuffer();
                for (int i = 0; i < byteBuffer.length; i++) {
                    //转换成16进制并存储在字符串中
                    String hex=Integer.toHexString(0xff&byteBuffer[i]);
                    if (hex.length()==1){
                        strHexString.append('0');
                    }
                    strHexString.append(hex);
                }
                //得到返回结果
                strResult=strHexString.toString();
            }catch (NoSuchAlgorithmException e){
                e.printStackTrace();
            }
        }
        return strResult;
    }

    @Override
    public String toString() {
        return super.toString();
    }
}
