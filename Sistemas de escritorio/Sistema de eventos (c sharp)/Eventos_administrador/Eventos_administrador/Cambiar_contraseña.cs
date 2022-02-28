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
    public partial class Cambiar_contraseña : Form
    {
        public Cambiar_contraseña()
        {
            InitializeComponent();
        }

        private void Cambiar_contraseña_Load(object sender, EventArgs e)
        {
            nvaCuenta_txt.Focus();
        }

        private void interface_inicial()
        {
            nvaCuenta_txt.Focus();
            nvaCuenta_txt.Clear();
            nvaPass_txt.Clear();
            nvaPass2_txt.Clear();
        }
        private void cancela_btn_Click(object sender, EventArgs e)
        {
            Interfaz_administrador ia = new Interfaz_administrador();
            ia.Show();
            this.Close();
        }

        private void guardar_btn_Click(object sender, EventArgs e)
        {
            SqlConnection conexion = ConexionSQL.Conectar();

            if (nvaCuenta_txt.Text == "" || nvaPass_txt.Text == "" || nvaPass2_txt.Text == "")
            {
                MessageBox.Show("Hay campos Vacios", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                nvaCuenta_txt.Focus();
            }
            else if (nvaPass_txt.Text != nvaPass2_txt.Text)
            {
                MessageBox.Show("Contraseñas Diferentes", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                conexion.Open();
                SqlCommand comando = new SqlCommand(string.Format(
                    "Update Administrador Set Cuenta = '{0}', Contraseña = '{1}'",
                    nvaCuenta_txt.Text, nvaPass2_txt.Text), conexion);

                comando.ExecuteNonQuery();
                conexion.Close();
                MessageBox.Show("Datos guardador correctamente", "Datos Guardados", MessageBoxButtons.OK, MessageBoxIcon.Information);
                interface_inicial();

            }
        }        
    }
}