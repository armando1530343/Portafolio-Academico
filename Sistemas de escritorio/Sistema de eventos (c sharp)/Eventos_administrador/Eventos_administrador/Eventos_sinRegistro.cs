using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Data;
using System.Data.SqlClient;
using System.IO;

namespace Eventos_administrador
{
    public partial class Eventos_sinRegistro : Form
    {
        static int filas;
        static Panel[] Eventos;

        bool normal;
              
        public Eventos_sinRegistro(bool n)
        {
            InitializeComponent();
            filas = 0;
            normal = n;
        }

        public static void setFilas(int f)
        {
            filas = f;
        }
        public static Panel[] getEventos()
        {
            return Eventos;
        }
        public static void setEventos(Panel[] ev)
        {
            Eventos = ev;
        }
        public static int getFilas()
        {
            return filas;
        }

        
        
        //int filas = ds.Tables[0].Rows.Count;

        private void evento_panel_Paint(object sender, PaintEventArgs e)
        {
            
            
            
        }


        public Label crearCaja(int x, int y, int w, int h, Color color, string cadena)
        {
            Label lab = new Label();
            lab.Location = new Point(x, y);
            lab.Width = w;
            lab.Height = h;
            lab.Font = new Font("Segoe UI", 10);
            lab.ForeColor = color;
            lab.Text = cadena;
            lab.AutoSize = true;
            return lab;
        }
        public PictureBox crearImagen(DataSet ds, int fila)
        {
            PictureBox img = new PictureBox();
            img.Location = new Point(pictureBox1.Location.X, pictureBox1.Location.Y);
            img.Width = 381;
            img.Height = 193;
            img.SizeMode = PictureBoxSizeMode.StretchImage;
            byte[] datos = new byte[0];
            DataRow dr = ds.Tables[0].Rows[fila];
            datos = (byte[])dr["Imagen"];
            MemoryStream ms = new MemoryStream(datos);
            img.Image = System.Drawing.Bitmap.FromStream(ms);
            return img;
        }

        public Panel crearPanel(int x, int y)
        {
            Panel pan = new Panel();
            pan.Width = 515;
            pan.Height = 120;
            pan.AutoScroll = true;
            pan.BorderStyle = BorderStyle.FixedSingle;
            pan.Location = new Point(x, y);
            return pan;
        }

        public Button crearBoton(int x, int y, string texto, bool ena, Color color)
        {
            Button btn = new Button();
            btn.Location = new Point(x, y);
            btn.Width = 137;
            btn.Height = 28;
            btn.Font = new Font("Segoe UI", 10);
            btn.Text = texto;
            btn.Enabled = ena;

            return btn;
        }

