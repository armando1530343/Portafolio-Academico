/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juegogato_servidor;
import javax.swing.JFrame;
import juego.gato.lib.Servidor; // Libreria donde se extraen las funciones para el servidor
/**
 *
 * @author Armando Isaac
 */
public class JuegoGato_Servidor {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        Servidor aplicacion = new Servidor();
        aplicacion.setDefaultCloseOperation( JFrame.EXIT_ON_CLOSE );
        aplicacion.execute();
        
    }
    
}
