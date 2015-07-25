using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Data.OleDb;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Text.RegularExpressions;

using PanGu;
using PanGu.Dict;
using NPOI.HSSF.UserModel;
using NPOI;
using NPOI.POIFS;
using NPOI.HSSF;
using NPOI.Util;
using NPOI.POIFS.FileSystem;
using NPOI.SS.UserModel;


namespace 分词与特征提取
{
    public partial class Form1 : Form
    {
        struct textAttribute
        {
            public string content;
            public int variety;
        }
        struct entropyWord
        {
            public textAttribute tb;
            public double entropy;
        }
        private DataSet ds = new DataSet();
        private List<textAttribute> segmentList = new List<textAttribute>();
        private int number;
        private string saveURL;

        public Form1()
        {
            InitializeComponent();
        }

        /// <summary>
        /// 导入excel
        /// </summary>
        /// <param name="filenameurl"></param>
        /// <returns></returns>
        public DataSet ExecleDs(string filenameurl)
        {

            string strConn = "Provider=Microsoft.Jet.OleDb.4.0;" + "data source=" + filenameurl + ";Extended Properties='Excel 8.0; HDR=YES; IMEX=1'";
            OleDbConnection conn = new OleDbConnection(strConn);
            conn.Open();
            DataTable dt = conn.GetOleDbSchemaTable(OleDbSchemaGuid.Tables, null);
            string tableName = dt.Rows[0][2].ToString().Trim();
            DataSet ds = new DataSet();
            string strExcel = string.Format("select * from [{0}]", tableName);
            OleDbDataAdapter odda = new OleDbDataAdapter(strExcel, conn);
            odda.Fill(ds);
            return ds;
        }

        /// <summary>
        /// 导出excel
        /// </summary>
        /// <param name="segmentList"></param>
        private void ExportExcel(List<textAttribute> segmentList)
        {
            HSSFWorkbook hssfworkbook = new HSSFWorkbook();//创建工作本
            ISheet sheet1 = hssfworkbook.CreateSheet("Sheet1");//创建表
            sheet1.SetColumnWidth(0, 100 * 256);//设置表宽
            int i = 0;
            foreach (textAttribute ta in segmentList)
            {
                sheet1.CreateRow(i).CreateCell(0).SetCellValue(ta.content);//创建单元格
                sheet1.GetRow(i).CreateCell(1).SetCellValue(ta.variety);
                i++;
            }

            //通过filestream写入
            FileStream file = new FileStream(@saveURL + "分词结果.xls", FileMode.Create);
            hssfworkbook.Write(file);
            file.Close();
        }

        private void ExportExcel(List<entropyWord> OrderList)
        {
            HSSFWorkbook hssfworkbook = new HSSFWorkbook();//创建工作本
            ISheet sheet1 = hssfworkbook.CreateSheet("Sheet1");//创建表
            sheet1.SetColumnWidth(0, 100 * 256);//设置表宽
            int i = 0;
            foreach (entropyWord en in OrderList)
            {
                sheet1.CreateRow(i).CreateCell(0).SetCellValue(en.tb.content);//创建单元格
                sheet1.GetRow(i).CreateCell(1).SetCellValue(en.tb.variety);
                i++;
            }

            //通过filestream写入
            FileStream file = new FileStream(@saveURL + "特征提取.xls", FileMode.Create);
            hssfworkbook.Write(file);
            file.Close();
        }


        /// <summary>
        /// 得到分词结果和情感分类的List
        /// </summary>
        private void GetSegmentList()
        {
            for (int i = 0; i < dgv_data.Rows.Count; i++)
            {
                // if (dgv_data.Rows[i].Cells[1].Value == DBNull.Value)
                // { }
                if (dgv_data.Rows[i].Cells[0].Value == null)
                { }
                else
                {
                    textAttribute tb;
                    tb.content = DisplaySegment(dgv_data.Rows[i].Cells[0].Value.ToString());
                    dgv_data.Rows[i].Cells[0].Value = tb.content;
                    if (dgv_data.Rows[i].Cells[1].Value == DBNull.Value)
                    {
                        tb.variety = 0;
                    }
                    else
                    {
                        tb.variety = Convert.ToInt32(dgv_data.Rows[i].Cells[1].Value);
                    }
                    segmentList.Add(tb);
                }
            }
        }

