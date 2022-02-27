/*
    PRACTICA REALIZADA POR: FROYLÁN MELQUIADES WBARIO MARTINEZ
    ITI-UPV
    7-2
*/

package edu.upv.poo;

import java.awt.*;
import javax.swing.*;

public class Practica07_Tarea {
    
    public JFrame frame;
    public JFrame paint;

    public static void main(String[] args) {
        Practica07_Tarea app = new Practica07_Tarea();
        app.run();
    }
    
    public void run(){
        paint = new JFrame();
        Paint myDrawablePanel = new Paint();
        paint.add(myDrawablePanel, BorderLayout.CENTER);
        paint.setSize(800, 500);
        paint.setVisible(true);
    }
}
