/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package pacman;
import java.awt.Color;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.*;

/**
 *
 * @author Armando Isaac
 */
public class Laberinto extends JPanel {
    
    int pacx, pacy, x, y; // posisciones del pacman
    int fan1x, fan1y, fan2x, fan2y, fan3x, fan3y, fan4x, fan4y;//posiciones de los fantasmas (3 fantasmas)
    int [] caminosH;//coordenadas de los caminos en Horizontal (ejes X)
    int [] caminosV;//coordenadas de los caminos en Vertical (ejes Y)
    boolean [] dirFan1;
    boolean [] dirFan2;
    boolean [] dirFan3;
    boolean [] dirFan4;
    int [][] esquinas;
    
    
    public Laberinto(){
        addKeyListener(new Controls());
        setFocusable(true);
        this.setBackground(Color.black);       
               
        //coordenadas estáticas de los caminos horizontales
        caminosH = new int[4];        
        caminosH[0] = 40; caminosH[1] = 260; caminosH[2] = 480; caminosH[3] = 700;
        //coordenadas estáticas de los caminos verticales
        caminosV = new int[3];        
        caminosV[0] = 10; caminosV[1] = 260; caminosV[2] = 510;
        esquinas = new int [12][2];
        dirFan1 = new boolean[4];
        dirFan2 = new boolean[4];
        dirFan3 = new boolean[4];
        dirFan4 = new boolean[4];
        
        //coordenadas de todas las esquinas del laberinto
        esquinas[0][0] = caminosH[0]; esquinas[0][1] = caminosV[0];
        esquinas[1][0] = caminosH[0]; esquinas[1][1] = caminosV[1];
        esquinas[2][0] = caminosH[0]; esquinas[2][1] = caminosV[2];
        
        esquinas[3][0] = caminosH[1]; esquinas[3][1] = caminosV[0];
        esquinas[4][0] = caminosH[1]; esquinas[4][1] = caminosV[1];
        esquinas[5][0] = caminosH[1]; esquinas[5][1] = caminosV[2];
        
        esquinas[6][0] = caminosH[2]; esquinas[6][1] = caminosV[0];
        esquinas[7][0] = caminosH[2]; esquinas[7][1] = caminosV[1];
        esquinas[8][0] = caminosH[2]; esquinas[8][1] = caminosV[2];
        
        esquinas[9][0] = caminosH[3]; esquinas[9][1] = caminosV[0];
        esquinas[10][0] = caminosH[3]; esquinas[10][1] = caminosV[1];
        esquinas[11][0] = caminosH[3]; esquinas[11][1] = caminosV[2];
        
        pacx = caminosH[1];//coordenada inicial en X
        pacy = caminosV[2];//coordenada inicial en Y
        
        //coordenadas iniciales de los fantasmas
        fan1x = caminosH[0]; fan1y = caminosV[0];
        fan2x = caminosH[1]; fan2y = caminosV[0];
        fan3x = caminosH[2]; fan3y = caminosV[0];
        fan4x = caminosH[3]; fan4y = caminosV[0];
        //direcciones del recorrido de cada fantasma
        //  arriba             abajo             izquierda            derecha                 
        dirFan1[0] = false; dirFan1[1] = true; dirFan1[2] = false; dirFan1[3] = false;
        dirFan2[0] = false; dirFan2[1] = true; dirFan2[2] = false; dirFan2[3] = false;
        dirFan3[0] = false; dirFan3[1] = true; dirFan3[2] = false; dirFan3[3] = false;
        dirFan4[0] = false; dirFan4[1] = true; dirFan4[2] = false; dirFan4[3] = false;
        
        
        
        //valores de los incrementos de las coordenadas del pacman
        x = 0; y = 0;
    }
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        
        Graphics2D [] paredes = new Graphics2D[12]; //se crea un arreglo para dibujar todas las paredes       
        Graphics2D pacman = (Graphics2D)g;//se crea el pacman
        Graphics2D [] fantasma = new Graphics2D[4];//se crean los fantasmas
        
        
        
        //caracteristicas del pacman
        pacman.setColor(Color.yellow);
        pacman.fillOval(pacx, pacy, 30, 30);  
        //caracteristicas del fantasma rojo
        //pacman.setColor(Color.red);
        //pacman.fillOval(fan1x, fan1y, 30, 30);  
        
