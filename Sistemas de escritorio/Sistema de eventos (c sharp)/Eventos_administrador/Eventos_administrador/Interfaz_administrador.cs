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
    public partial class Interfaz_administrador : Form
    {
        public Interfaz_administrador()
        {
            InitializeComponent();
        }

        private void gestrinarEventosToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Gestion_eventos ge = new Gestion_eventos();
            ge.Show();
            this.Close();
        }

        private void consultasDeBaseDeDatosToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Consultas_BD bd = new Consultas_BD();
            bd.Show();
            this.Close();
        }

        private void cambiarDatosDeLaCuentaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Cambiar_contraseña cc = new Cambiar_contraseña();
            cc.Show();
            this.Close();
        }

        private void cerrarSesiónToolStripMenuItem_Click(object sender, EventArgs e)
        {
            paginaPrincipal f = new paginaPrincipal(true);
            f.Show();
            this.Close();  
        }
    }
}
