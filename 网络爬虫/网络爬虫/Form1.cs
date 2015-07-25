using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Text.RegularExpressions;
using System.Threading.Tasks;
using System.Web;
using System.Web.UI.MobileControls;
using System.Windows.Forms;
using PanGu;
using PanGu.Dict;
using NPOI.HSSF.UserModel;
using NPOI;
using NPOI.POIFS;
using NPOI.HSSF;
using NPOI.Util;
using NPOI.POIFS.FileSystem;
using NPOI.SS.UserModel;

namespace 网络爬虫
{
    public partial class Form1 : System.Windows.Forms.Form
    {
        public string startUrl;
        public Form1()
        {
            InitializeComponent();
        }

        private void bt_go_Click(object sender, EventArgs e)
        {
 
            startUrl = "http://tieba.baidu.com/f?kw=%E7%BD%91%E7%BB%9C%E6%B5%81%E8%A1%8C%E8%AF%AD&ie=utf-8&pn=";
            List<Link> links =GetLinks(startUrl, 50);

            if (File.Exists("C:\\Users\\LENOVO\\Desktop\\回复提取3.0.txt"))
                File.Delete("C:\\Users\\LENOVO\\Desktop\\回复提取3.0.txt");

            for (int i = 0; i < links.Count; i++)
            {
                string fstUrl = links[i].NavigateUrl;
                WebPage page = new WebPage(fstUrl);
                int pageNumber = GetPageNumber(page.Context);
                if (pageNumber == 0)
                    continue;
                for (int j = 0; j < pageNumber; j++)
                {
                    string currentUrl = fstUrl + "?pn=" + (j + 1).ToString();
                    WebPage currentPage = new WebPage(currentUrl);
                    GetAndWrite(currentPage.Context,"回复提取3.0.txt",true);
                }
            }
        }

        public List<Link> GetLinks(string urlHead,int pageNeededNumber)
        {
            List<Link> links = new List<Link>();
            string url ;
            for (int i = 0; i < pageNeededNumber; i++)
            {
                url = urlHead + 50 * i;
                WebPage page = new WebPage(url);
                links.AddRange(page.getSpecialLinksByUrl("/p/", 50));
            }
   
            StreamWriter sw = new StreamWriter("C:\\Users\\LENOVO\\Desktop\\urls3.0.txt",false,Encoding.UTF8);
            for (int i = 0; i < links.Count; i++)
            {
                sw.Write(links[i].NavigateUrl + "\r\n");
            }
            sw.Close();

            return links;
        }

        public int GetPageNumber(string text)
        {
            List<string> pageCount = GetMatchs(@"(?<=\d+回复贴.共)\d+(?=页)",text);
            if (pageCount.Count != 0)
                return Convert.ToInt32(pageCount[0]);
            else
                return 0;
        }

        public void GetAndWrite(string text,string name,bool IsCover)
        {
            List<string> s = GetMatchs(@"\b\w*?\d*?\b\s\b\w{4}\d\b.*?(?=\s回复)", text); //tb_content.Text.Split(new[] { "个人企业举报垃圾信息举报" }, StringSplitOptions.RemoveEmptyEntries);
            //FileStream aFile = new FileStream("C:\\Users\\LENOVO\\Desktop\\回复提取.txt", FileMode.OpenOrCreate);
            StreamWriter sw = new StreamWriter("C:\\Users\\LENOVO\\Desktop\\"+name, IsCover, Encoding.UTF8);
            sw.Write("\r\n");
            for (int i = 0; i < s.Count; i++)
            {
                sw.Write(s[i] + "\r\n");
            }
            sw.Close();
        }

        public List<string> GetMatchs(string pattern,string text)
        {
            // Define a regular expression for repeated words.
            Regex rx = new Regex(pattern,
              RegexOptions.Compiled | RegexOptions.IgnoreCase);

            // Define a test string.        
            //string text = "The the quick brown fox  fox jumped over the lazy dog dog.";

            // Find matches.
            MatchCollection matches = rx.Matches(text);

            // Report the number of matches found.
            //Console.WriteLine("{0} matches found in:\n   {1}",
                             // matches.Count,
                             // text);

            // Report on each match.
            List<string> matchs = new List<string>();
            foreach (Match match in matches)
            {
                matchs.Add(match.ToString());
               
            }
            return matchs;
        }

