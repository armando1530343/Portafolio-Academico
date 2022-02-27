package edu.upv.poo;

import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.util.ArrayList;

public class Paint extends JPanel implements ActionListener{
    
    //Se crean las instancias de los botones
    JButton btnExit = new JButton("Exit");
    JButton btnLine = new JButton("Linea");
    JButton btnRect = new JButton("Rectangulo");
    JButton btnPen = new JButton("Lapiz");
    
    //ArrayList para almacenar los puntos, el lapiz
    private final ArrayList<Point> points;
  
    //Dos ArrayList para almacenar los puntos de las lineas
    private final ArrayList<Point> line1;
    private final ArrayList<Point> line2;
    
    //Dos ArrayList para almacenar los puntos del rectangulo
    private final ArrayList<Point> rec1;
    private final ArrayList<Point> rec2;

    //Para Guardar los puntos cuando se da clic y cuando se suelta
    private Point pt1;
    private Point pt2;
    
    //Opcion para guardar el tipo de trazo que se desea pintar
    private int tipoTrazo = 1;
    
    //contructor que inicializa los arraylist
    
    public Paint(){
        points = new ArrayList<>();
        
        line1 = new ArrayList<>();
        line2 = new ArrayList<>();
        
        rec1 = new ArrayList<>();
        rec2 = new ArrayList<>();

        
        addMouseMotionListener(new MouseHandler() );
        addMouseListener(new MouseMove() );
        
        //Dibuja los botones (esta detallada mas abajo)
        dibujarBotones();
    }
    
    @Override
    public void paintComponent(Graphics g){
        super.paintComponent(g);
        
        //LAPIZ    
        for (int i = 0; i < points.size(); i++) {
            g.fillOval((int)points.get(i).x, points.get(i).y, 5, 5);
        }
        
        //LINEA
        if(tipoTrazo == 2){
            g.drawLine(pt1.x, pt1.y, pt2.x, pt2.y);
        }
        
        for (int i = 0; i < line1.size(); i++) {
            g.drawLine(line1.get(i).x, line1.get(i).y, line2.get(i).x, line2.get(i).y);
        }
        
        //RECTANGULO:
        if(tipoTrazo == 3){
            g.drawLine(pt1.x, pt1.y, pt2.x, pt1.y);
            g.drawLine(pt2.x, pt1.y, pt2.x, pt2.y);
            g.drawLine(pt2.x, pt2.y, pt1.x, pt2.y);
            g.drawLine(pt1.x, pt2.y, pt1.x, pt1.y);  
        }
        
        for (int i = 0; i < rec1.size(); i++) {
            g.drawLine(rec1.get(i).x, rec1.get(i).y, rec2.get(i).x, rec1.get(i).y);
            g.drawLine(rec2.get(i).x, rec1.get(i).y, rec2.get(i).x, rec2.get(i).y);
            g.drawLine(rec2.get(i).x, rec2.get(i).y, rec1.get(i).x, rec2.get(i).y);
            g.drawLine(rec1.get(i).x, rec2.get(i).y, rec1.get(i).x, rec1.get(i).y);
        } 
        
    }
    
    class MouseHandler implements MouseMotionListener{
        @Override
        public void mouseDragged(MouseEvent me) {
            
            if(tipoTrazo == 1){
                points.add(me.getPoint());
            }
            
            if(tipoTrazo == 2 || tipoTrazo == 3 ){
                pt2 = me.getPoint();
            }
            
            repaint();
            
        }

        @Override
        public void mouseMoved(MouseEvent me) {
           
        }
        
    }
    
    class MouseMove implements MouseListener{
        
        @Override
        public void mousePressed(MouseEvent e) {
            
            if(tipoTrazo == 2 || tipoTrazo == 3 ){
                pt1 = e.getPoint();
            }            

        }
        
        @Override
        public void mouseReleased(MouseEvent e) {
            
            if(tipoTrazo == 2){
                line1.add(pt1);
                line2.add(pt2);
            }
            
            if(tipoTrazo == 3){
                rec1.add(pt1);
                rec2.add(pt2);
            }
            
        }
        
        @Override
        public void mouseClicked(MouseEvent e) {
            
        }
        @Override
        public void mouseEntered(MouseEvent e) {
            
        }
        @Override
        public void mouseExited(MouseEvent e) {
            
        }
        
    }
    
    public void dibujarBotones(){
        setLayout(null);
        
        btnExit.setBounds(700,470,100,30);
        btnExit.addActionListener((ActionListener) this);
        add(btnExit);
        
        btnLine.setBounds(200, 10, 100, 30);
        btnLine.addActionListener((ActionListener) this);
        add(btnLine);
        
        btnRect.setBounds(300, 10, 150, 30);
        btnRect.addActionListener((ActionListener) this);
        add(btnRect);
        
        btnPen.setBounds(450, 10, 100, 30);
        btnPen.addActionListener((ActionListener) this);
        add(btnPen);
    }
    
    //Dependiendo del boton, es la opcion que se dibujará
    @Override
    public void actionPerformed(ActionEvent e) {
        
        
        if(e.getSource()== btnExit){
            System.exit(0);
        }
        
        if(e.getSource() == btnLine){
            tipoTrazo = 2;
        }
        
        if(e.getSource() == btnRect){
            tipoTrazo = 3;
        }
        
        if(e.getSource() == btnPen){
            tipoTrazo = 1;
        }
    }

}