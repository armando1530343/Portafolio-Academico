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
    public partial class Actualizar_evento : Form
    {
        public Actualizar_evento()
        {
            InitializeComponent();
        }

        private void cancela_btn_Click(object sender, EventArgs e)
        {
            Gestion_eventos ge = new Gestion_eventos();
            ge.Show();
            this.Close();
        }

        Evento evento = new Evento();

        private void Limpiar()
        {
            id_txt.Clear();
            id_txt.Focus();
            url_txt.Clear();
            nombre_txt.Clear();
            lugar_txt.Clear();
            tipo_cbx.Text = "";
            fecha_txt.Clear();
            descripcion_txt.Clear();
            asisten_txt.Clear();
            imagen_pbx.Image = null;
        }

        private void busca_btn_Click_1(object sender, EventArgs e)
        {
            bool existe;

            if (id_txt.Text != "")
            {
                existe = evento.buscarEvento(id_txt, url_txt, imagen_pbx, nombre_txt, lugar_txt, fecha_txt, tipo_cbx,
                                    descripcion_txt, asisten_txt);
                if (existe == true)
                {
                    guarda_btn.Enabled = true;
                    nombre_txt.Focus();
                }
                else
                {
                    id_txt.Clear();
                    id_txt.Focus();
                }
            }
            else
            {
                MessageBox.Show("No se ingresó Id");
            }
        }

        private void guarda_btn_Click(object sender, EventArgs e)
        {
            if (url_txt.Text == "" || nombre_txt.Text == "" || lugar_txt.Text == "" || fecha_txt.Text == "" || 
               tipo_cbx.Text == "" || descripcion_txt.Text == "" || asisten_txt.Text == "" || imagen_pbx.Image == null)
            {
                MessageBox.Show("Campos vacios","",MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                evento.actualizarEvento(id_txt, url_txt, imagen_pbx, nombre_txt, lugar_txt, fecha_txt, tipo_cbx,
                                    descripcion_txt, asisten_txt);
                Limpiar();
            }
        }

        private void limpia_btn_Click(object sender, EventArgs e)
        {
            Limpiar();
        }

        private void cargar_btn_Click(object sender, EventArgs e)
        {
            evento.cargarImagen(imagen_pbx);
        }        
    }
}