        private void Eventos_sinRegistro_Load(object sender, EventArgs e)
        {
            //int filas = ds.Tables[0].Rows.Count;
            DataSet ds = Evento.getComando();
            setFilas(ds.Tables[0].Rows.Count);
            Panel[] eventos = new Panel[getFilas()];
            
            int i;
            int noPagina = 1;


            for (i = 0; i < getFilas(); i++)
            {
                eventos[i] = new Panel();
                eventos[i].Location = new Point(10, 10);
                eventos[i].Width = evento_panel.Width - 10;
                eventos[i].Height = evento_panel.Height - 10;
                eventos[i].BorderStyle = BorderStyle.FixedSingle;
                //panel1.AutoScroll = true;

                PictureBox imagen = crearImagen(ds, i);


                Label texto1 = crearCaja(411, 23, 515, 20, Color.Red,
                    "Nombre: " + ds.Tables[0].Rows[i]["Nombre"].ToString());

                Label texto2 = crearCaja(label2.Location.X, label2.Location.Y, 515, 20, Color.White,
                    "Lugar: " + ds.Tables[0].Rows[i]["Lugar"].ToString());

                Label texto3 = crearCaja(label3.Location.X, label3.Location.Y, 515, 20, Color.White,
                    "Fecha: " + ds.Tables[0].Rows[i]["Fecha"].ToString());

                Label texto4 = crearCaja(label4.Location.X, label4.Location.Y, 515, 20, Color.White,
                    "Categoria: " + ds.Tables[0].Rows[i]["Categoria"].ToString());

                Label texto5 = crearCaja(label5.Location.X, label5.Location.Y, 515, 20, Color.White,
                    "Asistentes: " + ds.Tables[0].Rows[i]["Asistentes"].ToString());

                Label texto6 = crearCaja(label6.Location.X, label6.Location.Y, 120, 20, Color.Yellow, "Calificar Evento: ");
                texto6.Visible = !normal;

                Label texto7 = crearCaja(label7.Location.X, label7.Location.Y, 80, 20, Color.Yellow, "Estrellas");
                texto7.Visible = !normal;

                Label texto8 = crearCaja(label8.Location.X, label8.Location.Y, 515, 20, Color.White,
                    "Descripcion: " + ds.Tables[0].Rows[i]["Descripcion"].ToString());
                
                Label texto9 = crearCaja(label9.Location.X, label9.Location.Y, label9.Width, label9.Height, Color.White,
                    "Pagina " + noPagina);
                texto9.Name = "pag" + noPagina;

                Panel desc = crearPanel(panel1.Location.X, panel1.Location.Y);

                desc.Controls.Add(texto8);

                ComboBox cbox = new ComboBox();
                cbox.Location = new Point(comboBox1.Location.X, comboBox1.Location.Y);
                cbox.Width = 50;
                cbox.Height = 25;
                cbox.Font = new Font("Segoe UI", 10);
                cbox.Items.Add(1);
                cbox.Items.Add(2);
                cbox.Items.Add(3);
                cbox.Items.Add(4);
                cbox.Items.Add(5);
                cbox.Visible = !normal;

                CheckBox check = new CheckBox();
                check.Location = new Point(187, 270);
                check.Text = "Asistir al Evento";
                check.Width = checkBox1.Width;
                check.Height = checkBox1.Height;
                check.Font = new Font("Segoe UI", 10);
                check.Visible = !normal;

                bool enable1 = false;
                bool enable2 = false;

                if (i == 0 && filas == 1)
                {
                    enable1 = false;
                    enable2 = false;
                }
                else if (i == 0 && filas > 1)
                {
                    enable1 = false;
                    enable2 = true;
                }
                else if (i > 1 && i < filas - 1)
                {
                    enable1 = true;
                    enable2 = true;
                }
                else if (i == filas - 1)
                {
                    enable1 = true;
                    enable2 = false;
                }


                Button anterior = crearBoton(345, 331, "Anterior", enable1, Color.DarkSeaGreen);
                Button siguiente = crearBoton(505, 331, "Siguiente", enable2, Color.DarkSeaGreen);
                anterior.Click += anterior_Click;
                siguiente.Click += siguiente_Click;



                eventos[i].Controls.Add(texto1);
                eventos[i].Controls.Add(texto2);
                eventos[i].Controls.Add(texto3);
                eventos[i].Controls.Add(texto4);
                eventos[i].Controls.Add(texto5);
                eventos[i].Controls.Add(texto6);
                eventos[i].Controls.Add(texto7);
                eventos[i].Controls.Add(texto9);
                eventos[i].Controls.Add(imagen);
                eventos[i].Controls.Add(cbox);
                eventos[i].Controls.Add(desc);
                eventos[i].Controls.Add(check);
                eventos[i].Controls.Add(anterior);
                eventos[i].Controls.Add(siguiente);

                noPagina++;

            }
            evento_panel.Controls.Add(eventos[0]);
            setEventos(eventos);
            
        }

        int pag = 0;
        void siguiente_Click(object sender, EventArgs e)
        {
            Panel[] p = getEventos();
            pag++;
            evento_panel.Controls.Clear();
            evento_panel.Controls.Add(p[pag]);
        }

        void anterior_Click(object sender, EventArgs e)
        {
            Panel[] p = getEventos();
            int i;
            pag--;
            evento_panel.Controls.Clear();
            evento_panel.Controls.Add(p[pag]);
            
        }

        private void ant_btn_Click(object sender, EventArgs e)
        {

        }
       
    }
}