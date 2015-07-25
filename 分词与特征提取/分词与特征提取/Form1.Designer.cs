namespace 分词与特征提取
{
    partial class Form1
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.bt_browse = new System.Windows.Forms.Button();
            this.txt_location = new System.Windows.Forms.TextBox();
            this.dgv_data = new System.Windows.Forms.DataGridView();
            this.btExtraction = new System.Windows.Forms.Button();
            this.tbExtraction = new System.Windows.Forms.TextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            ((System.ComponentModel.ISupportInitialize)(this.dgv_data)).BeginInit();
            this.SuspendLayout();
            // 
            // bt_browse
            // 
            this.bt_browse.Location = new System.Drawing.Point(249, 28);
            this.bt_browse.Margin = new System.Windows.Forms.Padding(4);
            this.bt_browse.Name = "bt_browse";
            this.bt_browse.Size = new System.Drawing.Size(100, 29);
            this.bt_browse.TabIndex = 0;
            this.bt_browse.Text = "浏览";
            this.bt_browse.UseVisualStyleBackColor = true;
            this.bt_browse.Click += new System.EventHandler(this.bt_browse_Click);
            // 
            // txt_location
            // 
            this.txt_location.Location = new System.Drawing.Point(29, 30);
            this.txt_location.Margin = new System.Windows.Forms.Padding(4);
            this.txt_location.Name = "txt_location";
            this.txt_location.Size = new System.Drawing.Size(193, 25);
            this.txt_location.TabIndex = 1;
            // 
            // dgv_data
            // 
            this.dgv_data.BackgroundColor = System.Drawing.Color.White;
            this.dgv_data.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.dgv_data.Location = new System.Drawing.Point(13, 90);
            this.dgv_data.Margin = new System.Windows.Forms.Padding(4);
            this.dgv_data.Name = "dgv_data";
            this.dgv_data.RowTemplate.Height = 23;
            this.dgv_data.Size = new System.Drawing.Size(353, 188);
            this.dgv_data.TabIndex = 2;
            // 
            // btExtraction
            // 
            this.btExtraction.Enabled = false;
            this.btExtraction.Location = new System.Drawing.Point(249, 298);
            this.btExtraction.Name = "btExtraction";
            this.btExtraction.Size = new System.Drawing.Size(75, 23);
            this.btExtraction.TabIndex = 3;
            this.btExtraction.Text = "提取";
            this.btExtraction.UseVisualStyleBackColor = true;
            this.btExtraction.Click += new System.EventHandler(this.btExtraction_Click);
            // 
            // tbExtraction
            // 
            this.tbExtraction.Location = new System.Drawing.Point(117, 299);
            this.tbExtraction.Name = "tbExtraction";
            this.tbExtraction.Size = new System.Drawing.Size(100, 25);
            this.tbExtraction.TabIndex = 4;
            this.tbExtraction.Text = "800";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(26, 302);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(82, 15);
            this.label1.TabIndex = 5;
            this.label1.Text = "特征提取数";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(214, 302);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(22, 15);
            this.label2.TabIndex = 6;
            this.label2.Text = "个";
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(379, 347);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.tbExtraction);
            this.Controls.Add(this.btExtraction);
            this.Controls.Add(this.dgv_data);
            this.Controls.Add(this.txt_location);
            this.Controls.Add(this.bt_browse);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "Form1";
            this.Text = "分词与特征提取";
            ((System.ComponentModel.ISupportInitialize)(this.dgv_data)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bt_browse;
        private System.Windows.Forms.TextBox txt_location;
        private System.Windows.Forms.DataGridView dgv_data;
        private System.Windows.Forms.Button btExtraction;
        private System.Windows.Forms.TextBox tbExtraction;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
    }
}

