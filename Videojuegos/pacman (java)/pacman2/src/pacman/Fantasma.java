/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pacman;

import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Rectangle;
import java.awt.image.BufferedImage;
import java.util.Random;

/**
 *
 * @author Armando Isaac
 */
public class Fantasma {
    private int posx, posy, x, y;//posiciones de los fantasmas (3 fantasmas)
    private Laberinto lab;
    private int [] caminosV;
    private int [] caminosH;
    private boolean [] direccion = new boolean[4];
    private int [][] esquinas;
    private BufferedImage imagen;
    private Random rand = new Random();
    private static final int DIAMETER = 30;
    
    
    public Fantasma(Laberinto lab, int [] caminosV, int [] caminosH, int [][] esquinas, int x, int y, BufferedImage img){
        this.lab = lab;
        this.caminosV = caminosV;
        this.caminosH = caminosH;
        this.esquinas = esquinas;
        imagen = img;
        //direcciones del recorrido de cada fantasma
        //  arriba                 abajo                 izquierda              derecha 
        direccion[0] = false; direccion[1] = true; direccion[2] = false; direccion[3] = false;
        posx = x; posy = y; // coordenadas iniciales   
        this.x=0; this.y=0;
        
        
    }
    
    public void paint (Graphics2D g){
        
        g.drawImage(imagen, posx, posy, 30, 30, null);
        
    }
    
    public int getPosX(){return posx;}
    public int getPosY(){return posy;}
    
   
    
    int dir;
    int random;
    
    public void move(){
        posx += x;
        posy += y;
        
        for(int i = 0; i < 12; i++){
            if(posx == esquinas[i][0] && posy == esquinas[i][1]){              
                
                do{
                    random = rand.nextInt(4)+2;                    
                }while(esquinas[i][random]==0);
                
                if(esquinas[i][random] == 1){
                    y=-1; x=0;
                }
                if(esquinas[i][random] == 2){
                    y=1; x=0;
                }
                if(esquinas[i][random] == 3){
                    x=-1; y=0;
                    
                }
                if(esquinas[i][random] == 4){
                    x=1; y=0;
                    
                }
            }
        }
        if(posx < -40 && posy == caminosV[1]){posx = 800;}
        if(posx > 800 && posy == caminosV[1]){posx = -40;}
        
    }
    
    
}
