namespace Eventos_administrador
{
    partial class Elimina_evento
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Elimina_evento));
            this.busca_btn = new System.Windows.Forms.Button();
            this.id_txt = new System.Windows.Forms.TextBox();
            this.elimina_btn = new System.Windows.Forms.Button();
            this.cancela_btn = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.fecha_txt = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.imagen_pbx = new System.Windows.Forms.PictureBox();
            this.asisten_txt = new System.Windows.Forms.TextBox();
            this.tipo_cbx = new System.Windows.Forms.ComboBox();
            this.lugar_txt = new System.Windows.Forms.TextBox();
            this.descripcion_txt = new System.Windows.Forms.TextBox();
            this.nombre_txt = new System.Windows.Forms.TextBox();
            this.label7 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.url_txt = new System.Windows.Forms.TextBox();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imagen_pbx)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // busca_btn
            // 
            this.busca_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.busca_btn.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.busca_btn.ForeColor = System.Drawing.Color.White;
            this.busca_btn.Location = new System.Drawing.Point(554, 18);
            this.busca_btn.Name = "busca_btn";
            this.busca_btn.Size = new System.Drawing.Size(170, 38);
            this.busca_btn.TabIndex = 39;
            this.busca_btn.Text = "Buscar";
            this.busca_btn.UseVisualStyleBackColor = false;
            this.busca_btn.Click += new System.EventHandler(this.busca_btn_Click);
            // 
            // id_txt
            // 
            this.id_txt.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.id_txt.Location = new System.Drawing.Point(347, 26);
            this.id_txt.Name = "id_txt";
            this.id_txt.Size = new System.Drawing.Size(194, 25);
            this.id_txt.TabIndex = 33;
            // 
            // elimina_btn
            // 
            this.elimina_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.elimina_btn.Enabled = false;
            this.elimina_btn.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.elimina_btn.ForeColor = System.Drawing.Color.White;
            this.elimina_btn.Location = new System.Drawing.Point(769, 512);
            this.elimina_btn.Name = "elimina_btn";
            this.elimina_btn.Size = new System.Drawing.Size(170, 38);
            this.elimina_btn.TabIndex = 32;
            this.elimina_btn.Text = "Eliminar Eventos";
            this.elimina_btn.UseVisualStyleBackColor = false;
            this.elimina_btn.Click += new System.EventHandler(this.elimina_btn_Click);
            // 
            // cancela_btn
            // 
            this.cancela_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.cancela_btn.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cancela_btn.ForeColor = System.Drawing.Color.White;
            this.cancela_btn.Location = new System.Drawing.Point(577, 512);
            this.cancela_btn.Name = "cancela_btn";
            this.cancela_btn.Size = new System.Drawing.Size(170, 38);
            this.cancela_btn.TabIndex = 31;
            this.cancela_btn.Text = "Cancelar";
            this.cancela_btn.UseVisualStyleBackColor = false;
            this.cancela_btn.Click += new System.EventHandler(this.cancela_btn_Click_1);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.fecha_txt);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label3);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Controls.Add(this.label1);
            this.groupBox2.Controls.Add(this.imagen_pbx);
            this.groupBox2.Controls.Add(this.asisten_txt);
            this.groupBox2.Controls.Add(this.tipo_cbx);
            this.groupBox2.Controls.Add(this.lugar_txt);
            this.groupBox2.Controls.Add(this.descripcion_txt);
            this.groupBox2.Controls.Add(this.nombre_txt);
            this.groupBox2.Location = new System.Drawing.Point(235, 100);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(704, 406);
            this.groupBox2.TabIndex = 40;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "DATOS DEL EVENTO";
            // 
            // fecha_txt
            // 
            this.fecha_txt.Enabled = false;
            this.fecha_txt.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.fecha_txt.Location = new System.Drawing.Point(112, 92);
            this.fecha_txt.Name = "fecha_txt";
            this.fecha_txt.Size = new System.Drawing.Size(189, 25);
            this.fecha_txt.TabIndex = 33;
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.ForeColor = System.Drawing.Color.White;
            this.label6.Location = new System.Drawing.Point(10, 197);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(91, 21);
            this.label6.TabIndex = 32;
            this.label6.Text = "Descripcion";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.ForeColor = System.Drawing.Color.White;
            this.label5.Location = new System.Drawing.Point(21, 164);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(80, 21);
            this.label5.TabIndex = 31;
            this.label5.Text = "Asistentes";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.ForeColor = System.Drawing.Color.White;
            this.label4.Location = new System.Drawing.Point(24, 129);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(77, 21);
            this.label4.TabIndex = 30;
            this.label4.Text = "Categoria";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(51, 93);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(50, 21);
            this.label3.TabIndex = 29;
            this.label3.Text = "Fecha";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(51, 58);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(50, 21);
            this.label2.TabIndex = 28;
            this.label2.Text = "Lugar";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(33, 22);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(68, 21);
            this.label1.TabIndex = 27;
            this.label1.Text = "Nombre";
            // 
            // imagen_pbx
            // 
            this.imagen_pbx.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.imagen_pbx.Location = new System.Drawing.Point(319, 19);
            this.imagen_pbx.Name = "imagen_pbx";
            this.imagen_pbx.Size = new System.Drawing.Size(368, 288);
            this.imagen_pbx.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.imagen_pbx.TabIndex = 26;
            this.imagen_pbx.TabStop = false;
            // 
            // asisten_txt
            // 
            this.asisten_txt.Enabled = false;
            this.asisten_txt.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.asisten_txt.Location = new System.Drawing.Point(112, 163);
            this.asisten_txt.Name = "asisten_txt";
            this.asisten_txt.Size = new System.Drawing.Size(104, 25);
            this.asisten_txt.TabIndex = 24;
            // 
            // tipo_cbx
            // 
            this.tipo_cbx.Enabled = false;
            this.tipo_cbx.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
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
            this.tipo_cbx.Location = new System.Drawing.Point(112, 126);
            this.tipo_cbx.Name = "tipo_cbx";
            this.tipo_cbx.Size = new System.Drawing.Size(189, 25);
            this.tipo_cbx.TabIndex = 22;
            // 
            // lugar_txt
            // 
            this.lugar_txt.Enabled = false;
            this.lugar_txt.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lugar_txt.Location = new System.Drawing.Point(112, 57);
            this.lugar_txt.Name = "lugar_txt";
            this.lugar_txt.Size = new System.Drawing.Size(189, 25);
            this.lugar_txt.TabIndex = 21;
            // 
            // descripcion_txt
            // 
            this.descripcion_txt.Enabled = false;
            this.descripcion_txt.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.descripcion_txt.Location = new System.Drawing.Point(14, 221);
            this.descripcion_txt.Multiline = true;
            this.descripcion_txt.Name = "descripcion_txt";
            this.descripcion_txt.Size = new System.Drawing.Size(287, 166);
            this.descripcion_txt.TabIndex = 23;
            // 
            // nombre_txt
            // 
            this.nombre_txt.Enabled = false;
            this.nombre_txt.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nombre_txt.Location = new System.Drawing.Point(112, 21);
            this.nombre_txt.Name = "nombre_txt";
            this.nombre_txt.Size = new System.Drawing.Size(189, 25);
            this.nombre_txt.TabIndex = 20;
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.ForeColor = System.Drawing.Color.White;
            this.label7.Location = new System.Drawing.Point(245, 26);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(95, 21);
            this.label7.TabIndex = 33;
            this.label7.Text = "Id de Evento";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label8.ForeColor = System.Drawing.Color.White;
            this.label8.Location = new System.Drawing.Point(291, 64);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(39, 21);
            this.label8.TabIndex = 41;
            this.label8.Text = "URL";
            // 
            // url_txt
            // 
            this.url_txt.Enabled = false;
            this.url_txt.Font = new System.Drawing.Font("Segoe UI", 9.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.url_txt.Location = new System.Drawing.Point(347, 64);
            this.url_txt.Name = "url_txt";
            this.url_txt.Size = new System.Drawing.Size(420, 25);
            this.url_txt.TabIndex = 42;
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(213, 183);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 43;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(877, 12);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(95, 59);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 46;
            this.pictureBox2.TabStop = false;
            // 
            // Elimina_evento
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(984, 562);
            this.ControlBox = false;
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label8);
            this.Controls.Add(this.url_txt);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.busca_btn);
            this.Controls.Add(this.id_txt);
            this.Controls.Add(this.elimina_btn);
            this.Controls.Add(this.cancela_btn);
            this.Name = "Elimina_evento";
            this.Text = "Eliminar Evento";
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.imagen_pbx)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button busca_btn;
        private System.Windows.Forms.TextBox id_txt;
        private System.Windows.Forms.Button elimina_btn;
        private System.Windows.Forms.Button cancela_btn;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox imagen_pbx;
        public System.Windows.Forms.TextBox asisten_txt;
        public System.Windows.Forms.ComboBox tipo_cbx;
        public System.Windows.Forms.TextBox lugar_txt;
        public System.Windows.Forms.TextBox descripcion_txt;
        public System.Windows.Forms.TextBox nombre_txt;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox url_txt;
        public System.Windows.Forms.TextBox fecha_txt;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
    }
}