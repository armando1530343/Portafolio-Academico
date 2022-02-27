/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.ArrayList;
/**
 *
 * @author Armando Isaac
 */
public class MyDrawablePanel extends JPanel {
    
    private ArrayList<Point> points;
    private Point punto1, punto2;
    private boolean click;
    private int ancho, alto;
    private int recx, recy;
    
    
    public MyDrawablePanel(){
       points = new ArrayList<>();
       punto1 = new Point();
       punto2 = new Point();
       ancho = 0;
       alto = 0;
       recx = 0;
       recy = 0;
       addMouseMotionListener(new MouseHandler());
       addMouseListener(new MouseListen());
       click = false;
       
    }
    
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        /*for(Point p: points ){
            //g.fillOval((int)p.getX(), (int)p.getY(), 3, 3);
            g.drawLine((int)p.getX(), (int)p.getY(), 3, 3);
        }*/
        if (click == true)
            g.drawLine(punto1.x, punto1.y, punto2.x, punto2.y);
        else
            g.drawRect(recx, recy, ancho, alto);
    }
    class MouseHandler implements MouseMotionListener{

        @Override
        public void mouseDragged(MouseEvent me){
            //points.add(me.getPoint());
            punto2 = me.getPoint();
            
            if(me.getX() < punto1.x && me.getY() < punto1.y){
                //superior izquierda
                recx = me.getX();
                recy = me.getY();
                ancho = punto1.x - recx;
                alto = punto1.y - recy;
            }
            if(me.getX() > punto1.x && me.getY() < punto1.y){
                //superior derecha
                recx = punto1.x;
                recy = me.getY();
                ancho = me.getX() - recx;
                alto = punto1.y - me.getY();
            }
            if(me.getX() < punto1.x && me.getY() > punto1.y){
                //inferior izquierda
                recx = me.getX();
                recy = punto1.y;
                ancho = punto1.x - me.getX();
                alto = me.getY() - punto1.y;
            }
            if(me.getX() > punto1.x && me.getY() > punto1.y){
                //inferior derecha
                recx = punto1.x;
                recy = punto1.y;
                ancho = me.getX() - punto1.x;
                alto = me.getY() - punto1.y;
            }
            repaint();
        }
        
        @Override
        public void mouseMoved(MouseEvent me){
            //System.out.println("click");
            //repaint();
        }     
    }
    
    class MouseListen implements MouseListener{
        
        @Override
        public void mouseClicked(MouseEvent e) {
           //points.add(e.getPoint());
           
           //System.out.println("presiona");
           
        }

        @Override
        public void mousePressed(MouseEvent e) {
            click = !click;
            if(click == true)
                System.out.println("linea");
            else
                System.out.println("rectangulo");
            punto1 = e.getPoint();
        }

        @Override
        public void mouseReleased(MouseEvent e) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

        @Override
        public void mouseEntered(MouseEvent e) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

        @Override
        public void mouseExited(MouseEvent e) {
            //throw new UnsupportedOperationException("Not supported yet."); //To change body of generated methods, choose Tools | Templates.
        }

        
        
    }
}