        int ladoV = (getHeight()-50)/2;
        int ladoH = (getWidth()-260)/3;
        
        //pared
        paredes[0]=(Graphics2D)g;
        paredes[0].setColor(Color.blue);
        paredes[0].drawRect(0, 0, 30, 250);
        //pared
        paredes[1]=(Graphics2D)g;
        paredes[1].setColor(Color.blue);
        paredes[1].drawRect(0, 300, 30, 250);
        //pared
        paredes[2]=(Graphics2D)g;
        paredes[2].setColor(Color.blue);
        paredes[2].drawRect(80, 50, 170, 200);
        //pared
        paredes[3]=(Graphics2D)g;
        paredes[3].setColor(Color.blue);
        paredes[3].drawRect(300, 50, 170, 200);
        //pared
        paredes[4]=(Graphics2D)g;
        paredes[4].setColor(Color.blue);
        paredes[4].drawRect(520, 50, 170, 200);
        //pared
        paredes[5]=(Graphics2D)g;
        paredes[5].setColor(Color.blue);
        paredes[5].drawRect(80, 300, 170, 200);
        //pared
        paredes[6]=(Graphics2D)g;
        paredes[6].setColor(Color.blue);
        paredes[6].drawRect(300, 300, 170, 200);
        //pared
        paredes[7]=(Graphics2D)g;
        paredes[7].setColor(Color.blue);
        paredes[7].drawRect(520, 300, 170, 200);
        //pared
        paredes[8]=(Graphics2D)g;
        paredes[8].setColor(Color.blue);
        paredes[8].drawRect(740, 0, 30, 250);
        //pared
        paredes[9]=(Graphics2D)g;
        paredes[9].setColor(Color.blue);
        paredes[9].drawRect(740, 300, 30, 250);
        
    }
    public void move() {
        int ladoV = (getHeight()-50)/2;
        int ladoH = (getWidth()-260)/3;
        
        pacx += x;
        pacy += y;
        
        //caminos en vertical
        if(pacx == caminosH[0] || (pacx <= caminosH[0] && pacy != caminosV[1]) || pacx == caminosH[1] || 
           pacx == caminosH[2] || (pacx >= caminosH[3] && pacy != caminosV[1]) || pacx == caminosH[3])
            x=0; 
        //caminos en horizontal
        if(pacy <= caminosV[0] || pacy == caminosV[1] || pacy >= caminosV[2])
            y=0;
        
        //movimiento de los fantasmas
        if(dirFan2[0] == true/*abajo*/){   
            if(fan1x == caminosH[0] || fan1x == caminosH[1] || fan1x == caminosH[2] || fan1x == caminosH[3]){
                fan1y++; fan1x=0;
            }
        }
        
        
        
        //System.out.println(pacx);
    }
    public void run() {
        while (true) {
            move();
            repaint();
            try {
                Thread.sleep(6L);
            } catch (Exception ex) {

            }

        }
    }
    class Controls implements KeyListener {

        @Override
        public void keyTyped(KeyEvent e) {
            
        }

        @Override
        public void keyPressed(KeyEvent e) {
            if (e.getKeyCode() == KeyEvent.VK_LEFT) {
                if(pacx > caminosH[0] && (pacy == caminosV[0] || pacy == caminosV[1] || pacy >= caminosV[2]) || pacy == caminosV[1]){
                    x=-1;y=0; 
                }
            }
            if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
                if(pacx < caminosH[3] && (pacy == caminosV[0] || pacy == caminosV[1] || pacy >= caminosV[2]) || pacy == caminosV[1]){
                    x=1;y=0; 
                }
            }
            if (e.getKeyCode() == KeyEvent.VK_UP) {
                if(pacy > caminosV[0] && (pacx == caminosH[0] || pacx == caminosH[1] || pacx == caminosH[2] || pacx == caminosH[3])){
                    y=-1;x=0;
                }
            }
            if (e.getKeyCode() == KeyEvent.VK_DOWN) {
                if(pacy < caminosV[2] && (pacx == caminosH[0] || pacx == caminosH[1] || pacx == caminosH[2] || pacx == caminosH[3])){
                    y=+1;x=0;
                }
            }
        }

        @Override
        public void keyReleased(KeyEvent e) {
            
        }

    }
}