        /// <summary>
        /// 分词
        /// </summary>
        /// <param name="textSource"></param>
        /// <returns></returns>
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

        private void bt_browse_Click(object sender, EventArgs e)
        {
            OpenFileDialog ofd = new OpenFileDialog();
            ofd.InitialDirectory = Application.StartupPath;
            ofd.Filter = "All files (*.*)|*.*|Excel files|*.xlsx;*.xls";
            ofd.FilterIndex = 2;
            ofd.RestoreDirectory = true;
            string Path = "";
            if (ofd.ShowDialog() == DialogResult.OK)
            {
                try
                {
                    Path = ofd.FileName.ToString();
                    txt_location.Text = Path;
                    string[] sArray = Path.Split('\\');
                    saveURL = null;
                    for (int i = 0; i < sArray.Length - 1; i++)
                    {
                        saveURL += sArray[i] + "\\";
                    }
                    ds = ExecleDs(Path);
                    /*
                    DataTable dt = new DataTable();
                    dt.Columns.Add(ds.Tables[0].Columns[0]);
                    dt.Columns.Add(ds.Tables[0].Columns[1]);
                    ds.Tables[0] = dt;
                    */
                    dgv_data.DataSource = ds;
                    dgv_data.DataMember = ds.Tables[0].TableName.ToString();
                }
                catch
                {
                    MessageBox.Show("载入出错");
                }
                int j = dgv_data.Columns.Count;
                for (int i = 2; i < j; i++)
                    dgv_data.Columns.RemoveAt(2);
                GetSegmentList();
            }
            ExportExcel(segmentList);
            btExtraction.Enabled = true;
        }

        //将分词结果转化为一个个的词
        private void SwitchSegmentList()
        {
            List<textAttribute> newList = new List<textAttribute>();
            int count = segmentList.Count;
            for (int i = count - 1; i >= 0; i--)
            {
                if (segmentList[i].variety == 0)
                    segmentList.Remove(segmentList[i]);
            }
            foreach (textAttribute tb in segmentList)
            {
                string[] sArray = tb.content.Split('/');
                foreach (string s in sArray)
                {
                    textAttribute tbb;
                    tbb.content = s;
                    tbb.variety = tb.variety;
                    newList.Add(tbb);
                }
            }
            if (newList != null)
                segmentList = newList;
        }

        /// <summary>
        /// 特征提取函数
        /// </summary>
        private List<entropyWord> FatureExtruction(List<textAttribute> segmentList)
        {
            //variety==-1出现的概率
            double p1 = Convert.ToDouble(Calculate(null, -1, segmentList, 1)) / Convert.ToDouble(Calculate(null, 0, segmentList, 3));
            //variety==1出现的概率
            double p2 = Convert.ToDouble(Calculate(null, 1, segmentList, 1)) / Convert.ToDouble(Calculate(null, 0, segmentList, 3));
            //总体熵值
            double Hc = p1 * Math.Log(p1, 2) + p2 * Math.Log(p2, 2);
            //条件熵

            //停用词
            //System.Text.Encoding.GetEncoding("gb2312")
            string[] line = File.ReadAllLines(@saveURL + "中文停用词表.txt", System.Text.Encoding.Default);

            List<entropyWord> enList = new List<entropyWord>();
            foreach (textAttribute tb in segmentList)
            {
                int i = 0;
                if (enList != null)
                {
                    foreach (entropyWord en in enList)
                    {
                        if (en.tb.content == tb.content)//防止重复计算
                        {
                            i = 1;
                            break;
                        }
                    }
                }
                foreach (string s in line)
                {
                    if (tb.content == s)//去停用词
                    {
                        i = 1;
                        break;
                    }
                }
                /*int a = 0;
                double b = 0.0;
                if (int.TryParse(tb.content, out a) == true||double.TryParse(tb.content, out b))//判断是否数字
                {
                    i = 1;
                }*/
                if (!Regex.IsMatch(tb.content, @"[\u4e00-\u9fbb]+$"))//去除非汉字
                    i = 1;
                if (i != 1)
                {
                    entropyWord en;
                    en.tb = tb;
                    //a代表特征出现，b代表特征没有出现，1代表variety==-1,2代表variety==1
                    double totalCount = Convert.ToDouble(Calculate(null, 0, segmentList, 3));
                    double variety1Count = Convert.ToDouble(Calculate(null, -1, segmentList, 1));
                    double variety2Count = Convert.ToDouble(Calculate(null, 1, segmentList, 1));
                    double aCount = Convert.ToDouble(Calculate(tb.content, 0, segmentList, 0));
                    double bCount = totalCount - aCount;
                    double a1Count = Convert.ToDouble(Calculate(tb.content, -1, segmentList, 2));
                    double a2Count = Convert.ToDouble(Calculate(tb.content, 1, segmentList, 2));
                    double b1Count = variety1Count - a1Count;
                    double b2Count = variety2Count - a2Count;
                    double pa = aCount / totalCount;
                    double pb = bCount / totalCount;
                    double p1a = a1Count / aCount;
                    double p2a = a2Count / aCount;
                    double p1b = b1Count / bCount;
                    double p2b = b2Count / bCount;
                    double Hca = pa * (p1a * Math.Log(p1a, 2) + p2a * Math.Log(p2a, 2));
                    double Hcb = pb * (p1b * Math.Log(p1b, 2) + p2b * Math.Log(p2b, 2));
                    en.tb.variety = a1Count > a2Count ? -1 : 1;
                    en.entropy = -Hc + Hca + Hcb;
                    enList.Add(en);
                }
            }
            enList = EntropySort(enList);
            return enList;
        }

