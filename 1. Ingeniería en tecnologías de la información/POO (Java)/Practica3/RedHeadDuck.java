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
public class RedHeadDuck extends Duck {
    
    public RedHeadDuck(){
        fb = new FlyWithWings();
        qb = new Quack();
    }
    
    @Override
    public void display(){
        System.out.println("Displaying Red Head Duck.");
    }
    
}
