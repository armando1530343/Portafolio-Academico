
package edu.upv.poo;
import javax.swing.*;
public class Practica13 {

    public static void main(String[] args) {
        JFrame frame = new JFrame("Arkanoind");
        GamePanel gamePanel = new GamePanel();
        frame.add(gamePanel);
        frame.setSize(300,400);
        frame.setVisible(true);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        gamePanel.run();
    }
    
}
