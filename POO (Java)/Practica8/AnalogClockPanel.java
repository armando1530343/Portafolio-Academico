/*
 * To change this license header, choose Licens4e Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;

/**
 *
 * @author Armando Isaac
 */

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.math.*;
import java.util.Calendar;
import java.util.ArrayList;

public class AnalogClockPanel extends JPanel {
    
    private Timer timerH, timerM, timerS;
    private Calendar tiempo;
    private Graphics2D [] segundos;
    private double sx, sy;
    private int[]x;
    private int[]y;
    private int hora, min, seg, h;
    private double angulo, pi;
    
    public AnalogClockPanel(){
        sx = 200;
        sy = 0;
        angulo = -90;
        segundos = new Graphics2D[60];
        x = new int[60];
        y = new int[60];
        h=0;
        tiempo = Calendar.getInstance();
        hora = tiempo.get(Calendar.HOUR); 
        min = tiempo.get(Calendar.MINUTE); 
        seg = tiempo.get(Calendar.SECOND);
        pi = 3.1415926535897932384626433832795;
        
        timerS = new Timer(1000, e -> Segundos());
        timerS.start();
        //timerM = new Timer(300, e -> Minutos());
    }
    
    public void Segundos(){
        System.out.println(seg);        
        seg += 1;
        if(seg == 61)seg = 1;
        repaint();
    }    
    
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D)g;
        Graphics2D minutero = (Graphics2D)g;
        Graphics2D horario = (Graphics2D)g;
        Graphics2D [] numero = new Graphics2D[12];
        g2d.setRenderingHint(
                RenderingHints.KEY_ANTIALIASING,
                RenderingHints.VALUE_ANTIALIAS_ON);
        
        //g2d.fillOval(0, 0, 400, 400);
        int j = 0;
        for(int i = 0; i < segundos.length; i++){
            double cosAng = Math.cos(pi / 180 * angulo);
            double senAng = Math.sin(pi / 180 * angulo);
            sx = 200 * cosAng;      
            sy = 200 * senAng;
            segundos[i] = (Graphics2D)g;
            segundos[i].setColor(Color.black);
            
            x[i] = (int)(sx);
            y[i] = (int)(sy);
            segundos[i].drawLine((int)(x[i]*.98)+200, (int)(y[i]*.98)+200,(int)sx+200, (int)sy+200);
            
            if(i % 5 == 0){
                numero[j] = (Graphics2D)g;
                if (j==0)
                    numero[j].drawString(""+12, (int)(sx*.90)+200, (int)(sy*.90)+200);
                else
                    numero[j].drawString(""+j, (int)(sx*.90)+200, (int)(sy*.90)+200);
                j++;
                
            }
            
            angulo += 6;
        }
        //System.out.println(200+sx + " " + 200+sy);
        //int h;
        g2d.setColor(Color.red);
        g2d.drawLine(200, 200, (int)(x[seg-1]*.98)+200, (int)(y[seg-1]*.98)+200); 
        minutero.setColor(Color.red);
        //minutero.drawLine(200, 200, x[min-1], y[min-1]);
        minutero.drawLine(200, 200, (int)(x[min-1]*.80)+200, (int)(y[min-1]*.85)+200);
        if(min <= 12) h = (5*hora+1)-1;
        else if(min > 12 && min <= 24) h = (5*hora+2)-1;
        else if(min > 24 && min <= 36) h = (5*hora+3)-1;
        else if(min > 36 && min <= 48) h = (5*hora+4)-1;
        else if(min > 48 && min <= 60) h = (5*hora+5)-1;       
        
        horario.setColor(Color.red);
        horario.drawLine(200, 200, (int)(x[h]*.5)+200, (int)(y[h]*.5)+200);
        
        if(seg == 60) min ++;
        
        if(min == 61){
            min = 1;
            hora ++;
        }       
        if(min == 11 || min == 23 || min == 35 || min == 47 || min == 59){
            h++;
        }
    }
}