/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juego.gato.lib;

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.GridLayout;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.io.IOException;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Formatter;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import javax.swing.JFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;

/**
 *
 * @author Armando Isaac
 * 
 * Esta clase creara las funciones para el cliente al momento de jugar conectado al servidor
 */
public class Cliente extends JFrame implements Runnable{
    private JTextField campoId; // campo de texto para mostrar la marca del jugador
    private JTextArea areaPantalla; // objeto JTextArea para mostrar la salida
    private JPanel panelTablero; // panel para el tablero de tres en raya
    private JPanel panel2; // panel que contiene el tablero
    private Cuadro tablero[][]; // tablero de tres en raya
    private Cuadro cuadroActual; // el cuadro actual
    private Socket conexion; // conexión con el servidor
    private Scanner entrada; // entrada del servidor
    private Formatter salida; // salida al servidor
    private String hostTresEnRaya; // nombre de host para el servidor
    private String miMarca; // la marca de este cliente
    private boolean miTurno; // determina de qué cliente es el turno
    private final String MARCA_X = "X"; // marca para el primer cliente
    private final String MARCA_O = "O"; // marca para el segundo cliente
    private int matriz[][];
    private int ganador;
    
    
    // establece la interfaz de usuario y el tablero
    public Cliente( String host )
    {
        setTitle("Gato");
        //this.setLocationRelativeTo(null);
        //this.setLayout(null);
        //this.setResizable(false);
        this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        
        hostTresEnRaya = host; // establece el nombre del servidor
        areaPantalla = new JTextArea(4, 30); // establece objeto JTextArea
        areaPantalla.setBackground(Color.GREEN);
        areaPantalla.setEditable( false );
        add( new JScrollPane( areaPantalla ), BorderLayout.SOUTH );
        panelTablero = new JPanel(); // establece panel para los cuadros en el tablero
        panelTablero.setLayout( new GridLayout( 3, 3, 0, 0 ) );
        //panelTablero.setSize(30, 30);
        //panelTablero.setBackground(Color.GREEN);
        tablero = new Cuadro[ 3 ][ 3 ]; // crea el tablero
        matriz = new int [3][3];
        ganador=0;
        int i, j;
        for( i = 0; i < 3; i++){
            for( j = 0; j < 3; j++){
                matriz[i][j]=0;
            }
        }

        // itera a través de las filas en el tablero
        for ( int fila = 0; fila < tablero.length; fila++ )
        {
        // itera a través de las columnas en el tablero
            for ( int columna = 0; columna < tablero[ fila ].length; columna++ )
            {
                // crea un cuadro
                tablero[ fila ][ columna ] = new Cuadro( " ", fila * 3 + columna );
                panelTablero.add( tablero[ fila ][ columna ] ); // agrega el cuadro
            } // fin de for interior
        } // fin de for exterior

        campoId = new JTextField(); // establece campo de texto
        campoId.setEditable( false );
        add( campoId, BorderLayout.NORTH );

        panel2 = new JPanel(); // establece el panel que contiene a panelTablero
        //panel2.setSize(30,10);
        panel2.setBackground(Color.RED);
        panel2.add( panelTablero, BorderLayout.CENTER ); // agrega el panel del tablero
        add( panel2, BorderLayout.CENTER ); // agrega el panel contenedor

        setSize( 600, 600 ); // establece el tamaño de la ventana
        setVisible( true ); // muestra la ventana
        //this.setBackground(Color.RED);

        iniciarCliente();
    } // fin del constructor de ClienteTresEnRaya
    // inicia el subproceso cliente
    public final void iniciarCliente()
    {
        try // se conecta al servidor, obtiene los flujos e inicia subproceso de salida
        {
            // realiza conexión con el servidor
            conexion = new Socket(InetAddress.getByName( hostTresEnRaya ), 12345);

            // obtiene flujos para entrada y salida
            entrada = new Scanner( conexion.getInputStream() );
            salida = new Formatter( conexion.getOutputStream() );
        } // fin de try
        catch ( IOException excepcionES )
        {
            excepcionES.printStackTrace();
        } // fin de catch
         // crea e inicia subproceso trabajador para este cliente
        ExecutorService trabajador = Executors.newFixedThreadPool( 1 );
        trabajador.execute( this ); // ejecuta el cliente
    } // fin del método iniciarCliente

