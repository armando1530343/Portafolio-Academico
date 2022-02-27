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
public abstract class Duck {
    FlyBehavior fb;
    QuackBehavior qb;
    
    public void setFlyBehavior(FlyBehavior fb){
        this.fb = fb;
    }
    public void setQuackBehavior(QuackBehavior qb){
        this.qb = qb;
    }
    
    public void performFly(){
        fb.fly();
    }
    
    public void performQuack(){
        qb.quack();
    }
    
    public abstract void display();
}
