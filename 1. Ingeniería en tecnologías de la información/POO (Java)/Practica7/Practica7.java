/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;
import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

/**
 *
 * @author Armando Isaac
 */
public class Practica7{
    JFrame frame;

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        
        Practica7 app = new Practica7();
        app.run();
    }
    public void run(){
        frame = new JFrame();
        
        JButton button = new JButton("Should I dou it");
        frame.getContentPane().add(BorderLayout.CENTER, button);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.setSize(300, 300);
        frame.setVisible(true);
        ActionListener angelListener = new AngelListener();
        button.addActionListener(angelListener);
        button.addActionListener(new AngelListener());
        
        ActionListener myListener = new ActionListener(){
            @Override
            public void actionPerformed(ActionEvent event){
                JOptionPane.showMessageDialog(frame, "This is y action !!", "", JOptionPane.INFORMATION_MESSAGE);
            }
            
        };
        button.addActionListener(myListener);
        
        ActionListener myListenerL = event -> JOptionPane.showMessageDialog(frame, "This is y action !!", "", JOptionPane.INFORMATION_MESSAGE);
        
        frame.getContentPane().add(BorderLayout.CENTER, button);
        
        button.addActionListener(myListener);
    }
    class AngelListener implements ActionListener{
        @Override
        public void actionPerformed (ActionEvent event){
            JOptionPane.showMessageDialog(frame, this, "Don't do it, you might regret it!", JOptionPane.INFORMATION_MESSAGE);
        }
    }    
}