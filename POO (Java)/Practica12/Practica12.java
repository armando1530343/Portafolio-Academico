/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica12;
import static java.lang.System.out;
import java.lang.Exception;

/**
 *
 * @author Armando Isaac
 */
public class Practica12 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args)throws Exception {
        // TODO code application logic here
        
        try{
            throwException();
        }
        catch(Exception ex){
            out.println("Error: " + ex.getMessage());
        }
        int fromArray = readFromArray();
        out.println(fromArray);
    }
    
    static void throwException() throws Exception{
        out.println("Calling method");
        throw new Exception("Something went wrong");
    }
    
    static int readFromArray(){
        int[] intArr = new int[8];
        return intArr[8];
    }
    
}