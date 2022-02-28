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
    public partial class WhatsEvent : Form
    {
        public WhatsEvent()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void entra_btn_Click(object sender, EventArgs e)
        {
            paginaPrincipal pg = new paginaPrincipal(true);
            pg.Show();
        }
    }
}
