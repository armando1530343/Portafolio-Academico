/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;

import java.awt.*;
import java.awt.event.*;

public class Raquet {

    private static final int y = 330;
    private static final int WIDTH = 60;
    private static final int HEIGTH = 10;
    private int x = 0;
    private int xa = 0;
    private GamePanel gamePanel;

    public Raquet(GamePanel gamePanel) {
        this.gamePanel = gamePanel;
    }

    public void paint(Graphics2D g) {
        g.fillRect(x, y, WIDTH, HEIGTH);
    }

    public Rectangle getBounds() {
        return new Rectangle(x, y, WIDTH, HEIGTH);
    }

    public int getTopY() {
        return y - HEIGTH;
    }

    public void move() {
        if (x + xa > 0 && x + xa < gamePanel.getWidth() - WIDTH) {
            x += xa;
        }

    }

    public void keyReleased(KeyEvent e) {
        xa = 0;
    }

    public void keyPressed(KeyEvent e) {
        if (e.getKeyCode() == KeyEvent.VK_LEFT) {
            xa -= 3;
        }
        if (e.getKeyCode() == KeyEvent.VK_RIGHT) {
            xa += 3;
        }
    }

}
