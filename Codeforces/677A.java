import java.util.Scanner;

/**
 *
 * @author usuario
 */
public class Main{
    
    public static void main(String[] args){
        Scanner console = new Scanner(System.in);
        int n=console.nextInt();
        int h= console.nextInt();
        int suma=0;
        for (int i = 0; i < n; i++) {
            if(h< console.nextInt()){
                suma=suma+2;
            }else{
                suma++;
            }
           
        }
        System.out.println(suma);
    }
        
}
