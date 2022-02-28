/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package conecta4;
import java.util.Scanner;

/**
 *
 * @author Armando Isaac
 */
public class Conecta4 {

    /**
     * @param args the command line arguments
     */
    public static void main(String[] args) {
        // TODO code application logic here
        
        Tablero tab;//'tab' es un objeto creado de la clase 'Tablero'
        
        //se llama al constructor de la clase con las dimensiones del nuevo tablero
        tab = new Tablero(6,8);//éste creará una matriz de 6 X 8
        
        
        Scanner leer = new Scanner(System.in);
        
        boolean turno = false;//se sabra el turno del jugador por cada inserción
        boolean theEnd = false;// 'theEnd:false'=el juego continua
                               // 'theEnd:true'=el juego termina
        int ficha;//numero de jugador (ya sea 1 ó 2)
        int columna;
        
        //este ciclo estara iterando mientras no halla un ganador
        do{
            turno = !turno;//por cada iteracion el valor del turno se niega
                            //puede ser solo true ó false
            if(turno==true)
                ficha=1;//en caso de turno=true el turno es del jugador 1
            else
                ficha=2;//en caso de turno=false el turno es del jugador 2
            
            System.out.println("Turno: Jugador "+ficha);//muestra el numero de jugador
            System.out.println("  Selecciona Posicion");
            
            //ingresa una columnna dentro del rango adecuado
            do{System.out.print("  Columna: ");columna = leer.nextInt();}while(columna<1||columna>8);
            
            //'theEnd' recibe un valor boleano que devuelve la funcion de insertar
            //en caso de devolver un true es que ya hubo un ganador de lo contrario continuará
            theEnd = tab.inserta(columna, ficha);
            tab.mostrar();//muestra los valores del tablero                        
        }
        while(theEnd==false);//en caso de ser true se sale del ciclo y el juego termina
        System.out.println("\nGanador: Jugador "+ficha);  //muestra al ganador de la partida      
    }    
}