    // subproceso de control que permite la actualización continua de areaPantalla
    @Override
    public void run()
    {
        miMarca = entrada.nextLine(); // obtiene la marca del jugador (X o O)
        /*SwingUtilities.invokeLater(
            new Runnable()
            {
                public void run()
                {
                    // muestra la marca del jugador
                    campoId.setText( "Usted es el jugador \"" + miMarca + "\"" );
                } // fin del método run
            } // fin de la clase interna anónima
        ); // fin de la llamada a SwingUtilities.invokeLater*/
        SwingUtilities.invokeLater(() -> {
            // muestra la marca del jugador
            campoId.setText( "Usted es el jugador \"" + miMarca + "\"" );
        } // fin del método run
        // fin de la clase interna anónima
        ); // fin de la llamada a SwingUtilities.invokeLater

        miTurno = ( miMarca.equals( MARCA_X ) ); // determina si es turno del cliente
        // recibe los mensajes que se envían al cliente y los imprime en pantalla
        while ( true )
        {
            if ( entrada.hasNextLine() )
            procesarMensaje( entrada.nextLine() );
        } // fin de while
    } // fin del método run

    // procesa los mensajes recibidos por el cliente
    private void procesarMensaje( String mensaje )
    {
        int fila=0, columna=0;
        String m="";
        // ocurrió un movimiento válido
        switch (mensaje) {
        // fin de if
            case "Movimiento valido.":
                mostrarMensaje( "Movimiento valido, por favor espere.\n" );
                establecerMarca( cuadroActual, miMarca ); // establece marca en el cuadro
                
                //JOptionPane.showConfirmDialog(null, m);
                break;
        // fin de else if
            case "Movimiento invalido, intente de nuevo":
                mostrarMensaje( mensaje + "\n" ); // muestra el movimiento inválido
                miTurno = true; // sigue siendo turno de este cliente
                break;
        // fin de else if
            case "El oponente realizo movimiento":
                int ubicacion = entrada.nextInt(); // obtiene la ubicación del movimiento
                entrada.nextLine(); // salta nueva línea después de la ubicación int
                //JOptionPane.showConfirmDialog(null, miMarca);
                fila = ubicacion / 3; // calcula la fila
                columna = ubicacion % 3; // calcula la columna
                establecerMarca( tablero[ fila ][ columna ],( miMarca.equals( MARCA_X ) ? MARCA_O : MARCA_X ) ); // marca el movimiento
                
                
                
                if (ubicacion == 0){
                    if(miMarca.equals(MARCA_O))matriz[0][0] = 1;
                    else matriz[0][0] = 2;  
                    //if(matriz[0][0] ==1 && matriz[1][0] ==1 )
                }
                else if (ubicacion == 1){
                    if(miMarca.equals(MARCA_O))matriz[0][1] = 1;
                    else matriz[0][1] = 2;            
                }
                else if (ubicacion == 2){
                    if(miMarca.equals(MARCA_O))matriz[0][2] = 1;
                    else matriz[0][2] = 2;            
                }
                else if (ubicacion == 3){
                    if(miMarca.equals(MARCA_O))matriz[1][0] = 1;
                    else matriz[1][0] = 2;            
                }
                else if (ubicacion == 4){
                    if(miMarca.equals(MARCA_O))matriz[1][1] = 1;
                    else matriz[1][1] = 2;            
                }
                else if (ubicacion == 5){
                    if(miMarca.equals(MARCA_O))matriz[1][2] = 1;
                    else matriz[1][2] = 2;            
                }
                else if (ubicacion == 6){
                    if(miMarca.equals(MARCA_O))matriz[2][0] = 1;
                    else matriz[2][0] = 2;            
                }
                else if (ubicacion == 7){
                    if(miMarca.equals(MARCA_O))matriz[2][1] = 1;
                    else matriz[2][1] = 2;            
                }
                else if (ubicacion == 8){
                    if(miMarca.equals(MARCA_O))matriz[2][2] = 1;
                    else matriz[2][2] = 2;            
                }
                //JOptionPane.showConfirmDialog(null, ubicacion + " " +matriz[0][0]);
                if(matriz[0][0] ==1 && matriz[1][0] ==1 && matriz[2][0] ==1||
                   matriz[1][0] ==1 && matriz[1][1] ==1 && matriz[1][2] ==1||
                   matriz[2][0] ==1 && matriz[2][1] ==1 && matriz[2][2] ==1||
                   matriz[0][0] ==1 && matriz[0][1] ==1 && matriz[0][2] ==1||
                   matriz[0][1] ==1 && matriz[1][1] ==1 && matriz[2][1] ==1||
                   matriz[0][2] ==1 && matriz[1][2] ==1 && matriz[2][2] ==1||
                   matriz[0][0] ==1 && matriz[1][1] ==1 && matriz[2][2] ==1||
                   matriz[0][2] ==1 && matriz[1][1] ==1 && matriz[2][0] ==1){
                    JOptionPane.showConfirmDialog(null, "Ganador: 'X'");
                    
                }
                if(matriz[0][0] ==2 && matriz[1][0] ==2 && matriz[2][0] ==2||
                   matriz[1][0] ==2 && matriz[1][1] ==2 && matriz[1][2] ==2||
                   matriz[2][0] ==2 && matriz[2][1] ==2 && matriz[2][2] ==2||
                   matriz[0][0] ==2 && matriz[0][1] ==2 && matriz[0][2] ==2||
                   matriz[0][1] ==2 && matriz[1][1] ==2 && matriz[2][1] ==2||
                   matriz[0][2] ==2 && matriz[1][2] ==2 && matriz[2][2] ==2||
                   matriz[0][0] ==2 && matriz[1][1] ==2 && matriz[2][2] ==2||
                   matriz[0][2] ==2 && matriz[1][1] ==2 && matriz[2][0] ==2)
                    JOptionPane.showConfirmDialog(null, "Ganador: 'O'");
                
                /*if(ubicacion == 0){
                    if (tablero[fila][columna].getMarca().equals(miMarca) &&
                        tablero[fila+1][columna].getMarca().equals(miMarca)/* ||
                        tablero[fila+1][columna+1].getMarca().equals(miMarca) &&
                        tablero[fila+2][columna+2].getMarca().equals(miMarca)||
                        tablero[fila][columna+1].getMarca().equals(miMarca) &&
                        tablero[fila][columna+2].getMarca().equals(miMarca)){
                        JOptionPane.showConfirmDialog(null, "Ganador: jugador " + miMarca);
                        
                    }
                }*/
                
                mostrarMensaje( "El oponente hizo un movimiento. Ahora es su turno.\n" );
                //JOptionPane.showConfirmDialog(null, tablero[fila][columna].getMarca());
                miTurno = true; // ahora es turno de este cliente
                break;
            default:
                mostrarMensaje( mensaje + "\n" ); // muestra el mensaje
                break;
        }
    } // fin del método procesarMensaje
    // manipula el objeto areaSalida en el subproceso despachador de eventos
    private void mostrarMensaje( final String mensajeAMostrar )
    {
        SwingUtilities.invokeLater(() -> {
            areaPantalla.append( mensajeAMostrar ); // actualiza la salida
        } // fin del método run
        // fin de la clase interna
        ); // fin de la llamada a SwingUtilities.invokeLater
    } // fin del método mostrarMensaje

