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
    public partial class Gestion_eventos : Form
    {
        public Gestion_eventos()
        {
            InitializeComponent();
        }


        private void boton1_Click(object sender, EventArgs e)
        {
            Agregar_evento ae = new Agregar_evento();
            ae.Show();
            this.Close();
        }

        private void boton2_Click(object sender, EventArgs e)
        {
            Actualizar_evento ae = new Actualizar_evento();
            ae.Show();
            this.Close();
        }

        private void boton3_Click(object sender, EventArgs e)
        {
            Elimina_evento ee = new Elimina_evento();
            ee.Show();
            this.Close();
        }

        private void boton4_Click(object sender, EventArgs e)
        {
            Interfaz_administrador ia = new Interfaz_administrador();
            ia.Show();
            this.Close();
        }
    }
}
