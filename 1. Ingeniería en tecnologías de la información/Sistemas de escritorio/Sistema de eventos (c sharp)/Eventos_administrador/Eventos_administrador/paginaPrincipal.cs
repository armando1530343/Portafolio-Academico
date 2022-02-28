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
    public partial class paginaPrincipal : Form
    {
        bool normal;
        public paginaPrincipal(bool n)
        {
            InitializeComponent();
            normal = n;
        }


        private void paginaPrincipal_Load(object sender, EventArgs e)
        {
            label.Text = "Deshabilitar Fecha";
            Evento evento = new Evento();
            evento.agregarLugar(lugar_cbx);
            menuStrip2.Visible = false;
            
            
            if (normal == true)
            {
                groupBox1.Location = new Point(this.Width / 2 - groupBox1.Width / 2, groupBox1.Location.Y);
                panel1.Visible = false;
            }
            else
            {
                menuStrip1.Visible = false;
                menuStrip2.Visible = true;
                
            }
            
        }

        private void iniciaSesion_menu_Click(object sender, EventArgs e)
        {
            Login log = new Login();
            log.Show();
            this.Close();
        }

        

        bool cambia = false;

        

        Evento evento = new Evento();

        
        private void buscar2_btn_Click_1(object sender, EventArgs e)
        {
            Eventos_sinRegistro sn = new Eventos_sinRegistro(normal);
            bool existe = evento.existenEventos(lugar_cbx, fecha_txt, tipo_cbx);
            if (existe == true)
            {
                //MessageBox.Show("Se encontró información de Eventos", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                sn.Show();
            }
            else
            {
                MessageBox.Show("Ningun evento coincide con la busqueda realizada", "", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void label_Click_1(object sender, EventArgs e)
        {
            cambia = !cambia;
            if (cambia == true)
            {
                label.Text = "Habilitar Fecha";
                fecha_txt.Enabled = false;
            }
            else
            {
                label.Text = "Deshabilitar Fecha";
                fecha_txt.Enabled = true;
            }
        }

        private void toolStripMenuItem1_Click_1(object sender, EventArgs e)
        {
            paginaPrincipal p = new paginaPrincipal(true);
            p.Show();
            this.Close();
        }

        private void registro_menu_Click(object sender, EventArgs e)
        {
            RegistroUsuario ru = new RegistroUsuario();
            ru.Show();
            this.Close();
        }

        private void buscar_btn_Click_1(object sender, EventArgs e)
        {
            Eventos_sinRegistro sn = new Eventos_sinRegistro(normal);
            bool existe = evento.nombreEvento(evento_txt);
            if (existe == true)
            {
                sn.Show();
                //this.Close();
            }
        }
    }
}