    // método utilitario para establecer una marca en el tablero, en el subproceso despachador de eventos
    private void establecerMarca( final Cuadro cuadroAMarcar, final String marca )
    {
        SwingUtilities.invokeLater(() -> {
            cuadroAMarcar.establecerMarca(marca); // establece la marca en el cuadro
        } // fin del método run
        // fin de la clase interna anónima
        ); // fin de la llamada a SwingUtilities.invokeLater
    } // fin del método establecerMarca

    // envía un mensaje al servidor, indicando el cuadro en el que se hizo clic
    public void enviarCuadroClic( int ubicacion )
    {
        // si es mi turno
        if ( miTurno )
        {
            salida.format( "%d\n", ubicacion ); // envía la ubicación al servidor
            salida.flush();
            miTurno = false; // ya no es mi turno
        } // fin de if
    } // fin del método enviarCuadroClic

    // establece el cuadro actual
    public void establecerCuadroActual( Cuadro cuadro )
    {
        cuadroActual = cuadro; // asigna el argumento al cuadro actual
    } // fin del método establecerCuadroActual

    // clase interna privada para los cuadros en el tablero
    private class Cuadro extends JPanel
    {
        private String marca, marca2; // marca a dibujar en este cuadro
        private final int ubicacion; // ubicacion del cuadro

