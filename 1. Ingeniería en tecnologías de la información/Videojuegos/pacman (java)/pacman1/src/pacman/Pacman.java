/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pacman;

import javax.swing.JFrame;

/**
 *
 * @author Armando Isaac
 */
public class Pacman {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        JFrame tablero = new JFrame("PACMAN");
        Laberinto lab = new Laberinto();
        tablero.add(lab);
        tablero.setSize(800,600);
        tablero.setVisible(true);
        tablero.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        lab.run();
    }
    
}
