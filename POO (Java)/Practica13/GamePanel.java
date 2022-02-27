/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package edu.upv.poo;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class GamePanel extends JPanel {

    private Ball ball = new Ball(this);
    private Raquet raquet = new Raquet(this);

    public GamePanel() {
        addKeyListener(new Controls());
        setFocusable(true);
    }

    public void move() {
        getBall().move();
        getRaquet().move();
    }

    @Override
    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2d = (Graphics2D) g;
        g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);
        getBall().paint(g2d);
        getRaquet().paint(g2d);
    }

    public void run() {
        while (true) {
            move();
            repaint();
            try {
                Thread.sleep(10L);
            } catch (Exception ex) {

            }

        }
    }

    /**
     * @return the ball
     */
    public Ball getBall() {
        return ball;
    }

    /**
     * @return the raquet
     */
    public Raquet getRaquet() {
        return raquet;
    }

    class Controls implements KeyListener {

        @Override
        public void keyTyped(KeyEvent e) {

        }

        @Override
        public void keyPressed(KeyEvent e) {
            getRaquet().keyPressed(e);
        }

        @Override
        public void keyReleased(KeyEvent e) {
            getRaquet().keyReleased(e);
        }

    }

}
