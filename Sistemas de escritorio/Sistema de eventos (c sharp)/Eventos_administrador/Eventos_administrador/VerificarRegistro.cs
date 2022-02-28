using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;

namespace Eventos_administrador
{
    class VerificarRegistro
    {
        bool existe;
        SqlConnection conexion = ConexionSQL.Conectar();
        SqlCommand comando;

        //string id_admin;
        public VerificarRegistro()
        {
            //id_admin = "";
        }

        DataSet ds;
        SqlDataAdapter da;
        SqlDataReader dr;

        public static DataSet cmd;

        public static void setDataSet(DataSet d)
        {
            cmd = d;
        }
        public static DataSet getDataset()
        {
            return cmd;
        }
        
        public bool Login(string cuenta, string pass)
        {
            existe = false;
           
            da = new SqlDataAdapter(
                "Select * from Administrador where Cuenta='" + cuenta + "' and Contraseña='" + pass + "'", conexion);
            ds = new DataSet();
            
            conexion.Open();
            da.Fill(ds);
            conexion.Close();

            //bool admin = false;

            if (ds.Tables[0].Rows.Count > 0)
            {
                existe = true;
                //admin = true;
            }
            else
            {
                da = new SqlDataAdapter(
                "Select * from Usuario where Nombre_Usuario='" + cuenta + "' and Contraseña='" + pass + "'", conexion);
                ds = new DataSet();
                conexion.Open();
                da.Fill(ds);
                conexion.Close();
                if (ds.Tables[0].Rows.Count > 0)
                {
                    existe = true;
                }
            
            }
            setDataSet(ds);


            return existe;
        }

        public bool registro(string tabla, string campo, TextBox reg)
        {
            existe = false;
            comando = new SqlCommand(
                string.Format("Select * from {0} where {1} = '{2}'", tabla, campo, reg.Text),conexion);
            conexion.Open();
            dr = comando.ExecuteReader();
            if (dr.Read())
            {
                existe = true;
            }
            conexion.Close();
            return existe;
        }
    }
}