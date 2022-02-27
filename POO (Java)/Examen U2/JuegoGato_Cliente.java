/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juegogato_cliente;
// Fig. 24.16: PruebaClienteTresEnRaya.java
// Prueba la clase ClienteTresEnRaya.
import javax.swing.JFrame;
import juego.gato.lib.Cliente;// Libreria donde se extraen las funciones para el cliente

/**
 *
 * @author Armando Isaac
 */
public class JuegoGato_Cliente {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Cliente aplicacion1, aplicacion2; // declara la aplicación cliente
        // si no hay argumentos de línea de comandos
        
        aplicacion1 = new Cliente( "127.0.0.1" ); // localhost
        aplicacion2 = new Cliente( "127.0.0.1" ); // localhost
        JFrame ap1 = new JFrame();
        
        aplicacion1.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        aplicacion2.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
    }    
}
