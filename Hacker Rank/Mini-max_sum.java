import java.io.*;
import java.util.*;
import java.text.*;
import java.math.*;
import java.util.regex.*;

public class Solution {

    static void miniMaxSum(int[] arr) {
        // Complete this function
        long suma= 0;
        int max=arr[0];
        int min=max;
        for(int i=0;i<arr.length;i++){
            suma= suma+ arr[i];
            if(arr[i]>max) max=arr[i];
            if(arr[i]<min) min=arr[i];
        }
        System.out.println((suma-max)+" "+(suma-min));
    }

    public static void main(String[] args) {
        Scanner in = new Scanner(System.in);
        int[] arr = new int[5];
        for(int arr_i = 0; arr_i < 5; arr_i++){
            arr[arr_i] = in.nextInt();
        }
        miniMaxSum(arr);
        in.close();
    }
}
