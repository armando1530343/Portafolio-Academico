/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package practica4;

/**
 *
 * @author Armando Isaac
 */
public class Practica4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        System.out.println("==Practica 4");
        Character [] c = new Character[4];
        c[0] = new King();
        c[1] = new Queen();
        c[2] = new Knight();
        c[3] = new Troll();
        
        runGame(c);
        
    }
    public static void runGame(Character [] character){
        System.out.println("Running game...");
        for(Character c : character){
            c.fight();
            if(c instanceof King){
                c.setWeaponBehavior(new SwordBehavior());
                ((King) c).weapon.useWeapon();
            }
            if(c instanceof Queen){
                c.setWeaponBehavior(new BowAndArrowBehavior());
                ((Queen) c).weapon.useWeapon();
            }
            if(c instanceof Knight){
                c.setWeaponBehavior(new KnifeBehavior());
                ((Knight) c).weapon.useWeapon();
            }
            if(c instanceof Troll){
                c.setWeaponBehavior(new AxeBehavior());
                ((Troll) c).weapon.useWeapon();
            }
        }
    }
    
}
