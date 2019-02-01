import java.util.*;

class LongTest
{
	public static byte[] long2Bytes(long num) {
        byte[] byteNum = new byte[8];
        for (int ix = 0; ix < 8; ++ix) {
            int offset = 64 - (ix + 1) * 8;
            byteNum[ix] = (byte) ((num >> offset) & 0xff);
        }
        return byteNum;
    }

	public static byte[] addBytes(byte[] data1, byte[] data2) {
		byte[] data3 = new byte[data1.length + data2.length];
		System.arraycopy(data1, 0, data3, 0, data1.length);
		System.arraycopy(data2, 0, data3, data1.length, data2.length);
		return data3;
 
	}

	public static void main(String[] args)
	{
		long m = 1;
		long l = 0x01000401;
		byte[] str = new byte[5];
		str[0] = 96;
		str[1] = 97;
		str[2] = 98;
		str[3] = 99;
		//System.out.println(addBytes(long2Bytes(m), long2Bytes(l)));
		//System.out.println(Arrays.toString(addBytes(long2Bytes(m), long2Bytes(l))));
		System.out.println(new String(str).toString());

		byte[] x = new byte[2];
		byte[] y = new byte[2];
		x [0] = 1;
		y [0] = 2;
		//System.out.println(x[0]);
		//System.out.println(x[1]);
		//System.out.println(Arrays.equals(x,y));
	}
}