        public Cuadro( String marcaCuadro, int ubicacionCuadro )
        {
            marca = marcaCuadro; // establece la marca para este cuadro
            ubicacion = ubicacionCuadro; // establece la ubicación de este cuadro

            addMouseListener(
                new MouseAdapter()
                {
                    @Override
                    public void mouseReleased( MouseEvent e )
                    {
                        establecerCuadroActual( Cuadro.this ); // establece el cuadro actual

                        // envía la ubicación de este cuadro
                        enviarCuadroClic( obtenerUbicacionCuadro() );
                        } // fin del método mouseReleased
                    } // fin de la clase interna anónima
            ); // fin de la llamada a addMouseListener
        } // fin del constructor de Cuadro

        public String getMarca() {
            return marca;
        }
        

        // devuelve el tamaño preferido del objeto Cuadro
        @Override
        public Dimension getPreferredSize()
        {
            return new Dimension( 150, 150 ); // devuelve el tamaño preferido
        } // fin del método getPreferredSize

        // devuelve el tamaño mínimo del objeto Cuadro
        @Override
        public Dimension getMinimumSize()
        {
            return getPreferredSize(); // devuelve el tamaño preferido
        } // fin del método getMinimumSize

        // establece la marca para el objeto Cuadro
        public void establecerMarca( String nuevaMarca )
        {
            marca = nuevaMarca; // establece la marca del cuadro
            marca2 = marca;
            repaint(); // vuelve a pintar el cuadro
            //JOptionPane.showConfirmDialog(null, marca);
        } // fin del método establecerMarca
         // devuelve la ubicación del objeto Cuadro
        public int obtenerUbicacionCuadro()
        {
            return ubicacion; // devuelve la ubicación del cuadro
        } // fin del método obtenerUbicacionCuadro
        public String obtenerMarca(){
            return marca2;
        }

        // dibuja el objeto Cuadro
        @Override
        public void paintComponent( Graphics g )
        {
            super.paintComponent( g );

            g.drawRect( 0, 0, 150, 150 ); // dibuja el cuadro
            
            //g.drawString( marca, 30, 30 ); // dibuja la marca
            //g.fillArc();
            if(marca.equals(MARCA_O)){
                g.setColor(Color.BLUE);
                g.drawArc(10, 10, 130, 130, 0, 360);
            }
            else if(marca.equals(MARCA_X)){
                g.setColor(Color.RED);
                g.drawLine(10, 10, 140, 140);
                g.drawLine(140, 10, 10, 140);
            }
            
            
            
        } // fin del método paintComponent
    } // fin de la clase interna Cuadro
}
