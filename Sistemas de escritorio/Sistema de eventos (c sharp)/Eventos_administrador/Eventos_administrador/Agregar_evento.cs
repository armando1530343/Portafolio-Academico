using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data.SqlClient;

namespace Eventos_administrador
{
    public partial class Agregar_evento : Form
    {
        public Agregar_evento()
        {
            InitializeComponent();
        }

        WebBrowser navegador = new WebBrowser();
        int pagina = 0;
        bool validaURL = false;


        private void Agregar_evento_Load(object sender, EventArgs e)
        {
            captura_btn.Enabled = false;
            navegador.ScriptErrorsSuppressed = true;
            navegador.DocumentCompleted += new WebBrowserDocumentCompletedEventHandler(this.Capturar_datos);
        }

        private void Capturar_datos(object sender, EventArgs e)
        {
            Estructuras est = new Estructuras(navegador, nombre_txt, lugar_txt, lugar_txt, descripcion_txt, asisten_txt);
            try
            {
                if (pagina == 1)
                {
                    est.el_vortex();
                }
                else if (pagina == 2)
                {
                    est.eventHint();
                }
                else if (pagina == 3)
                {
                    est.zonaTuristica();
                }
                else if(pagina == 4)
                {
                    est.Eventbrite();
                }
                validaURL = true;
                
            }
            catch (Exception error)
            {
                MessageBox.Show("El URL no coincide con la direccion de un evento\nError: " + error.Message,
                    "URL Erronea", MessageBoxButtons.OK, MessageBoxIcon.Error);
                url_txt.Focus();
                //desbloquear();
            }
            
        }

        private void captura_btn_Click(object sender, EventArgs e)
        {
            VerificarRegistro ver = new VerificarRegistro();
            bool existe = ver.registro("Evento", "URL", url_txt);

            if (existe == true)
            {
                MessageBox.Show("Ya existe la URL del Evento", "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                navegador.Navigate(url_txt.Text); 
            }
                      
        }

        private void Limpiar()
        {
            url_txt.Clear();
            nombre_txt.Clear();
            lugar_txt.Clear();
            tipo_cbx.Text = "";
            descripcion_txt.Clear();
            url_txt.Focus();
            asisten_txt.Clear();
            imagen_pbx.Image = null;
        }
        
        private void pag1_btn_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://www.elvortex.com/calendario-de-eventos/");
            //desbloquear();
            pagina = 1;
            captura_btn.Enabled = true;
        }

        private void pag2_btn_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("http://es.eventhint.com/ciudad-victoria");
            //desbloquear();
            pagina = 2;
            captura_btn.Enabled = true;
        }

        private void pag3_btn_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://www.zonaturistica.com/calendario-de-festividades-en/mexico-agosto-2017.html");
            //desbloquear();
            pagina = 3;
            captura_btn.Enabled = true;
        }

        private void pag4_btn_Click(object sender, EventArgs e)
        {
            System.Diagnostics.Process.Start("https://www.eventbrite.es/d/mexico-city--mexico-city/events/");
            //desbloquear();
            pagina = 4;
            captura_btn.Enabled = true;
        }

        private void cancela_btn_Click(object sender, EventArgs e)
        {
            Gestion_eventos ge = new Gestion_eventos();
            ge.Show();
            this.Close();
        }

        private void limpia_btn_Click(object sender, EventArgs e)
        {
            Limpiar();
        }

        Evento evento;

        private string validarCadena(TextBox cadena)
        {
            return cadena.Text.Replace("'", " ");
        }


        private void cargar_btn_Click(object sender, EventArgs e)
        {
            evento = new Evento();
            evento.cargarImagen(imagen_pbx);
        }  

        private void guarda_btn_Click(object sender, EventArgs e)
        {            
            if (nombre_txt.Text == "" || lugar_txt.Text == "" || descripcion_txt.Text == "" || 
                fecha_txt.Text == "" || tipo_cbx.Text == "" || asisten_txt.Text == "" || imagen_pbx.Image == null)
            {
                MessageBox.Show("Hay campos vacios o no se cargó la Imagen", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            /*else if (validaURL == false)
            {
                MessageBox.Show("URL Incorrecta", "", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }*/
            else
            {
                evento = new Evento();
                nombre_txt.Text = validarCadena(nombre_txt);
                lugar_txt.Text = validarCadena(lugar_txt);
                //fecha_txt.Text = validarCadena(fecha_txt);
                descripcion_txt.Text = validarCadena(descripcion_txt);
                url_txt.Text = validarCadena(url_txt);
                
                
                evento.agragarEvento(nombre_txt, lugar_txt, fecha_txt, tipo_cbx, descripcion_txt, asisten_txt,
                                        url_txt, imagen_pbx);
                
                
                Limpiar();
            }
        }

        ValidarCampo vc = new ValidarCampo();

        private void asisten_txt_KeyPress(object sender, KeyPressEventArgs e)
        {
            vc.soloNumeros(e);
        }

            

    }
}
