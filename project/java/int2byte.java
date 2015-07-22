/* http://www.cnblogs.com/cpcpc/archive/2011/09/05/2167889.html */
/*
public static byte[] int2byte(int res) 
{
byte[] targets = new byte[4];

targets[0] = (byte) (res & 0xff);// ���λ 
targets[1] = (byte) ((res >> 8) & 0xff);// �ε�λ 
targets[2] = (byte) ((res >> 16) & 0xff);// �θ�λ 
targets[3] = (byte) (res >>> 24);// ���λ,�޷������ơ� 
return targets; 
}


public static void main(String[] args) {  
        ByteArrayOutputStream baos = new ByteArrayOutputStream();  
        DataOutputStream dos = new DataOutputStream(baos);  
        try {  
            dos.writeByte(4);  
            dos.writeByte(1);  
            dos.writeByte(1);  
            dos.writeShort(217);  
          } catch (IOException e) {  
        e.printStackTrace();  
    }  
  
    byte[] aa = baos.toByteArray();  
    ByteArrayInputStream bais = new ByteArrayInputStream(baos.toByteArray());  
    DataInputStream dis = new DataInputStream(bais);  
  
    try {  
        System.out.println(dis.readByte());  
        System.out.println(dis.readByte());  
        System.out.println(dis.readByte());  
        System.out.println(dis.readShort());  
    } catch (IOException e) {  
        e.printStackTrace();  
    }  
    try {  
        dos.close();  
        dis.close();  
    } catch (IOException e) {  
        e.printStackTrace(); 
    }  
}
*/

/* http://blog.csdn.net/zgyulongfei/article/details/7738970 */
public class Utilities {

	public static byte[] int2byte(int res) 
	{
	    byte[] targets = new byte[4];
	
	    targets[0] = (byte) (res & 0xff);// ���λ 
	    targets[1] = (byte) ((res >> 8) & 0xff);// �ε�λ 
	    targets[2] = (byte) ((res >> 16) & 0xff);// �θ�λ 
	    targets[3] = (byte) (res >>> 24);// ���λ,�޷������ơ� 
	    return targets; 
	}

	public static byte[] int2Bytes(int num) 
	{
		byte[] byteNum = new byte[4];
		for (int ix = 0; ix < 4; ++ix) 
		{
			int offset = 32 - (ix + 1) * 8;
			byteNum[ix] = (byte) ((num >> offset) & 0xff);
		}
		return byteNum;
	}

	public static int bytes2Int(byte[] byteNum) 
	{
		int num = 0;
		for (int ix = 0; ix < 4; ++ix) {
			num <<= 8;
			num |= (byteNum[ix] & 0xff);
		}
		return num;
	}

	public static byte int2OneByte(int num) 
	{
		return (byte) (num & 0x000000ff);
	}

	public static int oneByte2Int(byte byteNum) 
	{
						//���������int
        return byteNum > 0 ? byteNum : (128 + (128 + byteNum));
	}
		
	public static byte[] long2Bytes(long num) 
	{
		byte[] byteNum = new byte[8];
		for (int ix = 0; ix < 8; ++ix) 
		{
			int offset = 64 - (ix + 1) * 8;
			byteNum[ix] = (byte) ((num >> offset) & 0xff);
		}
		return byteNum;
	}

	public static long bytes2Long(byte[] byteNum) 
	{
		long num = 0;
		for (int ix = 0; ix < 8; ++ix) 
		{
			num <<= 8;
			num |= (byteNum[ix] & 0xff);
		}
		return num;
	}
}


public class TestMain {
	public static void main(String[] args) 
	{
		int num = 129;
		System.out.println("���Ե�intֵΪ:" + num);

		byte[] int2bytes = Utilities.int2Bytes(num);
		System.out.printf("intת��bytes: ");
		for (int i = 0; i < 4; ++i) {
			System.out.print(int2bytes[i] + " ");
		}
		System.out.println();

		int bytes2int = Utilities.bytes2Int(int2bytes);
		System.out.println("bytesת�г�int: " + bytes2int);

		byte int2OneByte = Utilities.int2OneByte(num);
		System.out.println("intת�г�one byte: " + int2OneByte);

		int oneByte2Int = Utilities.oneByte2Int(int2OneByte);
		System.out.println("one byteת�г�int: " + oneByte2Int);
		System.out.println();

		long longNum = 100000;
		System.out.println("���Ե�longֵΪ��" + longNum);

		byte[] long2Bytes = Utilities.long2Bytes(longNum);
		System.out.printf("longת�г�bytes: ");
		for (int ix = 0; ix < long2Bytes.length; ++ix) {
			System.out.print(long2Bytes[ix] + " ");
		}
		System.out.println();

		long bytes2Long = Utilities.bytes2Long(long2Bytes);
		System.out.println("bytesת�г�long: " + bytes2Long);
	}
}

