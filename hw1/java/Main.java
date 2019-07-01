import java.util.*;
import java.lang.*;
import java.io.*;

public class Main{
    public static void main(String[] args){
        int[] a = { 4, 5, 1, 3, 6, 7, 9, 10, 2, 8 };
        int n = 10;
        int k = 4;
        int ans1 = Hw1.randomizedSelect(a, n, k);
        if(Hw1.Checker(a, n, k, ans1)==true){
            System.out.println("correct");
        }
        else{
            System.out.println("incorrect");
        }
        int ans2 = Hw1.deterministicSelect(a, n, k);
        if(Hw1.Checker(a, n, k, ans2)==true){
            System.out.println("correct");
        }
        else{
            System.out.println("incorrect");
        }

    }
}
