namespace Eventos_administrador
{
    partial class RegistroUsuario
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(RegistroUsuario));
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.pass2_txt = new System.Windows.Forms.TextBox();
            this.pass1_txt = new System.Windows.Forms.TextBox();
            this.usuario_txt = new System.Windows.Forms.TextBox();
            this.edad_txt = new System.Windows.Forms.TextBox();
            this.apellido_txt = new System.Windows.Forms.TextBox();
            this.nombre_txt = new System.Windows.Forms.TextBox();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.busca_btn = new System.Windows.Forms.Button();
            this.button1 = new System.Windows.Forms.Button();
            this.limpia_btn = new System.Windows.Forms.Button();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(12, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(181, 150);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 18;
            this.pictureBox1.TabStop = false;
            // 
            // label7
            // 
            this.label7.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label7.Font = new System.Drawing.Font("Segoe UI", 20.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label7.Location = new System.Drawing.Point(291, 12);
            this.label7.Name = "label7";
            this.label7.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label7.Size = new System.Drawing.Size(300, 40);
            this.label7.TabIndex = 19;
            this.label7.Text = "REGISTRO DE USUARIO";
            this.label7.Visible = false;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.pass2_txt);
            this.groupBox1.Controls.Add(this.pass1_txt);
            this.groupBox1.Controls.Add(this.usuario_txt);
            this.groupBox1.Controls.Add(this.edad_txt);
            this.groupBox1.Controls.Add(this.apellido_txt);
            this.groupBox1.Controls.Add(this.nombre_txt);
            this.groupBox1.Controls.Add(this.label6);
            this.groupBox1.Controls.Add(this.label5);
            this.groupBox1.Controls.Add(this.label4);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Location = new System.Drawing.Point(199, 75);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(554, 316);
            this.groupBox1.TabIndex = 20;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "FORMULARIO DE DATOS";
            // 
            // pass2_txt
            // 
            this.pass2_txt.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pass2_txt.Location = new System.Drawing.Point(180, 261);
            this.pass2_txt.Name = "pass2_txt";
            this.pass2_txt.Size = new System.Drawing.Size(345, 33);
            this.pass2_txt.TabIndex = 31;
            this.pass2_txt.UseSystemPasswordChar = true;
            // 
            // pass1_txt
            // 
            this.pass1_txt.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pass1_txt.Location = new System.Drawing.Point(180, 217);
            this.pass1_txt.Name = "pass1_txt";
            this.pass1_txt.Size = new System.Drawing.Size(345, 33);
            this.pass1_txt.TabIndex = 30;
            this.pass1_txt.UseSystemPasswordChar = true;
            // 
            // usuario_txt
            // 
            this.usuario_txt.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.usuario_txt.Location = new System.Drawing.Point(180, 172);
            this.usuario_txt.Name = "usuario_txt";
            this.usuario_txt.Size = new System.Drawing.Size(345, 33);
            this.usuario_txt.TabIndex = 29;
            // 
            // edad_txt
            // 
            this.edad_txt.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.edad_txt.Location = new System.Drawing.Point(180, 127);
            this.edad_txt.Name = "edad_txt";
            this.edad_txt.Size = new System.Drawing.Size(345, 33);
            this.edad_txt.TabIndex = 28;
            this.edad_txt.KeyPress += new System.Windows.Forms.KeyPressEventHandler(this.edad_txt_KeyPress);
            // 
            // apellido_txt
            // 
            this.apellido_txt.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.apellido_txt.Location = new System.Drawing.Point(180, 81);
            this.apellido_txt.Name = "apellido_txt";
            this.apellido_txt.Size = new System.Drawing.Size(345, 33);
            this.apellido_txt.TabIndex = 27;
            // 
            // nombre_txt
            // 
            this.nombre_txt.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.nombre_txt.Location = new System.Drawing.Point(180, 37);
            this.nombre_txt.Name = "nombre_txt";
            this.nombre_txt.Size = new System.Drawing.Size(345, 33);
            this.nombre_txt.TabIndex = 21;
            // 
            // label6
            // 
            this.label6.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label6.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label6.Location = new System.Drawing.Point(6, 262);
            this.label6.Name = "label6";
            this.label6.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label6.Size = new System.Drawing.Size(168, 32);
            this.label6.TabIndex = 26;
            this.label6.Text = "Conf. Contraseña:";
            this.label6.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label5
            // 
            this.label5.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label5.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label5.Location = new System.Drawing.Point(57, 218);
            this.label5.Name = "label5";
            this.label5.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label5.Size = new System.Drawing.Size(117, 32);
            this.label5.TabIndex = 25;
            this.label5.Text = "Contraseña:";
            this.label5.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label4
            // 
            this.label4.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label4.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label4.Location = new System.Drawing.Point(85, 173);
            this.label4.Name = "label4";
            this.label4.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label4.Size = new System.Drawing.Size(89, 32);
            this.label4.TabIndex = 24;
            this.label4.Text = "Usuario:";
            this.label4.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label3
            // 
            this.label3.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label3.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label3.Location = new System.Drawing.Point(85, 128);
            this.label3.Name = "label3";
            this.label3.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label3.Size = new System.Drawing.Size(89, 32);
            this.label3.TabIndex = 23;
            this.label3.Text = "Edad:";
            this.label3.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label2
            // 
            this.label2.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.Location = new System.Drawing.Point(85, 82);
            this.label2.Name = "label2";
            this.label2.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label2.Size = new System.Drawing.Size(89, 32);
            this.label2.TabIndex = 22;
            this.label2.Text = "Apellido:";
            this.label2.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // label1
            // 
            this.label1.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.label1.Font = new System.Drawing.Font("Segoe UI", 14.25F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(85, 38);
            this.label1.Name = "label1";
            this.label1.RightToLeft = System.Windows.Forms.RightToLeft.No;
            this.label1.Size = new System.Drawing.Size(89, 32);
            this.label1.TabIndex = 21;
            this.label1.Text = "Nombre:";
            this.label1.TextAlign = System.Drawing.ContentAlignment.TopRight;
            // 
            // busca_btn
            // 
            this.busca_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.busca_btn.ForeColor = System.Drawing.Color.White;
            this.busca_btn.Location = new System.Drawing.Point(199, 397);
            this.busca_btn.Name = "busca_btn";
            this.busca_btn.Size = new System.Drawing.Size(164, 37);
            this.busca_btn.TabIndex = 46;
            this.busca_btn.Text = "Cancelar";
            this.busca_btn.UseVisualStyleBackColor = false;
            this.busca_btn.Click += new System.EventHandler(this.busca_btn_Click);
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.Color.DarkSlateGray;
            this.button1.ForeColor = System.Drawing.Color.White;
            this.button1.Location = new System.Drawing.Point(589, 397);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(164, 37);
            this.button1.TabIndex = 47;
            this.button1.Text = "Registrar";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // limpia_btn
            // 
            this.limpia_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.limpia_btn.ForeColor = System.Drawing.Color.White;
            this.limpia_btn.Location = new System.Drawing.Point(398, 397);
            this.limpia_btn.Name = "limpia_btn";
            this.limpia_btn.Size = new System.Drawing.Size(164, 37);
            this.limpia_btn.TabIndex = 48;
            this.limpia_btn.Text = "Limpiar";
            this.limpia_btn.UseVisualStyleBackColor = false;
            this.limpia_btn.Click += new System.EventHandler(this.limpia_btn_Click);
            // 
            // RegistroUsuario
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(784, 462);
            this.ControlBox = false;
            this.Controls.Add(this.limpia_btn);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.busca_btn);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.label7);
            this.Controls.Add(this.pictureBox1);
            this.ForeColor = System.Drawing.Color.White;
            this.Name = "RegistroUsuario";
            this.Text = "RegistroUsuario";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.PictureBox pictureBox1;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.TextBox pass2_txt;
        private System.Windows.Forms.TextBox pass1_txt;
        private System.Windows.Forms.TextBox usuario_txt;
        private System.Windows.Forms.TextBox edad_txt;
        private System.Windows.Forms.TextBox apellido_txt;
        private System.Windows.Forms.TextBox nombre_txt;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button busca_btn;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button limpia_btn;
    }
}