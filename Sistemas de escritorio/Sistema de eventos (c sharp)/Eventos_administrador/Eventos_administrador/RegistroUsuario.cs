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
using System.Data;

namespace Eventos_administrador
{
    public partial class RegistroUsuario : Form
    {
        public RegistroUsuario()
        {
            InitializeComponent();
        }

        public void limpiar()
        {
            nombre_txt.Clear();
            nombre_txt.Focus();
            apellido_txt.Clear();
            edad_txt.Clear();
            usuario_txt.Clear();
            pass1_txt.Clear();
            pass2_txt.Clear();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            SqlConnection conexion = ConexionSQL.Conectar();
            SqlCommand comando;
            SqlDataReader dr;
            SqlDataAdapter da;

            if(nombre_txt.Text == "" || apellido_txt.Text == "" || edad_txt.Text == "" || usuario_txt.Text == "" ||
                pass1_txt.Text == "" || pass2_txt.Text == "")
            {
                MessageBox.Show("Hay campos vacios", "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else if (pass1_txt.Text != pass2_txt.Text)
            {
                MessageBox.Show("Contraseñas diferentes", "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
            }
            else
            {
                comando = new SqlCommand("select * from Usuario where Nombre_Usuario = '" + usuario_txt.Text + "'", conexion);

                conexion.Open();
                dr = comando.ExecuteReader();
                //conexion.Close();

                if (dr.Read())
                {
                    MessageBox.Show("El nombre de usuario ya existe", "", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                }
                else
                {
                    try
                    {
                        int edad = Convert.ToInt32(edad_txt.Text);
                        conexion.Close();
                        comando = new SqlCommand(string.Format("Insert into Usuario(Nombre, Apellido, Edad, Nombre_Usuario, Contraseña)" +
                        "values ('{0}','{1}', {2}, '{3}', '{4}')",
                        nombre_txt.Text, apellido_txt.Text, edad, usuario_txt.Text, pass1_txt.Text), conexion);
                        conexion.Open();
                        comando.ExecuteNonQuery();
                        conexion.Close();
                        MessageBox.Show("Se ha registrado correctamente", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                        limpiar();
                    }
                    catch (Exception error)
                    {
                        MessageBox.Show(error.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    }
                    
                }
                conexion.Close();

                
            }
        }

        private void busca_btn_Click(object sender, EventArgs e)
        {
            paginaPrincipal p = new paginaPrincipal(true);
            p.Show();
            this.Close();
        }

        private void edad_txt_KeyPress(object sender, KeyPressEventArgs e)
        {
            ValidarCampo v = new ValidarCampo();
            v.soloNumeros(e);
        }

        private void limpia_btn_Click(object sender, EventArgs e)
        {
            limpiar();
        }

    }
}
