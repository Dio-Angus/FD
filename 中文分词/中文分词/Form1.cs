using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

using PanGu;
using PanGu.Dict;

namespace 中文分词
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void bt_segment_Click(object sender, EventArgs e)
        {
            if (textBox1.Text != "")
            {
                textBox2.Text = DisplaySegment(textBox1.Text);
            }
        }

        private void bt_clear_Click(object sender, EventArgs e)
        {
            textBox1.Text = "";
        }

        private string DisplaySegment(string textSource)
        {
            //Stopwatch watch = new Stopwatch();
            //watch.Start();

            Segment segment = new Segment();
            ICollection<WordInfo> words = segment.DoSegment(textSource);

            /*watch.Stop();

            labelSrcLength.Text = textBoxSource.Text.Length.ToString();

            labelSegTime.Text = watch.Elapsed.ToString();
            if (watch.ElapsedMilliseconds == 0)
            {
                labelRegRate.Text = "无穷大";
            }
            else
            {
                labelRegRate.Text = ((double)(textBoxSource.Text.Length / watch.ElapsedMilliseconds) * 1000).ToString();
            }


            if (checkBoxShowTimeOnly.Checked)
            {
                return;
            }*/

            StringBuilder wordsString = new StringBuilder();
            foreach (WordInfo wordInfo in words)
            {
                if (wordInfo == null)
                {
                    continue;
                }

                /* if (showPosition)
                 {

                     wordsString.AppendFormat("{0}({1},{2})/", wordInfo.Word, wordInfo.Position, wordInfo.Rank);
                     //if (_Options.MultiDimensionality)
                     //{
                     //}
                     //else
                     //{
                     //    wordsString.AppendFormat("{0}({1})/", wordInfo.Word, wordInfo.Position);
                     //}
                 }*/
                // else
                // {
                wordsString.AppendFormat("{0}/", wordInfo.Word);
                // }
            }

            //textBoxSegwords.Text += "\n\r" + wordsString.ToString();
            return wordsString.ToString();
        }

    }
}
