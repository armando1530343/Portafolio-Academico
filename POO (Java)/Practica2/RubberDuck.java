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
public class RubberDuck extends Duck implements Quackable, Swimable{
    @Override 
    public void display(){
        System.out.println("Displaying a Rubber Duck...");
    } 
    @Override 
    public void quack(){
        System.out.println("squeak squeak !!!");
    }
    @Override 
    public void swim(){
        System.out.println("Floating...");
    }
}
