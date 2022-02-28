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
public class Practica3 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        System.out.println("== Practica 3");
        Duck[] ducks = new Duck[4];
        ducks[0] = new MallardDuck();
        ducks[1] = new RedHeadDuck();
        ducks[2] = new RubberDuck();
        ducks[3] = new DecoryDuck();
        
        runDuckSimulator(ducks);
        
        
    }
    
    public static void runDuckSimulator(Duck[] ducks){
        
        System.out.println("Running Simulation...\n");
        
        for(Duck duck : ducks){
            duck.display();
            duck.performQuack();
            duck.performFly();
            
            if(duck instanceof RubberDuck || duck instanceof DecoryDuck){
                System.out.println("Changing fly behavior...Rocket");
                duck.setFlyBehavior(new FlyRocketPowered());
                duck.performFly();
            }
            
            System.out.println("");
        }
    }
    
}
