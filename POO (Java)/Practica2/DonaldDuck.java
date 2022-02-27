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
public class DonaldDuck extends Duck implements Flyable, Quackable, Swimable, Eatable, Speakable{
    @Override 
    public void display(){
         System.out.println("Displaying a Donald Duck...");
    }
    @Override
    public void fly(){
        System.out.println("Flying...");
    }
    @Override
    public void quack(){
        System.out.println("Quack quack...");
    }
    @Override
    public void swim(){
        System.out.println("Swiming...");
    }
    @Override
    public void eat(){
        System.out.println("Eating...");
    }
    @Override
    public void speak(){
        System.out.println("Speak...");
    }
}