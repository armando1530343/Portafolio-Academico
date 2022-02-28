namespace Eventos_administrador
{
    partial class Cambiar_contraseña
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Cambiar_contraseña));
            this.cancela_btn = new System.Windows.Forms.Button();
            this.guardar_btn = new System.Windows.Forms.Button();
            this.nvaCuenta_txt = new System.Windows.Forms.TextBox();
            this.nvaPass_txt = new System.Windows.Forms.TextBox();
            this.nvaPass2_txt = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.pictureBox2 = new System.Windows.Forms.PictureBox();
            this.groupBox1.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).BeginInit();
            this.SuspendLayout();
            // 
            // cancela_btn
            // 
            this.cancela_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.cancela_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cancela_btn.ForeColor = System.Drawing.Color.White;
            this.cancela_btn.Location = new System.Drawing.Point(606, 378);
            this.cancela_btn.Name = "cancela_btn";
            this.cancela_btn.Size = new System.Drawing.Size(146, 48);
            this.cancela_btn.TabIndex = 10;
            this.cancela_btn.Text = "Cancelar";
            this.cancela_btn.UseVisualStyleBackColor = false;
            this.cancela_btn.Click += new System.EventHandler(this.cancela_btn_Click);
            // 
            // guardar_btn
            // 
            this.guardar_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.guardar_btn.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.guardar_btn.ForeColor = System.Drawing.Color.White;
            this.guardar_btn.Location = new System.Drawing.Point(324, 378);
            this.guardar_btn.Name = "guardar_btn";
            this.guardar_btn.Size = new System.Drawing.Size(146, 46);
            this.guardar_btn.TabIndex = 9;
            this.guardar_btn.Text = "Guardar";
            this.guardar_btn.UseVisualStyleBackColor = false;
            this.guardar_btn.Click += new System.EventHandler(this.guardar_btn_Click);
            // 
            // nvaCuenta_txt
            // 
            this.nvaCuenta_txt.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nvaCuenta_txt.Location = new System.Drawing.Point(78, 56);
            this.nvaCuenta_txt.Name = "nvaCuenta_txt";
            this.nvaCuenta_txt.Size = new System.Drawing.Size(282, 35);
            this.nvaCuenta_txt.TabIndex = 11;
            // 
            // nvaPass_txt
            // 
            this.nvaPass_txt.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nvaPass_txt.Location = new System.Drawing.Point(78, 156);
            this.nvaPass_txt.Name = "nvaPass_txt";
            this.nvaPass_txt.Size = new System.Drawing.Size(282, 35);
            this.nvaPass_txt.TabIndex = 12;
            this.nvaPass_txt.UseSystemPasswordChar = true;
            // 
            // nvaPass2_txt
            // 
            this.nvaPass2_txt.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nvaPass2_txt.Location = new System.Drawing.Point(78, 256);
            this.nvaPass2_txt.Name = "nvaPass2_txt";
            this.nvaPass2_txt.Size = new System.Drawing.Size(282, 35);
            this.nvaPass2_txt.TabIndex = 13;
            this.nvaPass2_txt.UseSystemPasswordChar = true;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.ForeColor = System.Drawing.Color.White;
            this.label1.Location = new System.Drawing.Point(73, 23);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(155, 30);
            this.label1.TabIndex = 14;
            this.label1.Text = "Nuevo Usuario:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.nvaCuenta_txt);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.nvaPass_txt);
            this.groupBox1.Controls.Add(this.nvaPass2_txt);
            this.groupBox1.Location = new System.Drawing.Point(324, 34);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(428, 324);
            this.groupBox1.TabIndex = 15;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "groupBox1";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.ForeColor = System.Drawing.Color.White;
            this.label3.Location = new System.Drawing.Point(73, 223);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(216, 30);
            this.label3.TabIndex = 16;
            this.label3.Text = "Confirmar Contraseña";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(73, 123);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(189, 30);
            this.label2.TabIndex = 15;
            this.label2.Text = "Nueva Contraseña:";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 13);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(253, 212);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 16;
            this.pictureBox1.TabStop = false;
            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox2.Image")));
            this.pictureBox2.Location = new System.Drawing.Point(12, 391);
            this.pictureBox2.Name = "pictureBox2";
            this.pictureBox2.Size = new System.Drawing.Size(95, 59);
            this.pictureBox2.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox2.TabIndex = 46;
            this.pictureBox2.TabStop = false;
            // 
            // Cambiar_contraseña
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(784, 462);
            this.ControlBox = false;
            this.Controls.Add(this.pictureBox2);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.cancela_btn);
            this.Controls.Add(this.guardar_btn);
            this.MaximumSize = new System.Drawing.Size(800, 500);
            this.MinimumSize = new System.Drawing.Size(800, 500);
            this.Name = "Cambiar_contraseña";
            this.Text = "Cambiar datos de la Cuenta";
            this.Load += new System.EventHandler(this.Cambiar_contraseña_Load);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox2)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button cancela_btn;
        private System.Windows.Forms.Button guardar_btn;
        private System.Windows.Forms.TextBox nvaCuenta_txt;
        private System.Windows.Forms.TextBox nvaPass_txt;
        private System.Windows.Forms.TextBox nvaPass2_txt;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.PictureBox pictureBox2;
    }
}