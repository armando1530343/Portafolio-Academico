namespace Eventos_administrador
{
    partial class paginaPrincipal
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(paginaPrincipal));
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.iniciaSesion_menu = new System.Windows.Forms.ToolStripMenuItem();
            this.registro_menu = new System.Windows.Forms.ToolStripMenuItem();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.buscar_btn = new System.Windows.Forms.Button();
            this.evento_txt = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.label = new System.Windows.Forms.Label();
            this.fecha_txt = new System.Windows.Forms.DateTimePicker();
            this.tipo_lab = new System.Windows.Forms.Label();
            this.fecha_lab = new System.Windows.Forms.Label();
            this.lugar_lab = new System.Windows.Forms.Label();
            this.tipo_cbx = new System.Windows.Forms.ComboBox();
            this.lugar_cbx = new System.Windows.Forms.ComboBox();
            this.buscar2_btn = new System.Windows.Forms.Button();
            this.panel1 = new System.Windows.Forms.Panel();
            this.user_lab = new System.Windows.Forms.Label();
            this.menuStrip2 = new System.Windows.Forms.MenuStrip();
            this.toolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStrip1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.menuStrip2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.menuStrip1.BackColor = System.Drawing.Color.LightSeaGreen;
            this.menuStrip1.Dock = System.Windows.Forms.DockStyle.None;
            this.menuStrip1.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.iniciaSesion_menu,
            this.registro_menu});
            this.menuStrip1.Location = new System.Drawing.Point(759, 3);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(222, 29);
            this.menuStrip1.TabIndex = 3;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // iniciaSesion_menu
            // 
            this.iniciaSesion_menu.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.iniciaSesion_menu.ForeColor = System.Drawing.Color.White;
            this.iniciaSesion_menu.Name = "iniciaSesion_menu";
            this.iniciaSesion_menu.Size = new System.Drawing.Size(114, 25);
            this.iniciaSesion_menu.Text = "Iniciar Sesión";
            this.iniciaSesion_menu.Click += new System.EventHandler(this.iniciaSesion_menu_Click);
            // 
            // registro_menu
            // 
            this.registro_menu.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.registro_menu.ForeColor = System.Drawing.Color.White;
            this.registro_menu.Name = "registro_menu";
            this.registro_menu.Size = new System.Drawing.Size(100, 25);
            this.registro_menu.Text = "Registrarse";
            this.registro_menu.Click += new System.EventHandler(this.registro_menu_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(244, 190);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 47;
            this.pictureBox1.TabStop = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.buscar_btn);
            this.groupBox1.Controls.Add(this.evento_txt);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.groupBox2);
            this.groupBox1.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.groupBox1.Location = new System.Drawing.Point(12, 208);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(677, 392);
            this.groupBox1.TabIndex = 48;
            this.groupBox1.TabStop = false;
            // 
            // buscar_btn
            // 
            this.buscar_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.buscar_btn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buscar_btn.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buscar_btn.ForeColor = System.Drawing.Color.White;
            this.buscar_btn.Location = new System.Drawing.Point(506, 26);
            this.buscar_btn.Name = "buscar_btn";
            this.buscar_btn.Size = new System.Drawing.Size(161, 46);
            this.buscar_btn.TabIndex = 21;
            this.buscar_btn.Text = "Buscar";
            this.buscar_btn.UseVisualStyleBackColor = false;
            this.buscar_btn.Click += new System.EventHandler(this.buscar_btn_Click_1);
            // 
            // evento_txt
            // 
            this.evento_txt.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.evento_txt.Location = new System.Drawing.Point(188, 36);
            this.evento_txt.Name = "evento_txt";
            this.evento_txt.Size = new System.Drawing.Size(312, 29);
            this.evento_txt.TabIndex = 23;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(11, 39);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(171, 21);
            this.label1.TabIndex = 22;
            this.label1.Text = "NOMBRE DEL EVENTO:";
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.label);
            this.groupBox2.Controls.Add(this.fecha_txt);
            this.groupBox2.Controls.Add(this.tipo_lab);
            this.groupBox2.Controls.Add(this.fecha_lab);
            this.groupBox2.Controls.Add(this.lugar_lab);
            this.groupBox2.Controls.Add(this.tipo_cbx);
            this.groupBox2.Controls.Add(this.lugar_cbx);
            this.groupBox2.Controls.Add(this.buscar2_btn);
            this.groupBox2.ForeColor = System.Drawing.Color.White;
            this.groupBox2.Location = new System.Drawing.Point(11, 86);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(656, 252);
            this.groupBox2.TabIndex = 20;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "MAS BUSQUEDAS";
            // 
            // label
            // 
            this.label.AutoSize = true;
            this.label.Cursor = System.Windows.Forms.Cursors.Hand;
            this.label.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Underline, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label.ForeColor = System.Drawing.Color.Black;
            this.label.Location = new System.Drawing.Point(309, 109);
            this.label.Name = "label";
            this.label.Size = new System.Drawing.Size(29, 13);
            this.label.TabIndex = 18;
            this.label.Text = "label";
            this.label.Click += new System.EventHandler(this.label_Click_1);
            // 
            // fecha_txt
            // 
            this.fecha_txt.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fecha_txt.Location = new System.Drawing.Point(223, 67);
            this.fecha_txt.Name = "fecha_txt";
            this.fecha_txt.Size = new System.Drawing.Size(210, 29);
            this.fecha_txt.TabIndex = 17;
            // 
            // tipo_lab
            // 
            this.tipo_lab.AutoSize = true;
            this.tipo_lab.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tipo_lab.ForeColor = System.Drawing.Color.White;
            this.tipo_lab.Location = new System.Drawing.Point(497, 32);
            this.tipo_lab.Name = "tipo_lab";
            this.tipo_lab.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.tipo_lab.Size = new System.Drawing.Size(93, 21);
            this.tipo_lab.TabIndex = 16;
            this.tipo_lab.Text = "CATEGORIA";
            // 
            // fecha_lab
            // 
            this.fecha_lab.AutoSize = true;
            this.fecha_lab.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fecha_lab.ForeColor = System.Drawing.Color.White;
            this.fecha_lab.Location = new System.Drawing.Point(298, 32);
            this.fecha_lab.Name = "fecha_lab";
            this.fecha_lab.Size = new System.Drawing.Size(57, 21);
            this.fecha_lab.TabIndex = 15;
            this.fecha_lab.Text = "FECHA";
            // 
            // lugar_lab
            // 
            this.lugar_lab.AutoSize = true;
            this.lugar_lab.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lugar_lab.ForeColor = System.Drawing.Color.White;
            this.lugar_lab.Location = new System.Drawing.Point(81, 32);
            this.lugar_lab.Name = "lugar_lab";
            this.lugar_lab.Size = new System.Drawing.Size(60, 21);
            this.lugar_lab.TabIndex = 14;
            this.lugar_lab.Text = "LUGAR";
            // 
            // tipo_cbx
            // 
            this.tipo_cbx.BackColor = System.Drawing.SystemColors.Window;
            this.tipo_cbx.Cursor = System.Windows.Forms.Cursors.Hand;
            this.tipo_cbx.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.tipo_cbx.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.tipo_cbx.ForeColor = System.Drawing.Color.Black;
            this.tipo_cbx.FormattingEnabled = true;
            this.tipo_cbx.Items.AddRange(new object[] {
            "Cultural",
            "Musical",
            "Infantil",
            "Festival",
            "Exposicion",
            "Educativo",
            "Social",
            "Presentacion"});
            this.tipo_cbx.Location = new System.Drawing.Point(437, 67);
            this.tipo_cbx.Name = "tipo_cbx";
            this.tipo_cbx.Size = new System.Drawing.Size(210, 29);
            this.tipo_cbx.TabIndex = 13;
            // 
            // lugar_cbx
            // 
            this.lugar_cbx.BackColor = System.Drawing.SystemColors.Window;
            this.lugar_cbx.Cursor = System.Windows.Forms.Cursors.Hand;
            this.lugar_cbx.FlatStyle = System.Windows.Forms.FlatStyle.Popup;
            this.lugar_cbx.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lugar_cbx.ForeColor = System.Drawing.Color.Black;
            this.lugar_cbx.FormattingEnabled = true;
            this.lugar_cbx.Location = new System.Drawing.Point(8, 67);
            this.lugar_cbx.Name = "lugar_cbx";
            this.lugar_cbx.Size = new System.Drawing.Size(210, 29);
            this.lugar_cbx.TabIndex = 12;
            // 
            // buscar2_btn
            // 
            this.buscar2_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.buscar2_btn.Cursor = System.Windows.Forms.Cursors.Hand;
            this.buscar2_btn.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.buscar2_btn.Location = new System.Drawing.Point(251, 185);
            this.buscar2_btn.Name = "buscar2_btn";
            this.buscar2_btn.Size = new System.Drawing.Size(161, 46);
            this.buscar2_btn.TabIndex = 11;
            this.buscar2_btn.Text = "Buscar Evento";
            this.buscar2_btn.UseVisualStyleBackColor = false;
            this.buscar2_btn.Click += new System.EventHandler(this.buscar2_btn_Click_1);
            // 
            // panel1
            // 
            this.panel1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.panel1.Location = new System.Drawing.Point(695, 208);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(277, 392);
            this.panel1.TabIndex = 49;
            // 
            // user_lab
            // 
            this.user_lab.AutoSize = true;
            this.user_lab.Font = new System.Drawing.Font("Segoe UI", 18F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.user_lab.ForeColor = System.Drawing.Color.White;
            this.user_lab.Location = new System.Drawing.Point(358, 95);
            this.user_lab.Name = "user_lab";
            this.user_lab.Size = new System.Drawing.Size(0, 32);
            this.user_lab.TabIndex = 24;
            // 
            // menuStrip2
            // 
            this.menuStrip2.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Top | System.Windows.Forms.AnchorStyles.Right)));
            this.menuStrip2.BackColor = System.Drawing.Color.LightSeaGreen;
            this.menuStrip2.Dock = System.Windows.Forms.DockStyle.None;
            this.menuStrip2.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.menuStrip2.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.toolStripMenuItem1});
            this.menuStrip2.Location = new System.Drawing.Point(857, 3);
            this.menuStrip2.Name = "menuStrip2";
            this.menuStrip2.Size = new System.Drawing.Size(124, 29);
            this.menuStrip2.TabIndex = 50;
            this.menuStrip2.Text = "menuStrip2";
            // 
            // toolStripMenuItem1
            // 
            this.toolStripMenuItem1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.toolStripMenuItem1.ForeColor = System.Drawing.Color.White;
            this.toolStripMenuItem1.Name = "toolStripMenuItem1";
            this.toolStripMenuItem1.Size = new System.Drawing.Size(116, 25);
            this.toolStripMenuItem1.Text = "Cerrar Sesion";
            this.toolStripMenuItem1.Click += new System.EventHandler(this.toolStripMenuItem1_Click_1);
            // 
            // paginaPrincipal
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(984, 612);
            this.Controls.Add(this.menuStrip2);
            this.Controls.Add(this.user_lab);
            this.Controls.Add(this.panel1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.menuStrip1);
            this.MaximumSize = new System.Drawing.Size(1000, 650);
            this.MinimumSize = new System.Drawing.Size(1000, 650);
            this.Name = "paginaPrincipal";
            this.Text = "paginaPrincipal";
            this.Load += new System.EventHandler(this.paginaPrincipal_Load);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.menuStrip2.ResumeLayout(false);
            this.menuStrip2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem iniciaSesion_menu;
        private System.Windows.Forms.ToolStripMenuItem registro_menu;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button buscar_btn;
        private System.Windows.Forms.TextBox evento_txt;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label;
        private System.Windows.Forms.DateTimePicker fecha_txt;
        private System.Windows.Forms.Label tipo_lab;
        private System.Windows.Forms.Label fecha_lab;
        private System.Windows.Forms.Label lugar_lab;
        private System.Windows.Forms.ComboBox tipo_cbx;
        private System.Windows.Forms.ComboBox lugar_cbx;
        private System.Windows.Forms.Button buscar2_btn;
        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.MenuStrip menuStrip2;
        private System.Windows.Forms.ToolStripMenuItem toolStripMenuItem1;
        public System.Windows.Forms.Label user_lab;
    }
}