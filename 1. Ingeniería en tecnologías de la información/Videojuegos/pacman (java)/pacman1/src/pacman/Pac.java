/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pacman;

import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;

/**
 *
 * @author Armando Isaac
 */
public class Pac{
    private int posx, posy;
    Graphics2D g;
    
    Pac(int posx, int posy, Graphics2D g){
        this.posx = posx;
        this.posy = posy;
        this.g = g;
        
    }
    public void dibujar(){
        Graphics2D pacman = g;
        pacman.setColor(Color.yellow);
        pacman.fillOval(posx, posy, 30, 30);
    }
    public int getPosX(){return posx;}
    public int getPosY(){return posy;}
    public void setPosX(int x){posx = x;}
    public void setPosY(int y){posx = y;}
}