        //提取熵由大到小前100个词
        private List<entropyWord> EntropySort(List<entropyWord> enList)
        {
            int count = enList.Count;
            for (int i = count - 1; i >= 0; i--)
            {
                if (enList[i].entropy == 0 || double.IsNaN(enList[i].entropy))
                    enList.Remove(enList[i]);
            }
            List<entropyWord> OrderList = new List<entropyWord>();
            enList.Sort((left, right) =>
                {
                    if (left.entropy > right.entropy)
                        return -1;
                    else if (left.entropy == right.entropy)
                        return 0;
                    else
                        return 1;
                });
            for (int i = 0; i < enList.Count; i++)
            {
                dgv_data.Rows[i].Cells[0].Value = enList[i].tb.content;
                dgv_data.Rows[i].Cells[1].Value = enList[i].entropy;
            }
            for (int i = 0; i < number; i++)
            {
                OrderList.Add(enList[i]);
            }
            return OrderList;
        }

        /// <summary>
        /// 计算数量
        /// </summary>
        /// <param name="content"></param>
        /// <param name="variety"></param>
        /// <param name="segmentList"></param>
        /// <param name="index"></param>
        /// <returns></returns>
        private int Calculate(string content, int variety, List<textAttribute> segmentList, int index)
        {
            int calculate = 0;
            //只考虑文本内容
            if (index == 0)
            {
                foreach (textAttribute tb in segmentList)
                {
                    if (tb.content == content)
                        calculate++;
                }
            }
            //只考虑种类
            else if (index == 1)
            {
                foreach (textAttribute tb in segmentList)
                {
                    if (tb.variety == variety)
                        calculate++;
                }
            }
            //内容和种类都考虑
            else if (index == 2)
            {
                foreach (textAttribute tb in segmentList)
                {
                    if (tb.content == content)
                    {
                        if (tb.variety == variety)
                            calculate++;
                    }
                }
            }
            //计算总数
            else //if (index == 3)
            {
                foreach (textAttribute tb in segmentList)
                {
                    if (tb.variety != 0)
                        calculate++;
                }
            }
            return calculate;
        }

        private void btExtraction_Click(object sender, EventArgs e)
        {
            btExtraction.Enabled = false;
            if (tbExtraction.Text == null)
            {
                MessageBox.Show("提取特征数未确定");
            }
            try
            {
                number = Convert.ToInt32(tbExtraction.Text);
            }
            catch
            {
                MessageBox.Show("输入有误");
            }

            SwitchSegmentList();//将分词转化为单个词的形式
            List<entropyWord> OrderList = FatureExtruction(segmentList);//特征提取
            ExportExcel(OrderList);
            MessageBox.Show("提取完毕");
            btExtraction.Enabled = true;
        }
    }
}
