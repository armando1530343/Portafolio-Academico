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
    public partial class Login : Form
    {
        public static bool bloquear;
        public Login()
        {
            InitializeComponent();
        }
        
        private void salir_btn_Click(object sender, EventArgs e)
        {
            this.Close();
        }

        private void ingresa_btn_Click(object sender, EventArgs e)
        {
            VerificarRegistro ver = new VerificarRegistro();
            if (cuenta_txt.Text == "" || pass_txt.Text == "")
            {
                MessageBox.Show("Hay campos Vacios", "Inválido", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                cuenta_txt.Focus();
            }
            else
            {
                bool validar = ver.Login(cuenta_txt.Text, pass_txt.Text);
                DataSet ds;


                if (validar == true)
                {
                    ds = VerificarRegistro.getDataset();
                    
                    if (ds.Tables[0].Columns.Count > 3)
                    {
                        paginaPrincipal p = new paginaPrincipal(false);
                        p.user_lab.Text = "Bienvenido, " + ds.Tables[0].Rows[0]["Nombre"].ToString();
                        p.Show();
                        this.Close();
                    }
                    else
                    {
                        Interfaz_administrador ia = new Interfaz_administrador();
                        ia.Show();
                        this.Close();
                    }                    
                }
                else
                {
                    MessageBox.Show("Datos Incorrectos", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                    cuenta_txt.Focus();
                }
            }
            
        }

        private void Login_Load(object sender, EventArgs e)
        {

        }
    }
}