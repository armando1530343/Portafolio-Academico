/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;

/**
 *
 * @author Armando Isaac
 */
public class MallardDuck extends Duck {
    
    public MallardDuck(){
        fb = new FlyWithWings();
        qb = new Quack();
    }
    
    @Override
    public void display(){
        System.out.println("Displaying Mallard Duck.");
    }
}
