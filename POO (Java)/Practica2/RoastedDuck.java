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
public class RoastedDuck extends Duck implements Eatable{
    @Override 
    public void display(){
        System.out.println("Displaying a Roasted Duck...");
    } 
    @Override
    public void eat(){
        System.out.println("Eating Duck...");
    }
}
