using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace algebraLineal
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void salirDelSistemaToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult SN = MessageBox.Show("Seguro que quieres Salir", "Salir", MessageBoxButtons.YesNo, MessageBoxIcon.Exclamation);

            if (SN == DialogResult.Yes)
            {
                this.Close();
            }
        }

        private void crearMatricesToolStripMenuItem_Click(object sender, EventArgs e)
        {
            Matrices m = new Matrices();
            m.Show();
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            
        }

        
    }
}
