/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica2;

/**
 *
 * @author Armando Isaac
 */
public class PaperDuck extends Duck implements Swimable{
    @Override 
    public void display(){
         System.out.println("Displaying a Paper Duck...");
    }
    @Override
    public void swim(){
        System.out.println("Swiming...");
    }
}
