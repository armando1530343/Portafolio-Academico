package edu.upv.poo;

import java.awt.*;
import javax.swing.*;

public class Ball {

    private int ya = 1;
    private int x = 0;
    private int xa = 1;
    private int y = 0;
    private static final int DIAMETER = 30;
    private GamePanel gamePanel;

    public Ball(GamePanel gamePanel) {
        this.gamePanel = gamePanel;
    }

    public void paint(Graphics2D g) {
        g.fillOval(x, y, DIAMETER, DIAMETER);
    }

    public void move() {
        if (x + xa < 0) {
            xa = 1;
        }
        if (x + xa > gamePanel.getWidth() - DIAMETER) {
            xa = -1;
        }
        if (y + ya < 0) {
            ya = 1;
        }
        if (y + ya > gamePanel.getHeight() - DIAMETER) {
            ya = -1;
        }

        if (collision()) {
            ya = -1;
            y = gamePanel.getRaquet().getTopY() - DIAMETER;
        }
        if (y > gamePanel.getHeight() - (DIAMETER + 1)) {
            // TODO fin del juego
            y = 0;
            x = 0;

        }
        y += ya;
        x += xa;
    }

    public Rectangle getBounds() {
        return new Rectangle(x, y, DIAMETER, DIAMETER);
    }

    public boolean collision() {
        return gamePanel.getRaquet().getBounds().intersects(getBounds());
    }

}
