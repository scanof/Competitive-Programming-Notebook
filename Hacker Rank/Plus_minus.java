import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    static void plusMinus(int[] arr) {
        // Complete this function
        int p=0;
        int n=0;
        int z=0;
        for(int i=0;i<arr.length;i++){
            if(arr[i]<0) n++;
            if(arr[i]>0) p++;
            if(arr[i]==0) z++;
        }
        String num="";
        Double k=p/(double)arr.length;        
        System.out.println(num.format("%.6f", k));
        k=n/(double)arr.length;
        System.out.println(num.format("%.6f", k));
        k=z/(double)arr.length;
        System.out.println(num.format("%.6f", k));
        
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int n = in.nextInt();
        int[] arr = new int[n];
        for(int arr_i = 0; arr_i < n; arr_i++){
            arr[arr_i] = in.nextInt();
        }
        plusMinus(arr);
        in.close();
    }
}