        private void bt_show_Click(object sender, EventArgs e)
        {
            List<string> content = ReadData("C:\\Users\\LENOVO\\Desktop\\回复提取3.0.txt");
            for (int i = 0; i < content.Count; i++)
            {
                tb_content.Text += content[i] + "\r\n";
            }
        }


        public List<string> ReadData(string name)
        {
            //C#读取TXT文件之建立  FileStream 的对象,说白了告诉程序,     
            //文件在那里,对文件如何 处理,对文件内容采取的处理方式     
            FileStream fs = new FileStream(@name, FileMode.Open, FileAccess.Read);
            //仅 对文本 执行  读写操作     
            StreamReader sr = new StreamReader(fs);
            //定位操作点,begin 是一个参考点     
            sr.BaseStream.Seek(0, SeekOrigin.Begin);
            //读一下，看看文件内有没有内容，为下一步循环 提供判断依据     
            //sr.ReadLine() 这里是 StreamReader的要领  可不是 console 中的~      
            string str = sr.ReadLine();//假如  文件有内容      
            List<string> line = new List<string>();
            while (str != null)
            {
                //输出字符串，str 在上面已经定义了 读入一行字符      
                line.Add(str);
                //这里我的理会是 当输出一行后，指针移动到下一行~     
                //下面这句话就是 判断 指针所指这行能无法 有内容~     
                str = sr.ReadLine();
            }
            //C#读取TXT文件之关上文件，留心顺序，先对文件内部执行 关上，然后才是文件~     
            sr.Close();
            fs.Close();
            return line;
        }

        public struct theWord
        {
            public string text;
            public int times;
        }

        private void bt_clustering_Click(object sender, EventArgs e)
        {
            List<string> initialContent = ReadData("C:\\Users\\LENOVO\\Desktop\\回复提取3.0.txt");
            List<string> content = new List<string>();
            for (int i = 0; i < initialContent.Count; i++)
            {
                List<string> matchs=GetMatchs(@"(?<=\b.+?\b\s\b\w{4}\d\b\s).*", initialContent[i]);
                if (matchs.Count != 0)
                    content.Add(matchs[0]);
 
            }
            List<string> segmentWords = GetSegmentWords(content);
            string[] stopWords = File.ReadAllLines(@"中文停用词表（专用）.txt", System.Text.Encoding.Default);
            List<theWord> theWords = new List<theWord>();
            foreach (string s in segmentWords.Distinct().ToList())
            {
                int i = 0;
                foreach (string word in stopWords)
                {
                    if (word == s)
                    {
                        i = 1;
                        break;
                    }
                }
                if (!Regex.IsMatch(s, @"[\u4e00-\u9fbb]+$"))//去除非汉字
                    i = 1;
                if (i == 1)
                    continue;
                int times = 0;
                foreach (string word in segmentWords)
                {
                    if (s == word)
                        times++;
                }
                theWord theword;
                theword.text = s;
                theword.times = times;
                theWords.Add(theword);
            }
            theWords.Sort((left, right) =>
            {
                if (left.times > right.times)
                    return -1;
                else if (left.times == right.times)
                    return 0;
                else
                    return 1;
            });            
            for (int i = 0; i < theWords.Count; i++)
            {
                tb_content.Text += theWords[i].text + "(" + theWords[i].times + ")" + "\r\n";
            }

            StreamWriter sw = new StreamWriter("C:\\Users\\LENOVO\\Desktop\\流行词排行3.0.txt");
            sw.Write(tb_content.Text);
            sw.Close();
        }

        private List<string> GetSegmentWords(List<string> content)
        {
            Segment segment = new Segment();

            List<string> segmentWords = new List<string>();
            foreach (string s in content)
            {
                ICollection<WordInfo> words = segment.DoSegment(s);
                List<string> sWords = new List<string>();
                foreach (WordInfo wordInfo in words)
                {
                    if (wordInfo == null)
                    {
                        continue;
                    }
                    sWords.Add(wordInfo.Word);
                }
                segmentWords.AddRange(sWords);
            }
            return segmentWords;
        }
    }
}
