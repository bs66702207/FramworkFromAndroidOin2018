import java.util.*;

public class BitSetDemo1 {

   public static void main(String[] args) {

      // create 3 bitsets
      BitSet bitset1 = new BitSet(20);
      BitSet bitset2 = new BitSet(20);
      BitSet bitset3 = new BitSet(20);

      // assign values to bitset1
      bitset1.set(0);
      bitset1.set(1);
      bitset1.set(2);
      bitset1.set(3);
      bitset1.set(4);
      bitset1.set(5);

      // assign values to bitset2
      bitset2.set(2);
      bitset2.set(4);
      bitset2.set(6);
      bitset2.set(8);
      bitset2.set(10);

      // print the sets
      System.out.println("Bitset1:" + bitset1);
      System.out.println("Bitset2:" + bitset2);

      // print the first clear bit of bitset1
      System.out.println("" + bitset1.nextClearBit(0));//6

      // print the first clear bit of bitset2 after index 15
      System.out.println("" + bitset2.nextClearBit(15));

      System.out.println("" + bitset3.nextClearBit(0));
   }
}

