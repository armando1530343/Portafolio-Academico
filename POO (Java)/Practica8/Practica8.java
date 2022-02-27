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
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

public class Practica8 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        JFrame clockFrame = new JFrame("My analog clock");
        AnalogClockPanel clockPanel = new AnalogClockPanel();
        clockFrame.add(clockPanel);
        clockFrame.setSize(450,450);
        clockFrame.setVisible(true);
    }
}