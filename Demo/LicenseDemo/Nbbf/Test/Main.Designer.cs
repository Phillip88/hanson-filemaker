namespace Test
{
    partial class Main
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
            this.components = new System.ComponentModel.Container();
            this.cmdCreate = new System.Windows.Forms.Button();
            this.cmdInstall = new System.Windows.Forms.Button();
            this.cmdValidate = new System.Windows.Forms.Button();
            this.txtKey1 = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.txtManufacturer = new System.Windows.Forms.TextBox();
            this.label3 = new System.Windows.Forms.Label();
            this.txtProduct = new System.Windows.Forms.TextBox();
            this.ssStatus = new System.Windows.Forms.StatusStrip();
            this.tssStatus = new System.Windows.Forms.ToolStripStatusLabel();
            this.tmrStatus = new System.Windows.Forms.Timer(this.components);
            this.txtKey2 = new System.Windows.Forms.TextBox();
            this.txtKey3 = new System.Windows.Forms.TextBox();
            this.txtKey4 = new System.Windows.Forms.TextBox();
            this.txtKey5 = new System.Windows.Forms.TextBox();
            this.ssStatus.SuspendLayout();
            this.SuspendLayout();
            // 
            // cmdCreate
            // 
            this.cmdCreate.Location = new System.Drawing.Point(204, 64);
            this.cmdCreate.Name = "cmdCreate";
            this.cmdCreate.Size = new System.Drawing.Size(75, 23);
            this.cmdCreate.TabIndex = 10;
            this.cmdCreate.Text = "&Create";
            this.cmdCreate.UseVisualStyleBackColor = true;
            this.cmdCreate.Click += new System.EventHandler(this.cmdCreate_Click);
            // 
            // cmdInstall
            // 
            this.cmdInstall.Location = new System.Drawing.Point(285, 64);
            this.cmdInstall.Name = "cmdInstall";
            this.cmdInstall.Size = new System.Drawing.Size(75, 23);
            this.cmdInstall.TabIndex = 11;
            this.cmdInstall.Text = "&Install";
            this.cmdInstall.UseVisualStyleBackColor = true;
            this.cmdInstall.Click += new System.EventHandler(this.cmdInstall_Click);
            // 
            // cmdValidate
            // 
            this.cmdValidate.Location = new System.Drawing.Point(366, 64);
            this.cmdValidate.Name = "cmdValidate";
            this.cmdValidate.Size = new System.Drawing.Size(75, 23);
            this.cmdValidate.TabIndex = 12;
            this.cmdValidate.Text = "&Validate";
            this.cmdValidate.UseVisualStyleBackColor = true;
            this.cmdValidate.Click += new System.EventHandler(this.cmdValidate_Click);
            // 
            // txtKey1
            // 
            this.txtKey1.Location = new System.Drawing.Point(102, 38);
            this.txtKey1.MaxLength = 5;
            this.txtKey1.Name = "txtKey1";
            this.txtKey1.Size = new System.Drawing.Size(63, 20);
            this.txtKey1.TabIndex = 5;
            this.txtKey1.Tag = "0";
            this.txtKey1.TextChanged += new System.EventHandler(this.txtKey1_TextChanged);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(19, 41);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(77, 13);
            this.label1.TabIndex = 4;
            this.label1.Text = "&Generated key";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(12, 15);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(84, 13);
            this.label2.TabIndex = 0;
            this.label2.Text = "&Manufacturer ID";
            // 
            // txtManufacturer
            // 
            this.txtManufacturer.Location = new System.Drawing.Point(102, 12);
            this.txtManufacturer.Name = "txtManufacturer";
            this.txtManufacturer.Size = new System.Drawing.Size(41, 20);
            this.txtManufacturer.TabIndex = 1;
            this.txtManufacturer.TextChanged += new System.EventHandler(this.txtManufacturer_TextChanged);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(149, 15);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(58, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "&Product ID";
            // 
            // txtProduct
            // 
            this.txtProduct.Location = new System.Drawing.Point(213, 12);
            this.txtProduct.Name = "txtProduct";
            this.txtProduct.Size = new System.Drawing.Size(41, 20);
            this.txtProduct.TabIndex = 3;
            this.txtProduct.TextChanged += new System.EventHandler(this.txtProduct_TextChanged);
            // 
            // ssStatus
            // 
            this.ssStatus.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.tssStatus});
            this.ssStatus.Location = new System.Drawing.Point(0, 96);
            this.ssStatus.Name = "ssStatus";
            this.ssStatus.Size = new System.Drawing.Size(455, 22);
            this.ssStatus.TabIndex = 9;
            this.ssStatus.Text = "statusStrip1";
            // 
            // tssStatus
            // 
            this.tssStatus.Name = "tssStatus";
            this.tssStatus.Size = new System.Drawing.Size(440, 17);
            this.tssStatus.Spring = true;
            // 
            // tmrStatus
            // 
            this.tmrStatus.Tick += new System.EventHandler(this.tmrStatus_Tick);
            // 
            // txtKey2
            // 
            this.txtKey2.Location = new System.Drawing.Point(171, 38);
            this.txtKey2.MaxLength = 5;
            this.txtKey2.Name = "txtKey2";
            this.txtKey2.Size = new System.Drawing.Size(63, 20);
            this.txtKey2.TabIndex = 6;
            this.txtKey2.Tag = "1";
            this.txtKey2.TextChanged += new System.EventHandler(this.txtKey2_TextChanged);
            // 
            // txtKey3
            // 
            this.txtKey3.Location = new System.Drawing.Point(240, 38);
            this.txtKey3.MaxLength = 5;
            this.txtKey3.Name = "txtKey3";
            this.txtKey3.Size = new System.Drawing.Size(63, 20);
            this.txtKey3.TabIndex = 7;
            this.txtKey3.Tag = "2";
            this.txtKey3.TextChanged += new System.EventHandler(this.txtKey3_TextChanged);
            // 
            // txtKey4
            // 
            this.txtKey4.Location = new System.Drawing.Point(309, 38);
            this.txtKey4.MaxLength = 5;
            this.txtKey4.Name = "txtKey4";
            this.txtKey4.Size = new System.Drawing.Size(63, 20);
            this.txtKey4.TabIndex = 8;
            this.txtKey4.Tag = "3";
            this.txtKey4.TextChanged += new System.EventHandler(this.txtKey4_TextChanged);
            // 
            // txtKey5
            // 
            this.txtKey5.Location = new System.Drawing.Point(378, 38);
            this.txtKey5.MaxLength = 5;
            this.txtKey5.Name = "txtKey5";
            this.txtKey5.Size = new System.Drawing.Size(63, 20);
            this.txtKey5.TabIndex = 9;
            this.txtKey5.Tag = "4";
            this.txtKey5.TextChanged += new System.EventHandler(this.txtKey5_TextChanged);
            // 
            // Main
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(455, 118);
            this.Controls.Add(this.txtKey5);
            this.Controls.Add(this.txtKey4);
            this.Controls.Add(this.txtKey3);
            this.Controls.Add(this.txtKey2);
            this.Controls.Add(this.ssStatus);
            this.Controls.Add(this.txtProduct);
            this.Controls.Add(this.label3);
            this.Controls.Add(this.txtManufacturer);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.txtKey1);
            this.Controls.Add(this.cmdValidate);
            this.Controls.Add(this.cmdInstall);
            this.Controls.Add(this.cmdCreate);
            this.Name = "Main";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Nbbf Test Application";
            this.ssStatus.ResumeLayout(false);
            this.ssStatus.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button cmdCreate;
        private System.Windows.Forms.Button cmdInstall;
        private System.Windows.Forms.Button cmdValidate;
        private System.Windows.Forms.TextBox txtKey1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox txtManufacturer;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.TextBox txtProduct;
        private System.Windows.Forms.StatusStrip ssStatus;
        private System.Windows.Forms.ToolStripStatusLabel tssStatus;
        private System.Windows.Forms.Timer tmrStatus;
        private System.Windows.Forms.TextBox txtKey2;
        private System.Windows.Forms.TextBox txtKey3;
        private System.Windows.Forms.TextBox txtKey4;
        private System.Windows.Forms.TextBox txtKey5;
    }
}

