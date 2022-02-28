namespace Eventos_administrador
{
    partial class Consultas_BD
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Consultas_BD));
            this.comando_txt = new System.Windows.Forms.TextBox();
            this.ejecutar_btn = new System.Windows.Forms.Button();
            this.consultas_dgv = new System.Windows.Forms.DataGridView();
            this.salir_btn = new System.Windows.Forms.Button();
            this.usev_btn = new System.Windows.Forms.Button();
            this.usuario_btn = new System.Windows.Forms.Button();
            this.evento_btn = new System.Windows.Forms.Button();
            this.admin_btn = new System.Windows.Forms.Button();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label1 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.consultas_dgv)).BeginInit();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // comando_txt
            // 
            this.comando_txt.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.comando_txt.Location = new System.Drawing.Point(377, 159);
            this.comando_txt.Name = "comando_txt";
            this.comando_txt.Size = new System.Drawing.Size(413, 29);
            this.comando_txt.TabIndex = 5;
            // 
            // ejecutar_btn
            // 
            this.ejecutar_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.ejecutar_btn.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ejecutar_btn.ForeColor = System.Drawing.Color.White;
            this.ejecutar_btn.Location = new System.Drawing.Point(803, 151);
            this.ejecutar_btn.Name = "ejecutar_btn";
            this.ejecutar_btn.Size = new System.Drawing.Size(149, 43);
            this.ejecutar_btn.TabIndex = 6;
            this.ejecutar_btn.Text = "Ejecutar";
            this.ejecutar_btn.UseVisualStyleBackColor = false;
            this.ejecutar_btn.Click += new System.EventHandler(this.ejecutar_btn_Click);
            // 
            // consultas_dgv
            // 
            this.consultas_dgv.BackgroundColor = System.Drawing.Color.MediumTurquoise;
            this.consultas_dgv.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.consultas_dgv.Location = new System.Drawing.Point(278, 212);
            this.consultas_dgv.Name = "consultas_dgv";
            this.consultas_dgv.Size = new System.Drawing.Size(674, 251);
            this.consultas_dgv.TabIndex = 7;
            // 
            // salir_btn
            // 
            this.salir_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.salir_btn.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.salir_btn.ForeColor = System.Drawing.Color.White;
            this.salir_btn.Location = new System.Drawing.Point(540, 486);
            this.salir_btn.Name = "salir_btn";
            this.salir_btn.Size = new System.Drawing.Size(168, 64);
            this.salir_btn.TabIndex = 8;
            this.salir_btn.Text = "Salir";
            this.salir_btn.UseVisualStyleBackColor = false;
            this.salir_btn.Click += new System.EventHandler(this.salir_btn_Click);
            // 
            // usev_btn
            // 
            this.usev_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.usev_btn.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.usev_btn.ForeColor = System.Drawing.Color.White;
            this.usev_btn.Location = new System.Drawing.Point(22, 229);
            this.usev_btn.Name = "usev_btn";
            this.usev_btn.Size = new System.Drawing.Size(161, 46);
            this.usev_btn.TabIndex = 21;
            this.usev_btn.Text = "Usuario_Evento";
            this.usev_btn.UseVisualStyleBackColor = false;
            this.usev_btn.Click += new System.EventHandler(this.usev_btn_Click);
            // 
            // usuario_btn
            // 
            this.usuario_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.usuario_btn.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.usuario_btn.ForeColor = System.Drawing.Color.White;
            this.usuario_btn.Location = new System.Drawing.Point(22, 164);
            this.usuario_btn.Name = "usuario_btn";
            this.usuario_btn.Size = new System.Drawing.Size(161, 46);
            this.usuario_btn.TabIndex = 20;
            this.usuario_btn.Text = "Usuario";
            this.usuario_btn.UseVisualStyleBackColor = false;
            this.usuario_btn.Click += new System.EventHandler(this.usuario_btn_Click);
            // 
            // evento_btn
            // 
            this.evento_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.evento_btn.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.evento_btn.ForeColor = System.Drawing.Color.White;
            this.evento_btn.Location = new System.Drawing.Point(22, 102);
            this.evento_btn.Name = "evento_btn";
            this.evento_btn.Size = new System.Drawing.Size(161, 46);
            this.evento_btn.TabIndex = 19;
            this.evento_btn.Text = "Evento";
            this.evento_btn.UseVisualStyleBackColor = false;
            this.evento_btn.Click += new System.EventHandler(this.evento_btn_Click);
            // 
            // admin_btn
            // 
            this.admin_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.admin_btn.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.admin_btn.ForeColor = System.Drawing.Color.White;
            this.admin_btn.Location = new System.Drawing.Point(22, 38);
            this.admin_btn.Name = "admin_btn";
            this.admin_btn.Size = new System.Drawing.Size(161, 46);
            this.admin_btn.TabIndex = 18;
            this.admin_btn.Text = "Administrador";
            this.admin_btn.UseVisualStyleBackColor = false;
            this.admin_btn.Click += new System.EventHandler(this.admin_btn_Click);
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.usev_btn);
            this.groupBox1.Controls.Add(this.admin_btn);
            this.groupBox1.Controls.Add(this.usuario_btn);
            this.groupBox1.Controls.Add(this.evento_btn);
            this.groupBox1.Location = new System.Drawing.Point(12, 200);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(206, 319);
            this.groupBox1.TabIndex = 22;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(257, 162);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(114, 21);
            this.label1.TabIndex = 23;
            this.label1.Text = "Comando SQL:";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(206, 182);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 24;
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
            // Consultas_BD
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(984, 562);
            this.ControlBox = false;
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.salir_btn);
            this.Controls.Add(this.consultas_dgv);
            this.Controls.Add(this.ejecutar_btn);
            this.Controls.Add(this.comando_txt);
            this.Name = "Consultas_BD";
            this.Text = "Consultas de la Base de Datos";
            ((System.ComponentModel.ISupportInitialize)(this.consultas_dgv)).EndInit();
            this.groupBox1.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox comando_txt;
        private System.Windows.Forms.Button ejecutar_btn;
        private System.Windows.Forms.DataGridView consultas_dgv;
        private System.Windows.Forms.Button salir_btn;
        private System.Windows.Forms.Button usev_btn;
        private System.Windows.Forms.Button usuario_btn;
        private System.Windows.Forms.Button evento_btn;
        private System.Windows.Forms.Button admin_btn;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
    }
}