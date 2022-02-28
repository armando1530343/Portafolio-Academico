using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Data;
using System.Data.SqlClient;
using System.Windows.Forms;
using System.IO;
using System.Drawing;

namespace Eventos_administrador
{
    class Evento
    {

        public static DataSet tabla;
        public static int filas;
        public Evento()
        {
            filas = 0;
        }

        public static void setComando(DataSet ds)
        {
            tabla = ds;
        }

        public static DataSet getComando()
        {
            return tabla;
        }

        public static void setFilas(int f)
        {
            filas = f;
        }

        public static int getFilas()
        {
            return filas;
        }
        

        SqlConnection conexion = ConexionSQL.Conectar();
        SqlCommand comando;
        DataSet ds;
        SqlDataAdapter adaptador;

        Agregar_evento ae = new Agregar_evento();
        
        public void agragarEvento(TextBox nombre, TextBox lugar, DateTimePicker fecha, ComboBox tipo,
                                    TextBox descripcion, TextBox asistentes, TextBox url, PictureBox imagen)
        {            
            try
            {
                conexion = ConexionSQL.Conectar();
                        
                conexion.Open();
                comando = new SqlCommand("Insert Into Evento (Nombre,Lugar,Fecha,Categoria,Descripcion,Asistentes,URL,Imagen) values (" +
                    "'" + nombre.Text + "'," +
                    "'" + lugar.Text + "'," +
                    "'" + fecha.Text + "'," +
                    "'" + tipo.Text + "'," +
                    "'" + descripcion.Text + "'," +
                          asistentes.Text + "," +
                    "'" + url.Text + "', @img)" , conexion);

                comando.Parameters.Add("@img", SqlDbType.Image);

                MemoryStream ms = new MemoryStream();
                imagen.Image.Save(ms, System.Drawing.Imaging.ImageFormat.Jpeg);
                comando.Parameters["@img"].Value = ms.GetBuffer();

                comando.ExecuteNonQuery();
                MessageBox.Show("Datos guardados correctamente", "Datos guardados", MessageBoxButtons.OK, MessageBoxIcon.Information);
                conexion.Close();
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message,"Error al guardar", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            
        }

        public bool buscarEvento(TextBox id, TextBox url, PictureBox imagen, TextBox nombre, TextBox lugar, TextBox fecha, ComboBox tipo,
                                        TextBox descripcion, TextBox asistentes)
        {
            bool retorno = false;
            byte[] datos = new byte[0];


            try
            {
                adaptador = new SqlDataAdapter(
                    "Select * from Evento Where Id_evento=" + id.Text, conexion);
                ds = new DataSet();
                conexion.Open();
                adaptador.Fill(ds);
                conexion.Close();

                if (ds.Tables[0].Rows.Count > 0)
                {
                    nombre.Text = ds.Tables[0].Rows[0]["Nombre"].ToString();
                    lugar.Text = ds.Tables[0].Rows[0]["Lugar"].ToString();
                    fecha.Text = ds.Tables[0].Rows[0]["Fecha"].ToString();
                    tipo.Text = ds.Tables[0].Rows[0]["Categoria"].ToString();
                    descripcion.Text = ds.Tables[0].Rows[0]["Descripcion"].ToString();
                    asistentes.Text = ds.Tables[0].Rows[0]["Asistentes"].ToString();
                    url.Text = ds.Tables[0].Rows[0]["URL"].ToString();


                    DataRow dr = ds.Tables[0].Rows[0];
                    datos = (byte[])dr["Imagen"];
                    MemoryStream ms = new MemoryStream(datos);
                    imagen.Image = System.Drawing.Bitmap.FromStream(ms);

                    retorno = true;
                }
                else
                {
                    MessageBox.Show("No se encontraron Eventos con Id = " + id.Text,
                        "Datos Incorrectos", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message, "Error al cargar los datos", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            return retorno;
        }

        public void actualizarEvento(TextBox id, TextBox url, PictureBox imagen, TextBox nombre, TextBox lugar, TextBox fecha, ComboBox tipo,
                                        TextBox descripcion, TextBox asistentes)
        {
            try
            {
                comando = new SqlCommand("Update Evento set " +
                "URL = '" + url.Text +
                "', Nombre = '" + nombre.Text +
                "', Lugar = '" + lugar.Text +
                "', Fecha = '" + fecha.Text +
                "', Categoria = '" + tipo.Text +
                "', Descripcion = '" + descripcion.Text +
                "', Asistentes = " + asistentes.Text + 
                ", Imagen = @img Where Id_evento = " + id.Text, conexion);

                comando.Parameters.Add("@img", SqlDbType.Image);

                MemoryStream ms = new MemoryStream();
                imagen.Image.Save(ms, System.Drawing.Imaging.ImageFormat.Jpeg);
                comando.Parameters["@img"].Value = ms.GetBuffer();

                conexion.Open();
                comando.ExecuteNonQuery();
                conexion.Close();
                MessageBox.Show("Datos actualizados", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch (Exception error)
            {
                MessageBox.Show(error.Message,"Error al acutualizar", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void eliminarEvento(TextBox idEvento)
        {
            int id = Convert.ToInt32(idEvento.Text);
            try
            {
                comando = new SqlCommand("Delete from Evento where Id_evento = " + id, conexion);
                conexion.Open();
                comando.ExecuteNonQuery();
                conexion.Close();
                MessageBox.Show("El evento se eliminó correctamente", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
            catch(Exception error)
            {
                MessageBox.Show(error.Message, "", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        public void agregarLugar(ComboBox lugar)
        {
            int i;
            adaptador = new SqlDataAdapter("select Lugar from Evento", conexion);
            ds = new DataSet();
            conexion.Open();
            adaptador.Fill(ds);
            conexion.Close();

            if (ds.Tables[0].Rows.Count > 0)
            {
                for (i = 0; i < ds.Tables[0].Rows.Count; i++)
                {
                    lugar.Items.Add(ds.Tables[0].Rows[i]["Lugar"].ToString());
                }
            }

        }

        public void cargarImagen(PictureBox imagen)
        {
            Image img;
            OpenFileDialog dialogo = new OpenFileDialog();
            dialogo.Filter = "JPG(*.JPG)|*.jpg";

            if (dialogo.ShowDialog() == DialogResult.OK)
            {
                img = Image.FromFile(dialogo.FileName);
                imagen.Image = img;

            }
        }
        public bool nombreEvento(TextBox evento)
        {
            adaptador = new SqlDataAdapter("select * from Evento where Nombre like '" + evento.Text + "%'", conexion);
            ds = new DataSet();
            conexion.Open();
            adaptador.Fill(ds);
            conexion.Close();
            bool existe = false;
            if (ds.Tables[0].Rows.Count > 0)
            {
                //MessageBox.Show("Se encontraron coincidencias", "", MessageBoxButtons.OK, MessageBoxIcon.Information);
                setComando(ds);
                existe = true;
            }
            else
            {
                MessageBox.Show("No hay Eventos", "", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            return existe;
        }

        SqlDataReader dr;

        public bool existenEventos(ComboBox lugar, DateTimePicker fecha, ComboBox tipo)
        {
            bool hayFecha = false;
            bool hayTipo = false;
            bool existeBusqueda = false;

            //MessageBox.Show("comandoTxt = " + comandoTxt);

            if (tipo.Text != "")
            {
                comando = new SqlCommand(string.Format("select * from Evento where Categoria = '{0}'", tipo.Text), conexion);
                conexion.Open();
                dr = comando.ExecuteReader();
                if (dr.Read())
                {
                    hayTipo = true;
                }
                conexion.Close();
            }

            comando = new SqlCommand(string.Format("select * from Evento where Fecha = '{0}'", fecha.Text), conexion);
            conexion.Open();
            dr = comando.ExecuteReader();
            
            
            if (dr.Read())
            {
                hayFecha = true;
            }
            conexion.Close();                        

            if (lugar.Text == "" && tipo.Text == "" && fecha.Enabled == false)
            {
                MessageBox.Show("No se seleccionó busqueda");
                
            }
            else if (lugar.Text == "" && tipo.Text == "" && fecha.Enabled == true)
            {
                if (hayFecha == true)
                {
                    existeBusqueda = true;
                    comando.CommandText = string.Format("select * from Evento where Fecha = '{0}'",fecha.Text);
                }
            }
            else if (lugar.Text != "" && tipo.Text == "" && fecha.Enabled == false)
            {
                existeBusqueda = true;
                comando.CommandText = string.Format("select * from Evento where Lugar = '{0}'", lugar.Text);
            }
            else if (lugar.Text == "" && tipo.Text != "" && fecha.Enabled == false)
            {
                if (hayTipo == true)
                {
                    existeBusqueda = true;
                    comando.CommandText = string.Format("select * from Evento where Categoria = '{0}'", tipo.Text);
                }
                    
            }
            else if (lugar.Text != "" && tipo.Text != "" && fecha.Enabled == false)
            {
                comando = new SqlCommand(string.Format("select * from Evento where Lugar = '{0}' and Categoria = '{1}'", lugar.Text, tipo.Text), conexion);
                conexion.Open();
                dr = comando.ExecuteReader();
                if (dr.Read())
                {
                    existeBusqueda = true;
                }
                conexion.Close();
            }
            else if (lugar.Text == "" && tipo.Text != "" && fecha.Enabled == true)
            {
                comando = new SqlCommand(string.Format("select * from Evento where Categoria = '{0}' and Fecha = '{1}'", tipo.Text, fecha.Text),conexion);
                conexion.Open();
                dr = comando.ExecuteReader();
                if (dr.Read())
                {
                    existeBusqueda = true;
                }
                conexion.Close();
            }
            else if (lugar.Text != "" && tipo.Text == "" && fecha.Enabled == true)
            {
                comando = new SqlCommand(string.Format("select * from Evento where Lugar = '{0}' and Fecha = '{1}'", lugar.Text, fecha.Text), conexion);
                conexion.Open();
                dr = comando.ExecuteReader();
                if (dr.Read())
                {
                    existeBusqueda = true;
                }
                conexion.Close();
            }
            else if (lugar.Text != "" && tipo.Text != "" && fecha.Enabled == true)
            {
                comando = new SqlCommand(string.Format("select * from Evento where Lugar = '{0}' and Fecha = '{1}' and Categoria = '{2}'", lugar.Text, fecha.Text, tipo.Text), conexion);
                conexion.Open();
                dr = comando.ExecuteReader();
                if (dr.Read())
                {
                    existeBusqueda = true;
                }
                conexion.Close();
            }

            //MessageBox.Show(comando.CommandText);
            adaptador = new SqlDataAdapter(comando);
            ds = new DataSet();
            conexion.Open();
            adaptador.Fill(ds);
            setComando(ds);
            conexion.Close();

            setFilas(ds.Tables[0].Rows.Count);

            return existeBusqueda;

        }

        public void despliegaInformacion(Panel pan, string cmd, int filas)
        {
            
        }

    }
    
}