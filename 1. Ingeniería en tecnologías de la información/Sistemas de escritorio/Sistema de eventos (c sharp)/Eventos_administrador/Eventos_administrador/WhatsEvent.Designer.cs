namespace Eventos_administrador
{
    partial class WhatsEvent
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
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(WhatsEvent));
            this.button1 = new System.Windows.Forms.Button();
            this.entra_btn = new System.Windows.Forms.Button();
            this.pictureBox1 = new System.Windows.Forms.PictureBox();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).BeginInit();
            this.SuspendLayout();
            // 
            // button1
            // 
            this.button1.BackColor = System.Drawing.SystemColors.Control;
            this.button1.Cursor = System.Windows.Forms.Cursors.Hand;
            this.button1.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button1.Location = new System.Drawing.Point(177, 382);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(251, 66);
            this.button1.TabIndex = 5;
            this.button1.Text = "Salir";
            this.button1.UseVisualStyleBackColor = false;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // entra_btn
            // 
            this.entra_btn.BackColor = System.Drawing.Color.DarkSlateGray;
            this.entra_btn.Font = new System.Drawing.Font("Segoe UI", 15.75F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.entra_btn.ForeColor = System.Drawing.Color.White;
            this.entra_btn.Location = new System.Drawing.Point(177, 292);
            this.entra_btn.Name = "entra_btn";
            this.entra_btn.Size = new System.Drawing.Size(251, 66);
            this.entra_btn.TabIndex = 8;
            this.entra_btn.Text = "Entrar a What 7";
            this.entra_btn.UseVisualStyleBackColor = false;
            this.entra_btn.Click += new System.EventHandler(this.entra_btn_Click);
            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = ((System.Drawing.Image)(resources.GetObject("pictureBox1.Image")));
            this.pictureBox1.Location = new System.Drawing.Point(157, 23);
            this.pictureBox1.Name = "pictureBox1";
            this.pictureBox1.Size = new System.Drawing.Size(287, 263);
            this.pictureBox1.SizeMode = System.Windows.Forms.PictureBoxSizeMode.StretchImage;
            this.pictureBox1.TabIndex = 44;
            this.pictureBox1.TabStop = false;
            // 
            // WhatsEvent
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Teal;
            this.ClientSize = new System.Drawing.Size(604, 512);
            this.Controls.Add(this.pictureBox1);
            this.Controls.Add(this.entra_btn);
            this.Controls.Add(this.button1);
            this.MaximumSize = new System.Drawing.Size(620, 550);
            this.MinimumSize = new System.Drawing.Size(620, 550);
            this.Name = "WhatsEvent";
            this.Text = "WhatsEvent";
            ((System.ComponentModel.ISupportInitialize)(this.pictureBox1)).EndInit();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button entra_btn;
        private System.Windows.Forms.PictureBox pictureBox1;
    }
}