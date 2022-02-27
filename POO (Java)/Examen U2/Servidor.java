/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package juego.gato.lib;

import java.awt.BorderLayout;
import java.net.ServerSocket;
import java.net.Socket;
import java.io.IOException;
import java.util.Formatter;
import java.util.Scanner;
import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;
import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;
import java.util.concurrent.locks.Condition;
import javax.swing.JFrame;
import javax.swing.JTextArea;
import javax.swing.SwingUtilities;

/**
 *
 * @author Armando Isaac
 * 
 * Esta clase es la principal al momento de iniciar el juego ya que si no se arranca primero
 * no se podrá jugar
 */
public class Servidor extends JFrame{
    private String[] tablero = new String[ 9 ]; // tablero de tres en raya
    private JTextArea areaSalida; // para imprimir los movimientos en pantalla
    private Jugador[] jugadores; // arreglo de objetos Jugador
    private ServerSocket servidor; // socket servidor para conectarse con los clientes
    private int jugadorActual; // lleva la cuenta del jugador que sigue en turno
    private final static int JUGADOR_X = 0; // constante para el primer jugador
    private final static int JUGADOR_O = 1; // constante para el segundo jugador
    private final static String[] MARCAS = { "X", "O" }; // arreglo de marcas
    private ExecutorService ejecutarJuego; // ejecuta a los jugadores
    private Lock bloqueoJuego; // para bloquear el juego y estar sincronizado
    private Condition otroJugadorConectado; // para esperar al otro jugador
    private Condition turnoOtroJugador; // para esperar el turno del otro jugador
    // establece servidor de tres en raya y GUI para mostrar mensajes en pantalla
    public Servidor()
    {
        super( "Servidor de Tres en raya" ); // establece el título de la ventana

        // crea objeto ExecutorService con un subproceso para cada jugador
        ejecutarJuego = Executors.newFixedThreadPool( 2 );
        bloqueoJuego = new ReentrantLock(); // crea bloqueo para el juego
        // variable de condición para los dos jugadores conectados
        otroJugadorConectado = bloqueoJuego.newCondition();
        // variable de condición para el turno del otro jugador
        turnoOtroJugador = bloqueoJuego.newCondition();

        for ( int i = 0; i < 9; i++ )
            tablero[ i ] = new String( "" ); // crea tablero de tres en raya
        
        jugadores = new Jugador[ 2 ]; // crea arreglo de jugadores
        jugadorActual = JUGADOR_X; // establece el primer jugador como el jugador actual
        try
        {
            servidor = new ServerSocket( 12345, 2 ); // establece objeto ServerSocket
        } // fin de try
        catch ( IOException excepcionES )
        {
            excepcionES.printStackTrace();
            System.exit( 1 );
        } // fin de catch
        
        areaSalida = new JTextArea(); // crea objeto JTextArea para mostrar la salida
        add( areaSalida, BorderLayout.CENTER );
        areaSalida.setText( "Servidor esperando conexiones\n" );
        setSize( 300, 300 ); // establece el tamaño de la ventana
        setVisible( true ); // muestra la ventana
    } // fin del constructor de ServidorTresEnRaya

     // espera dos conexiones para poder jugar
    public void execute()
    {
        // espera a que se conecte cada cliente
        for ( int i = 0; i < jugadores.length; i++ )
        {
            try // espera la conexión, crea el objeto Jugador, inicia objeto Runnable
            {
                jugadores[ i ] = new Jugador( servidor.accept(), i );
                ejecutarJuego.execute( jugadores[ i ] ); // ejecuta el objeto Runnable jugador
            } // fin de try
            catch ( IOException excepcionES )
            {
                excepcionES.printStackTrace();
                System.exit( 1 );
            } // fin de catch
        } // fin de for

        bloqueoJuego.lock(); // bloquea el juego para avisar al subproceso del jugador X

        try
        {
            jugadores[ JUGADOR_X ].establecerSuspendido( false ); // continúa el jugador X
            otroJugadorConectado.signal(); // despierta el subproceso del jugador X
        } // fin de try
        finally
        {
            bloqueoJuego.unlock(); // desbloquea el juego después de avisar al jugador X
        } // fin de finally
    }
    // muestra un mensaje en objeto areaSalida
    private void mostrarMensaje( final String mensajeAMostrar )
    {
        // muestra un mensaje del subproceso de ejecución despachador de eventos
        SwingUtilities.invokeLater(
        new Runnable()
        {
            public void run() // actualiza el objeto areaSalida
            {
                areaSalida.append( mensajeAMostrar ); // agrega el mensaje
            } // fin del método run
            } // fin de la clase interna
        ); // fin de la llamada a SwingUtilities.invokeLater
    } // fin del método mostrarMensaje

    // determina si el movimiento es válido
    public boolean validarYMover( int ubicacion, int jugador )
    {
        // mientras no sea el jugador actual, debe esperar su turno
        while ( jugador != jugadorActual )
        {
            bloqueoJuego.lock(); // bloquea el juego para esperar a que el otro jugador haga su movmiento

            try
            {
                turnoOtroJugador.await(); // espera el turno de jugador
            } // fin de try
            catch ( InterruptedException excepcion )
            {
                excepcion.printStackTrace();
            } // fin de catch
            finally
            {
                bloqueoJuego.unlock(); // desbloquea el juego después de esperar
            } // fin de finally
        } // fin de while

        // si la ubicación no está ocupada, realiza el movimiento
        if ( !estaOcupada( ubicacion ) )
        {
            tablero[ ubicacion ] = MARCAS[ jugadorActual ]; // establece el movimiento en tablero
            jugadorActual = ( jugadorActual + 1 ) % 2; // cambia el jugador

            // deja que el nuevo jugador sepa que se realizó un movimiento
            jugadores[ jugadorActual ].otroJugadorMovio( ubicacion );
            bloqueoJuego.lock(); // bloquea el juego para indicar al otro jugador que realice su movimiento

            try
            {
                turnoOtroJugador.signal(); // indica al otro jugador que debe continuar
            } // fin de try
            finally
            {
                bloqueoJuego.unlock(); // desbloquea el juego despues de avisar
            } // fin de finally

            return true; // notifica al jugador que el movimiento fue válido
        } // fin de if
        else // el movimiento no fue válido
            return false; // notifica al jugador que el movimiento fue inválido
    } // fin del método validarYMover

