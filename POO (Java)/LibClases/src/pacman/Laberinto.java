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
import java.awt.event.*;
import java.awt.image.BufferedImage;
import java.io.IOException;
import javax.imageio.ImageIO;
import javax.swing.*;

/**
 *
 * @author Armando Isaac
 */
public class Laberinto extends JPanel {
    
    private Pac pacman;
    private Fantasma [] fantasma = new Fantasma[4];
    
    int [] caminosH;//coordenadas de los caminos en Horizontal (ejes X)
    int [] caminosV;//coordenadas de los caminos en Vertical (ejes Y)
    
    int [][] esquinas;
    private BufferedImage rojo, azul, amarillo, rosa, pac, pacArriba, pacAbajo, pacIzq, pacDer;
    
    private boolean gana, pierde;
    
    
    //matriz de coordenadas de los puntos
    
    private int [][] v1 = new int[25][2];
    private int [][] v2 = new int[25][2];
    private int [][] v3 = new int[25][2];
    private int [][] v4 = new int[25][2];

    private int [][] h1 = new int[33][2];
    private int [][] h2 = new int[33][2];
    private int [][] h3 = new int[33][2];
    
    private int score;
    
    
    public Laberinto(){
        addKeyListener(new Controls());
        setFocusable(true);
        this.setBackground(Color.black); 
        
        pierde = false;
        gana = false;
               
        //coordenadas estáticas de los caminos horizontales
        caminosH = new int[4];        
        caminosH[0] = 40; caminosH[1] = 260; caminosH[2] = 480; caminosH[3] = 700;
        //coordenadas estáticas de los caminos verticales
        caminosV = new int[3];        
        caminosV[0] = 10; caminosV[1] = 260; caminosV[2] = 510;
        
        score = 199;
        
        BufferedImage [] imagen = new BufferedImage[5];
        
        try{
            //texturas de fantasmas
            rojo = ImageIO.read(getClass().getResourceAsStream("rojo.png"));
            amarillo = ImageIO.read(getClass().getResourceAsStream("amarillo.png"));
            azul = ImageIO.read(getClass().getResourceAsStream("azul.png"));
            rosa = ImageIO.read(getClass().getResourceAsStream("rosa.png"));
            //textura de pacman
            imagen[0] = ImageIO.read(getClass().getResourceAsStream("pac.png"));
            imagen[1] = ImageIO.read(getClass().getResourceAsStream("pacArriba.png"));
            imagen[2] = ImageIO.read(getClass().getResourceAsStream("pacAbajo.png"));
            imagen[3] = ImageIO.read(getClass().getResourceAsStream("pacIzq.png"));
            imagen[4] = ImageIO.read(getClass().getResourceAsStream("pacDer.png"));
            
            
        }
        catch(IOException ex){
            ex.printStackTrace();
        }
        repaint();
        
        esquinas = new int [12][6];
        
        //coordenadas de todas las esquinas del laberinto
        esquinas[0][0] = caminosH[0]; esquinas[0][1] = caminosV[0]; esquinas[0][2]=0; esquinas[0][3]=2; esquinas[0][4]=0; esquinas[0][5]=4;
        esquinas[1][0] = caminosH[0]; esquinas[1][1] = caminosV[1]; esquinas[1][2]=1; esquinas[1][3]=2; esquinas[1][4]=3; esquinas[1][5]=4;
        esquinas[2][0] = caminosH[0]; esquinas[2][1] = caminosV[2]; esquinas[2][2]=1; esquinas[2][3]=0; esquinas[2][4]=0; esquinas[2][5]=4;
        
        esquinas[3][0] = caminosH[1]; esquinas[3][1] = caminosV[0]; esquinas[3][2]=0; esquinas[3][3]=2; esquinas[3][4]=3; esquinas[3][5]=4;
        esquinas[4][0] = caminosH[1]; esquinas[4][1] = caminosV[1]; esquinas[4][2]=1; esquinas[4][3]=2; esquinas[4][4]=3; esquinas[4][5]=4;
        esquinas[5][0] = caminosH[1]; esquinas[5][1] = caminosV[2]; esquinas[5][2]=1; esquinas[5][3]=0; esquinas[5][4]=3; esquinas[5][5]=4;
        
        esquinas[6][0] = caminosH[2]; esquinas[6][1] = caminosV[0]; esquinas[6][2]=0; esquinas[6][3]=2; esquinas[6][4]=3; esquinas[6][5]=4;
        esquinas[7][0] = caminosH[2]; esquinas[7][1] = caminosV[1]; esquinas[7][2]=1; esquinas[7][3]=2; esquinas[7][4]=3; esquinas[7][5]=4;
        esquinas[8][0] = caminosH[2]; esquinas[8][1] = caminosV[2]; esquinas[8][2]=1; esquinas[8][3]=0; esquinas[8][4]=3; esquinas[8][5]=4;
        
        esquinas[9][0] = caminosH[3]; esquinas[9][1] = caminosV[0]; esquinas[9][2]=0; esquinas[9][3]=2; esquinas[9][4]=3; esquinas[9][5]=0;
        esquinas[10][0] = caminosH[3]; esquinas[10][1] = caminosV[1]; esquinas[10][2]=1; esquinas[10][3]=2; esquinas[10][4]=3; esquinas[10][5]=4;
        esquinas[11][0] = caminosH[3]; esquinas[11][1] = caminosV[2]; esquinas[11][2]=1; esquinas[11][3]=0; esquinas[11][4]=3; esquinas[11][5]=0;
        
        //se crea el pacman
        pacman = new Pac(this, caminosV, caminosH, caminosH[1], caminosV[2], imagen);
        //se crean los fantasmas
        fantasma[0] = new Fantasma(this, caminosV, caminosH, esquinas, caminosH[0], caminosV[0], rojo);
        fantasma[1] = new Fantasma(this, caminosV, caminosH, esquinas, caminosH[1], caminosV[0], amarillo);
        fantasma[2] = new Fantasma(this, caminosV, caminosH, esquinas, caminosH[2], caminosV[0], azul);
        fantasma[3] = new Fantasma(this, caminosV, caminosH, esquinas, caminosH[3], caminosV[0], rosa);
        
        int j = 25;
        for(int i = 0; i < 25; i++){
            v1[i][0] = caminosH[0]+15;
            v1[i][1] = j;
            v2[i][0] = caminosH[1]+15;
            v2[i][1] = j;
            v3[i][0] = caminosH[2]+15;
            v3[i][1] = j;
            v4[i][0] = caminosH[3]+15;
            v4[i][1] = j;
            j+=20;
        }
        j = 55;
        for(int i = 0; i < 33; i++){
            h1[i][0] = j;
            h1[i][1] = caminosV[0]+15;
            
            h2[i][0] = j;
            h2[i][1] = caminosV[1]+15;
            
            h3[i][0] = j;
            h3[i][1] = caminosV[2]+15;
            
            j+=20;
        }
    }
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        
        Graphics2D [] paredes = new Graphics2D[12]; //se crea un arreglo para dibujar todas las paredes 
        
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);   
        
        g2d.setColor(Color.red);
        g2d.drawString("SCORE: " + (199-score)*10, 350, 150);
        
        if(gana == true){
            g2d.setColor(Color.red);
            g2d.drawString("¡¡   GANASTE  ¡¡", 350, 200);
        }
        if(pierde == true){
            g2d.setColor(Color.red);
            g2d.drawString("F R A C A S A D O", 340, 200);
        }
        
        
        
        int j = 25;
        for(int i = 0; i < 25; i++){
            g2d = (Graphics2D)g;
            g2d.setColor(Color.yellow);
            g2d.fillOval(v1[i][0], v1[i][1], 5, 5);
            
            
            g2d = (Graphics2D)g;
            g2d.setColor(Color.yellow);
            g2d.fillOval(v2[i][0], v2[i][1], 5, 5);  
            
            g2d = (Graphics2D)g;
            g2d.setColor(Color.yellow);
            g2d.fillOval(v3[i][0], v3[i][1], 5, 5);
            
            g2d = (Graphics2D)g;
            g2d.setColor(Color.yellow);
            g2d.fillOval(v4[i][0], v4[i][1], 5, 5);
            
        }
        j = 55;
        for(int i = 0; i < 33; i++){
            g2d = (Graphics2D)g;
            g2d.setColor(Color.yellow);
            g2d.fillOval(h1[i][0],h1[i][1], 5, 5);
            
            g2d = (Graphics2D)g;
            g2d.setColor(Color.yellow);
            g2d.fillOval(h2[i][0],h2[i][1], 5, 5);
            
            g2d = (Graphics2D)g;
            g2d.setColor(Color.yellow);
            g2d.fillOval(h3[i][0],h3[i][1], 5, 5);
            
            j+=20;
        }
        
        //se dibuja el pacman en el laberinto
        pacman.paint(g2d);
        //se dibujan los fantasmas en el laberinto
        fantasma[0].paint(g2d);
        fantasma[1].paint(g2d);
        fantasma[2].paint(g2d);
        fantasma[3].paint(g2d);
        
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
        pacman.move();
        fantasma[0].move();
        fantasma[1].move();
        fantasma[2].move();
        fantasma[3].move();
        
        for(int i = 0; i < 4; i++){
            if(fantasma[i].getPosX() > pacman.getPacX()){
                if(pacman.getPacX() >= fantasma[i].getPosX()-10 && pacman.getPacY() == fantasma[i].getPosY())
                    pierde = true;
            }
            if(fantasma[i].getPosX() < pacman.getPacX()){
                if(fantasma[i].getPosX() >= pacman.getPacX()-10 && pacman.getPacY() == fantasma[i].getPosY())
                    pierde = true;
            }
            if(fantasma[i].getPosY() > pacman.getPacY()){
                if(pacman.getPacY() >= fantasma[i].getPosY()-10 && pacman.getPacX() == fantasma[i].getPosX())
                    pierde = true;
            }
            if(fantasma[i].getPosY() < pacman.getPacY()){
                if(fantasma[i].getPosY() >= pacman.getPacY()-10 && pacman.getPacX() == fantasma[i].getPosX())
                    pierde = true;
            }
            
        }
        for(int i = 0; i < 25; i++){            
            if(pacman.getPacX() == caminosH[0]){
                if(pacman.getPacY() == v1[i][1]){
                    v1[i][1]=1000;
                    score--;
                }
            }
            if(pacman.getPacX() == caminosH[1]){
                if(pacman.getPacY() == v2[i][1]){
                    v2[i][1]=1000;
                    score--;
                }
            }
            if(pacman.getPacX() == caminosH[2]){
                if(pacman.getPacY() == v3[i][1]){
                    v3[i][1]=1000;
                    score--;
                }
            }
            if(pacman.getPacX() == caminosH[3]){
                if(pacman.getPacY() == v4[i][1]){
                    v4[i][1]=1000;
                    score--;
                }
            }
        }
        for(int i = 0; i < 33; i++){
            if(pacman.getPacY() == caminosV[0]){
                if(pacman.getPacX() == h1[i][0]/* && pacman.getPacX()+15 == v1[0][0]*/){
                    h1[i][0]=1000;
                    score--;
                }
            }
            if(pacman.getPacY() == caminosV[1]){
                if(pacman.getPacX() == h2[i][0]/* && pacman.getPacX()+15 == v1[0][0]*/){
                    h2[i][0]=1000;
                    score--;
                }
            }
            if(pacman.getPacY() == caminosV[2]){
                if(pacman.getPacX() == h3[i][0]/* && pacman.getPacX()+15 == v1[0][0]*/){
                    h3[i][0]=1000;
                    score--;
                }
            }
        }
        
        if(score <= 0){gana = true;}//fin del juego
        
        
        
    }
    public void run() {
        while (true) {
            if(pierde == false && gana == false)move();
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
            pacman.keyPressed(e);
        }

        @Override
        public void keyReleased(KeyEvent e) {
            
        }

    }
    public boolean getJuego(){return pierde;}
}
