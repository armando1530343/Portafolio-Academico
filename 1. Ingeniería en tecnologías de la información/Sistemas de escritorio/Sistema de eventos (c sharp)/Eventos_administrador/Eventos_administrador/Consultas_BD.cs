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
    public partial class Consultas_BD : Form
    {
        public Consultas_BD()
        {
            InitializeComponent();
        }

        SqlConnection conexion = ConexionSQL.Conectar();
        SqlCommand comando;
        SqlDataAdapter da;
        SqlDataReader dr;
        DataTable dt;

        private void consultar(string consulta)
        {
            try
            {
                if (consulta.Contains("nsert") || consulta.Contains("elete") || consulta.Contains("pdate") ||
                    consulta.Contains("INSERT") || consulta.Contains("DELETE") || consulta.Contains("UPDATE"))
                {
                    MessageBox.Show("Solo comandos con 'Select'");
                }
                else
                {
                    da = new SqlDataAdapter(consulta, conexion);
                    dt = new DataTable();
                    da.Fill(dt);
                    consultas_dgv.DataSource = dt;
                }
                
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message);
                comando_txt.Focus();
            }
        }       

        private void salir_btn_Click(object sender, EventArgs e)
        {
            Interfaz_administrador ia = new Interfaz_administrador();
            ia.Show();
            this.Close();
        }
        private void admin_btn_Click(object sender, EventArgs e)
        {
            consultar("Select * from Administrador");
        }

        private void evento_btn_Click(object sender, EventArgs e)
        {
            consultar("Select * from Evento");
        }

        private void usuario_btn_Click(object sender, EventArgs e)
        {
            consultar("Select * from Usuario");
        }

        private void usev_btn_Click(object sender, EventArgs e)
        {
            consultar("Select * from Usuario_Evento");
        }

        private void ejecutar_btn_Click(object sender, EventArgs e)
        {
            consultar(comando_txt.Text);
        }
    }
}
