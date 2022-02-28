namespace Eventos_administrador
{
    partial class Login
    {
        /// <summary>
        /// Variable del diseñador requerida.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Limpiar los recursos que se estén utilizando.
        /// </summary>
        /// <param name="disposing">true si los recursos administrados se deben desechar; false en caso contrario.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Código generado por el Diseñador de Windows Forms

        /// <summary>
        /// Método necesario para admitir el Diseñador. No se puede modificar
        /// el contenido del método con el editor de código.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Login));
            this.cuenta_txt = new System.Windows.Forms.TextBox();
            this.pass_txt = new System.Windows.Forms.TextBox();
            this.ingresa_btn = new System.Windows.Forms.Button();
            this.salir_btn = new System.Windows.Forms.Button();
            this.lab1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // cuenta_txt
            // 
            this.cuenta_txt.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.cuenta_txt.ForeColor = System.Drawing.Color.Black;
            this.cuenta_txt.Location = new System.Drawing.Point(269, 229);
            this.cuenta_txt.Name = "cuenta_txt";
            this.cuenta_txt.Size = new System.Drawing.Size(282, 31);
            this.cuenta_txt.TabIndex = 1;
            // 
            // pass_txt
            // 
            this.pass_txt.Font = new System.Drawing.Font("Microsoft Sans Serif", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.pass_txt.ForeColor = System.Drawing.Color.Black;
            this.pass_txt.Location = new System.Drawing.Point(269, 280);
            this.pass_txt.Name = "pass_txt";
            this.pass_txt.Size = new System.Drawing.Size(282, 31);
            this.pass_txt.TabIndex = 2;
            this.pass_txt.UseSystemPasswordChar = true;
            // 
            // ingresa_btn
            // 
            this.ingresa_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.ingresa_btn.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ingresa_btn.ForeColor = System.Drawing.Color.White;
            this.ingresa_btn.Location = new System.Drawing.Point(177, 376);
            this.ingresa_btn.Name = "ingresa_btn";
            this.ingresa_btn.Size = new System.Drawing.Size(171, 56);
            this.ingresa_btn.TabIndex = 3;
            this.ingresa_btn.Text = "Ingresar";
            this.ingresa_btn.UseVisualStyleBackColor = false;
            this.ingresa_btn.Click += new System.EventHandler(this.ingresa_btn_Click);
            // 
            // salir_btn
            // 
            this.salir_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.salir_btn.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.salir_btn.ForeColor = System.Drawing.Color.White;
            this.salir_btn.Location = new System.Drawing.Point(438, 376);
            this.salir_btn.Name = "salir_btn";
            this.salir_btn.Size = new System.Drawing.Size(171, 56);
            this.salir_btn.TabIndex = 4;
            this.salir_btn.Text = "Cancelar";
            this.salir_btn.UseVisualStyleBackColor = false;
            this.salir_btn.Click += new System.EventHandler(this.salir_btn_Click);
            // 
            // lab1
            // 
            this.lab1.AutoSize = true;
            this.lab1.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.lab1.ForeColor = System.Drawing.Color.White;
            this.lab1.Location = new System.Drawing.Point(152, 230);
            this.lab1.Name = "lab1";
            this.lab1.Size = new System.Drawing.Size(88, 30);
            this.lab1.TabIndex = 8;
            this.lab1.Text = "Usuario:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label2.ForeColor = System.Drawing.Color.White;
            this.label2.Location = new System.Drawing.Point(117, 281);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(123, 30);
            this.label2.TabIndex = 9;
            this.label2.Text = "Contraseña:";
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(269, 12);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(231, 211);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 46;
            this.pictureBox1.TabStop = false;
            // 
            // Login
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(784, 462);
            this.ControlBox = false;
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.lab1);
            this.Controls.Add(this.salir_btn);
            this.Controls.Add(this.ingresa_btn);
            this.Controls.Add(this.pass_txt);
            this.Controls.Add(this.cuenta_txt);
            this.Name = "Login";
            this.Text = "Ingresar como Administrador";
            this.Load += new System.EventHandler(this.Login_Load);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        public System.Windows.Forms.TextBox cuenta_txt;
        public System.Windows.Forms.TextBox pass_txt;
        public System.Windows.Forms.Button ingresa_btn;
        public System.Windows.Forms.Button salir_btn;
        private System.Windows.Forms.Label lab1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}

