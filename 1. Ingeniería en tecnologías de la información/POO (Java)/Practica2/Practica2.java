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
public class Practica2 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("== Practica2: Duck Simulator");
        MallardDuck mallard = new MallardDuck();
        RedHeadDuck redHead = new RedHeadDuck();
        RubberDuck rubber = new RubberDuck();
        DecoryDuck decory = new DecoryDuck();
        DonaldDuck donald = new DonaldDuck();
        PaperDuck paper = new PaperDuck();
        RoastedDuck roasted = new RoastedDuck();
        
        Duck[] ducks = new Duck[7];
        ducks[0] = mallard;
        ducks[1] = redHead;
        ducks[2] = rubber;
        ducks[3] = decory;
        ducks[4] = donald;
        ducks[5] = paper;
        ducks[6] = roasted;
        
        //Incluir 3 tipos de patos más
        //incluir 2 comportamientos más
        
        processDucks(ducks);
    }
    
    public static void processDucks(Duck[] ducks){
        for(Duck d: ducks){
            d.display();
            if(d instanceof Quackable){
                ((Quackable)d).quack();
            }
            if(d instanceof Flyable){
                ((Flyable)d).fly();
            }
            if(d instanceof Swimable){
                ((Swimable)d).swim();
            }
            if(d instanceof Eatable){
                ((Eatable)d).eat();
            }
            if(d instanceof Speakable){
                ((Speakable)d).speak();
            }
        }
    }
    
}
