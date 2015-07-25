namespace 网络爬虫
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
            this.bt_go = new System.Windows.Forms.Button();
            this.tb_content = new System.Windows.Forms.TextBox();
            this.bt_show = new System.Windows.Forms.Button();
            this.bt_clustering = new System.Windows.Forms.Button();
            this.SuspendLayout();
            // 
            // bt_go
            // 
            this.bt_go.Location = new System.Drawing.Point(12, 3);
            this.bt_go.Name = "bt_go";
            this.bt_go.Size = new System.Drawing.Size(75, 23);
            this.bt_go.TabIndex = 0;
            this.bt_go.Text = "go";
            this.bt_go.UseVisualStyleBackColor = true;
            this.bt_go.Click += new System.EventHandler(this.bt_go_Click);
            // 
            // tb_content
            // 
            this.tb_content.Location = new System.Drawing.Point(12, 32);
            this.tb_content.Multiline = true;
            this.tb_content.Name = "tb_content";
            this.tb_content.ScrollBars = System.Windows.Forms.ScrollBars.Vertical;
            this.tb_content.Size = new System.Drawing.Size(545, 283);
            this.tb_content.TabIndex = 1;
            // 
            // bt_show
            // 
            this.bt_show.Location = new System.Drawing.Point(93, 3);
            this.bt_show.Name = "bt_show";
            this.bt_show.Size = new System.Drawing.Size(75, 23);
            this.bt_show.TabIndex = 2;
            this.bt_show.Text = "show";
            this.bt_show.UseVisualStyleBackColor = true;
            this.bt_show.Click += new System.EventHandler(this.bt_show_Click);
            // 
            // bt_clustering
            // 
            this.bt_clustering.Location = new System.Drawing.Point(174, 3);
            this.bt_clustering.Name = "bt_clustering";
            this.bt_clustering.Size = new System.Drawing.Size(75, 23);
            this.bt_clustering.TabIndex = 3;
            this.bt_clustering.Text = "cluster";
            this.bt_clustering.UseVisualStyleBackColor = true;
            this.bt_clustering.Click += new System.EventHandler(this.bt_clustering_Click);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(569, 327);
            this.Controls.Add(this.bt_clustering);
            this.Controls.Add(this.bt_show);
            this.Controls.Add(this.tb_content);
            this.Controls.Add(this.bt_go);
            this.Name = "Form1";
            this.Text = "FrmPAPAPA";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Button bt_go;
        private System.Windows.Forms.TextBox tb_content;
        private System.Windows.Forms.Button bt_show;
        private System.Windows.Forms.Button bt_clustering;
    }
}

