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
public class RubberDuck extends Duck{
    
    public RubberDuck(){
        fb = new FlyNoWay();
        qb = new Squeak();
    }
    
    @Override
    public void display(){
        System.out.println("Displaying Rubber Duck.");
    }
}