/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pacman;


import java.awt.*;
import java.awt.event.*;
import java.awt.image.BufferedImage;


/**
 *
 * @author Armando Isaac
 */
public class Pac {
    private int pacx, pacy, x = 0, y = 0; // posisciones del pacman
    private Laberinto lab;//se crea una instancia de la clase principal
    private int []caminosV; //caminos verticales de laberinto
    private int []caminosH;// caminos horizontales de laberinto
    private BufferedImage [] imagen; //arreglo para la textura del pacman
    private int numImg;
    
    
    public Pac(Laberinto lab, int [] caminosV, int [] caminosH, int x, int y, BufferedImage[] imagen){
        this.lab = lab;
        this.caminosV = caminosV;
        this.caminosH = caminosH;
        this.imagen = imagen;
        numImg = 0;
        pacx = x;
        pacy = y;
        
    }
    
    public void paint(Graphics2D g) {
        //se dubuja el pacman
        g.drawImage(imagen[numImg], pacx, pacy, 30, 30, null);
    }
    
    public int getPacX(){return pacx;}
    public int getPacY(){return pacy;}
    
    boolean pacCerrado = true;//define si el pacman cierra o abre
    int num;//indice del arreglo de imagenes
    
    public void move() {
        pacx += x;
        pacy += y;
        
        
        if(pacx % 25 == 0 || pacy % 25 == 0) pacCerrado = !pacCerrado;

        if(pacCerrado == true) numImg = 0;
        else numImg = num;
        
        //caminos en vertical
        if(pacx == caminosH[0] || (pacx <= caminosH[0] && pacy != caminosV[1]) || pacx == caminosH[1] || 
           pacx == caminosH[2] || (pacx >= caminosH[3] && pacy != caminosV[1]) || pacx == caminosH[3])
            x=0; 
        //caminos en horizontal
        if(pacy <= caminosV[0] || pacy == caminosV[1] || pacy >= caminosV[2])
            y=0; 
        
        if(pacx < -40)pacx = 800;
        if(pacx > 800)pacx = -40;
    }
    public void keyPressed(KeyEvent e) {
        if (e.getKeyCode() == KeyEvent.VK_LEFT) {
                if(pacx > caminosH[0] && (pacy == caminosV[0] || pacy == caminosV[1] || pacy >= caminosV[2]) || pacy == caminosV[1]){
                    x=-1;y=0; num = 3; 
                }
            }
            if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
                if(pacx < caminosH[3] && (pacy == caminosV[0] || pacy == caminosV[1] || pacy >= caminosV[2]) || pacy == caminosV[1]){
                    x=1;y=0; num = 4;
                }
            }
            if (e.getKeyCode() == KeyEvent.VK_UP) {
                if(pacy > caminosV[0] && (pacx == caminosH[0] || pacx == caminosH[1] || pacx == caminosH[2] || pacx == caminosH[3])){
                    y=-1;x=0; num = 1;
                }
            }
            if (e.getKeyCode() == KeyEvent.VK_DOWN) {
                if(pacy < caminosV[2] && (pacx == caminosH[0] || pacx == caminosH[1] || pacx == caminosH[2] || pacx == caminosH[3])){
                    y=+1;x=0; num = 2;
                }
            }
    }
    
}