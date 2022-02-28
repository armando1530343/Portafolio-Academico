
package edu.upv.poo;
import java.awt.*;
import javax.swing.*;
import java.awt.event.*;

/**
 *
 * @author Armando Isaac
 */
public class Practica07 {
JFrame frame;
JFrame drawableFrame;
    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
       Practica07 app = new Practica07();
       app.run();
    }
    
    public void run(){
        frame = new FrameNuevo();
        JButton button = new JButton ("Should I dou it?");
        ActionListener angelListener= new AngelListener();
        button.addActionListener(angelListener);
        button.addActionListener(new AngelListener());
        
        AngelListener myListener =new AngelListener(){
            @Override
            public void actionPerformed(ActionEvent event){
            JOptionPane.showMessageDialog(frame,"This is my action","",JOptionPane.INFORMATION_MESSAGE);
            
            
            }
        };
        
        
        frame.getContentPane().add(BorderLayout.CENTER,button);
        frame.setDefaultCloseOperation(FrameNuevo.EXIT_ON_CLOSE);
        frame.setSize(300,300);
        frame.setVisible(true);
        
        drawableFrame = new JFrame();
        MyDrawablePanel myDrawablePanel = new MyDrawablePanel();
        drawableFrame.add(myDrawablePanel,BorderLayout.CENTER);
        drawableFrame.setSize(500, 300);
        drawableFrame.setVisible(true);        
        
    }
    
    class AngelListener implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent event){
            JOptionPane.showMessageDialog(frame, this,"Don't do it, you might it!", JOptionPane.INFORMATION_MESSAGE);
        
        }
    
    }
    
}