    // determina si la ubicación está ocupada
    public boolean estaOcupada( int ubicacion )
    {
        if ( tablero[ ubicacion ].equals( MARCAS[ JUGADOR_X ] ) ||
        tablero [ ubicacion ].equals( MARCAS[ JUGADOR_O ] ) )
        return true; // la ubicación está ocupada
        else
        return false; // la ubicación no está ocupada
    } // fin del método estaOcupada

    // coloca código en este método para determinar si terminó el juego
    public boolean seTerminoJuego()
    {
        return false; // esto se deja como ejercicio
    } // fin del método seTerminoJuego

    // la clase interna privada Jugador maneja a cada Jugador como objeto Runnable
    private class Jugador implements Runnable
    {
        private Socket conexion; // conexión con el cliente
        private Scanner entrada; // entrada del cliente
        private Formatter salida; // salida al cliente
        private int numeroJugador; // rastrea cuál jugador es el actual
        private String marca; // marca para este jugador
        private boolean suspendido = true; // indica si el subproceso está suspendido

        // establece el subproceso Jugador
        public Jugador( Socket socket, int numero )
        {
            numeroJugador = numero; // almacena el número de este jugador
            marca = MARCAS[ numeroJugador ]; // especifica la marca del jugador
            conexion = socket; // almacena socket para el cliente

            try // obtiene los flujos del objeto Socket
            {
                entrada = new Scanner( conexion.getInputStream() );
                salida = new Formatter( conexion.getOutputStream() );
            } // fin de try
            catch ( IOException excepcionES )
            {
                excepcionES.printStackTrace();
                System.exit( 1 );
            } // fin de catch
        } // fin del constructor de Jugador

        // envía mensaje que indica que el otro jugador hizo un movimiento
        public void otroJugadorMovio( int ubicacion )
        {
            salida.format("El oponente realizo movimiento\n" );
            salida.format("%d\n", ubicacion ); // envía la ubicación del movimiento
            salida.flush(); // vacía la salida
        } // fin del método otroJugadorMovio

        // controla la ejecución del subproceso
        public void run()
        {
            // envía al cliente su marca (X o O), procesa los mensajes del cliente
            try
            {
                mostrarMensaje( "Jugador " + marca + " conectado\n" );
                salida.format( "%s\n", marca ); // envía la marca del jugador
                salida.flush(); // vacía la salida

                // si es el jugador X, espera a que llegue el otro jugador
                if ( numeroJugador == JUGADOR_X )
                {
                    salida.format( "%s\n%s", "Jugador X conectado",
                    "Esperando al otro jugador\n" );
                    salida.flush(); // vacía la salida
                    bloqueoJuego.lock(); // bloquea el juego para esperar al segundo jugador

                    try
                    {
                        while( suspendido )
                        {
                            otroJugadorConectado.await(); // espera al jugador O
                        } // fin de while
                    } // fin de try
                    catch ( InterruptedException excepcion )
                    {
                        excepcion.printStackTrace();
                    } // fin de catch
                    finally
                    {
                        bloqueoJuego.unlock(); // desbloquea el juego después del segundo jugador
                    } // fin de finally
                    // envía un mensaje que indica que el otro jugador se conectó
                    salida.format( "El otro jugador se conecto. Ahora es su turno.\n" );
                    salida.flush(); // vacía la salida
                } // fin de if
                else
                {
                    salida.format( "El jugador O se conecto, por favor espere\n" );
                    salida.flush(); // vacía la salida
                } // fin de else

                // mientras el juego no termine
                while ( !seTerminoJuego() )
                {
                    int ubicacion = 0; // inicializa la ubicación del movimiento

                    if ( entrada.hasNext() )
                        ubicacion = entrada.nextInt(); // obtiene la ubicación del movimiento

                    // comprueba si el movimiento es válido
                    if ( validarYMover( ubicacion, numeroJugador ) )
                        {
                            mostrarMensaje( "\nubicacion: " + ubicacion );
                            salida.format( "Movimiento valido.\n" ); // notifica al cliente
                            salida.flush(); // vacía la salida
                        } // fin de if
                    else // el movimiento fue inválido
                    {
                        salida.format( "Movimiento invalido, intente de nuevo\n" );
                        salida.flush(); // vacía la salida
                    } // fin de else
                } // fin de while
            } // fin de try
            finally
            {
                try
                {
                    conexion.close(); // cierra la conexión con el cliente
                } // fin de try
                catch ( IOException excepcionES )
                {
                    excepcionES.printStackTrace();
                    System.exit( 1 );
                } // fin de catch
            } // fin de finally
        } // fin del método run

        // establece si se suspende el subproceso o no
        public void establecerSuspendido( boolean estado )
        {
            suspendido = estado; // establece el valor de suspendido
        } // fin del método establecerSuspendido
    } // fin de la clase Jugador
}
