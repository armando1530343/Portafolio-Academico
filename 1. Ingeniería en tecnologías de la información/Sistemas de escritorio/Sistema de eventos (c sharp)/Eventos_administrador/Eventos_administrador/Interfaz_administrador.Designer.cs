namespace Eventos_administrador
{
    partial class Interfaz_administrador
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Interfaz_administrador));
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.gestrinarEventosToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.consultasDeBaseDeDatosToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cambiarDatosDeLaCuentaToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.cerrarSesiónToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(262, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(231, 211);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 45;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(74, 250);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(186, 143);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 46;
            this.pictureBox2.TabStop = false;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Anchor = System.Windows.Forms.AnchorStyles.None;
            this.menuStrip1.BackColor = System.Drawing.Color.LightSeaGreen;
            this.menuStrip1.Dock = System.Windows.Forms.DockStyle.None;
            this.menuStrip1.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.menuStrip1.GripMargin = new System.Windows.Forms.Padding(2);
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.gestrinarEventosToolStripMenuItem,
            this.consultasDeBaseDeDatosToolStripMenuItem,
            this.cambiarDatosDeLaCuentaToolStripMenuItem,
            this.cerrarSesiónToolStripMenuItem});
            this.menuStrip1.LayoutStyle = System.Windows.Forms.ToolStripLayoutStyle.Table;
            this.menuStrip1.Location = new System.Drawing.Point(305, 253);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(285, 159);
            this.menuStrip1.TabIndex = 49;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // gestrinarEventosToolStripMenuItem
            // 
            this.gestrinarEventosToolStripMenuItem.ForeColor = System.Drawing.Color.White;
            this.gestrinarEventosToolStripMenuItem.Name = "gestrinarEventosToolStripMenuItem";
            this.gestrinarEventosToolStripMenuItem.Size = new System.Drawing.Size(202, 34);
            this.gestrinarEventosToolStripMenuItem.Text = "Gestion de Eventos";
            this.gestrinarEventosToolStripMenuItem.Click += new System.EventHandler(this.gestrinarEventosToolStripMenuItem_Click);
            // 
            // consultasDeBaseDeDatosToolStripMenuItem
            // 
            this.consultasDeBaseDeDatosToolStripMenuItem.ForeColor = System.Drawing.Color.White;
            this.consultasDeBaseDeDatosToolStripMenuItem.Name = "consultasDeBaseDeDatosToolStripMenuItem";
            this.consultasDeBaseDeDatosToolStripMenuItem.Size = new System.Drawing.Size(279, 34);
            this.consultasDeBaseDeDatosToolStripMenuItem.Text = "Consultas de Base de datos";
            this.consultasDeBaseDeDatosToolStripMenuItem.Click += new System.EventHandler(this.consultasDeBaseDeDatosToolStripMenuItem_Click);
            // 
            // cambiarDatosDeLaCuentaToolStripMenuItem
            // 
            this.cambiarDatosDeLaCuentaToolStripMenuItem.ForeColor = System.Drawing.Color.White;
            this.cambiarDatosDeLaCuentaToolStripMenuItem.Name = "cambiarDatosDeLaCuentaToolStripMenuItem";
            this.cambiarDatosDeLaCuentaToolStripMenuItem.Size = new System.Drawing.Size(279, 34);
            this.cambiarDatosDeLaCuentaToolStripMenuItem.Text = "Cambiar datos de la cuenta";
            this.cambiarDatosDeLaCuentaToolStripMenuItem.Click += new System.EventHandler(this.cambiarDatosDeLaCuentaToolStripMenuItem_Click);
            // 
            // cerrarSesiónToolStripMenuItem
            // 
            this.cerrarSesiónToolStripMenuItem.ForeColor = System.Drawing.Color.White;
            this.cerrarSesiónToolStripMenuItem.Name = "cerrarSesiónToolStripMenuItem";
            this.cerrarSesiónToolStripMenuItem.Size = new System.Drawing.Size(147, 34);
            this.cerrarSesiónToolStripMenuItem.Text = "Cerrar Sesión";
            this.cerrarSesiónToolStripMenuItem.Click += new System.EventHandler(this.cerrarSesiónToolStripMenuItem_Click);
            // 
            // Interfaz_administrador
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(784, 462);
            this.ControlBox = false;
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.Name = "Interfaz_administrador";
            this.Text = "Interfaz_administrador";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem gestrinarEventosToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem consultasDeBaseDeDatosToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cambiarDatosDeLaCuentaToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem cerrarSesiónToolStripMenuItem;
    }
}