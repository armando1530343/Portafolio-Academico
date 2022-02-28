using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Eventos_administrador
{
    public partial class Elimina_evento : Form
    {
        public Elimina_evento()
        {
            InitializeComponent();
        }

        private void interface_inicial()
        {
            id_txt.Clear();
            id_txt.Focus();
            url_txt.Clear();
            nombre_txt.Clear();
            lugar_txt.Clear();
            tipo_cbx.Text = "";
            descripcion_txt.Clear();
            asisten_txt.Clear();
            imagen_pbx.Image = null;
            elimina_btn.Enabled = false;

        }

        Evento evento = new Evento();
        private void busca_btn_Click(object sender, EventArgs e)
        {
            bool existe;

            if (id_txt.Text == "")
            {
                MessageBox.Show("Ingresa la clave del evento","", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                existe = evento.buscarEvento(id_txt, url_txt, imagen_pbx, nombre_txt, lugar_txt, fecha_txt, tipo_cbx,
                                    descripcion_txt, asisten_txt);
                if (existe == true)
                {
                    elimina_btn.Enabled = true;
                }
                else
                {
                    interface_inicial();
                }
            }
        }

        private void cancela_btn_Click_1(object sender, EventArgs e)
        {
            Gestion_eventos ge = new Gestion_eventos();
            ge.Show();
            this.Close();
        }

        private void elimina_btn_Click(object sender, EventArgs e)
        {
            evento.eliminarEvento(id_txt);
            interface_inicial();
        }
    }
}
