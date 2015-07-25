using System;
using System.Collections.Generic;
using System.Data;
using System.Data.OleDb;
using System.IO;
using System.Text;
using System.Text.RegularExpressions;
using NPOI;
using NPOI.POIFS;
using NPOI.HSSF;
using NPOI.Util;
using NPOI.POIFS.FileSystem;
using NPOI.SS.UserModel;
using NPOI.HSSF.UserModel;


namespace 特征提取
{
    class Program
    {
        /// <summary>
        /// 实例数
        /// </summary>
        public static int insCount;
        /// <summary>
        /// 特征数
        /// </summary>
        public static int attCount;

        public static List<Instance> ins;

        public static List<Attribute> att;

        public static List<miXi> miC;

        public static List<cmiXY> cmiC;

        public struct miXi
        {
            public string name;
            public double miValue;
        }

        public struct cmiXY
        {
            public string xName;
            public string yName;
            public double value;
        }

        public struct mutualValue
        {
            public string a1Value;
            public string a2Value;
            public int times;
        }

        public struct cmiValue
        {
            public int number;
            public double value;
        }

        public struct Distance
        {
            public string xName;
            public string yName;
            public double value;
        }

        static void Main(string[] args)
        {
            string fileName = "wine";
            /*
               #region 生成实例和特征的list medelon
               DataSet data1 = getDatasetFromXlsx("madelon_train_1.xlsx");
               DataSet data2 = getDatasetFromXlsx("madelon_train_2.xlsx");//各250列，因为单独读一个excel表，有255列的限制
               DataSet label = getDatasetFromXlsx("madelon_train_labels.xlsx");
               insCount = label.Tables[0].Rows.Count;
               attCount = data1.Tables[0].Columns.Count + data2.Tables[0].Columns.Count;
               DataTable dt = new DataTable();

               #region 将data1和data2合并到dt当中
               DataColumn dc = null;
               dc = dt.Columns.Add("0", System.Type.GetType("System.String"));//类型区分大小写
               dc.AutoIncrement = true;//自动增加
               dc.AutoIncrementSeed = 1;//起始为1
               dc.AutoIncrementStep = 1;//步长为1
               for (int i = 0; i < attCount - 1; i++)
               {
                   dc = dt.Columns.Add((i + 1).ToString(), System.Type.GetType("System.String"));
               }
               for (int i = 0; i < insCount; i++)
               {
                   DataRow dr = dt.NewRow();
                   for (int j = 0; j < data1.Tables[0].Columns.Count; j++)
                   {
                       dr[j.ToString()] = data1.Tables[0].Rows[i][j].ToString();
                   }
                   for (int j = 0; j < data2.Tables[0].Columns.Count; j++)
                   {
                       dr[(j + data1.Tables[0].Columns.Count).ToString()] = data2.Tables[0].Rows[i][j].ToString();
                   }
                   dt.Rows.Add(dr);
               }
               #endregion

               ins = new List<Instance>();
               att = new List<Attribute>();

               //Console.WriteLine(dt.Columns.Count.ToString());

               //类别作为最后一条特殊的特征加入list的最后
               //生成实例list
               for (int i = 0; i < insCount; i++)
               {
                   Instance instance = new Instance();
                   instance.Number = i.ToString();
                   instance.Type = label.Tables[0].Rows[i][0].ToString();
                   List<string> ss = new List<string>();
                   for (int j = 0; j < attCount; j++)
                   {
                       ss.Add(dt.Rows[i][j].ToString());
                   }
                   ss.Add(label.Tables[0].Rows[i][0].ToString());
                   instance.Attributes = ss;
                   ins.Add(instance);
               }
               //生成特征list
               for (int i = 0; i < attCount; i++)
               {
                   Attribute attribute = new Attribute();
                   attribute.Name = i.ToString();
                   List<string> ss = new List<string>();
                   for (int j = 0; j < insCount; j++)
                   {
                       ss.Add(dt.Rows[j][i].ToString());
                   }
                   attribute.Values = ss;
                   attribute.getAttributeValues();
                   att.Add(attribute);
               }
               Attribute typeAttribute = new Attribute();
               typeAttribute.Name = attCount.ToString();
               List<string> sType = new List<string>();
               for (int j = 0; j < insCount; j++)
               {
                   sType.Add(label.Tables[0].Rows[j][0].ToString());
               }
               typeAttribute.Values = sType;
               typeAttribute.getAttributeValues();
               att.Add(typeAttribute);
               #endregion*/



            #region arrhythmia//wine
            List<string> data = ReadData("wine.data.txt");
            ins = new List<Instance>();
            att = new List<Attribute>();
            List<string[]> dataValue = new List<string[]>();
            for (int i = 0; i < data.Count; i++)
            {
                string[] values = data[i].Split(',');
                dataValue.Add(values);
            }
            insCount = data.Count;
            attCount = dataValue[0].Length - 1;
            //生成实例list
            for (int i = 0; i < insCount; i++)
            {
                Instance instance = new Instance();
                instance.Number = i.ToString();
                instance.Type = dataValue[i][0].ToString();
                List<string> ss = new List<string>();
                for (int j = 1; j < attCount + 1; j++)
                {
                    ss.Add(dataValue[i][j].ToString());
                }
                ss.Add(dataValue[i][0].ToString());
                instance.Attributes = ss;
                ins.Add(instance);
            }
            //生成特征list
            for (int i = 0; i < attCount + 1; i++)
            {
                Attribute attribute = new Attribute();
                attribute.Name = i.ToString();
                List<string> ss = new List<string>();
                for (int j = 0; j < insCount; j++)
                {
                    ss.Add(ins[j].Attributes[i].ToString());
                }
                attribute.Values = ss;
                attribute.getAttributeValues();
                att.Add(attribute);
            }
            #endregion



            Console.WriteLine("Data imported ！");

          
            miC = new List<miXi>();
            cmiC = new List<cmiXY>();

              /*
            #region 计算mi和cmi
            for (int i = 0; i < attCount; i++)
            {
                double IXiC = mutualInformation(i.ToString(), attCount.ToString());// I(Xi;C)
                 miXi mi = new miXi();
                mi.miValue = IXiC;
                mi.name = i.ToString();
                miC.Add(mi);
            }
            StreamWriter sw1 = new StreamWriter(fileName+"_mi.txt", false, Encoding.UTF8);
            for (int i = 0; i < miC.Count; i++)
            {
                sw1.Write(miC[i].name + "    " + miC[i].miValue.ToString() + "\r\n");
            }
            sw1.Close();
            Console.WriteLine("mi calculated！");
            for (int i = 0; i < attCount; i++)
            {
                for (int j = 0; j < attCount; j++)
                {
                    double cmiValue = conditionalMutualInformation(i.ToString(), attCount.ToString(), j.ToString());
                    cmiXY cmi = new cmiXY();
                    cmi.xName = i.ToString();
                    cmi.yName = j.ToString();
                    cmi.value = cmiValue;
                    cmiC.Add(cmi);
                    Console.WriteLine((i * 500 + j).ToString());
                }
            }
            StreamWriter sw2 = new StreamWriter(fileName +"_cmi.txt", false, Encoding.UTF8);
            for (int i = 0; i < cmiC.Count; i++)
            {
                sw2.Write(cmiC[i].xName + "    " + cmiC[i].yName + "    " + cmiC[i].value.ToString() + "\r\n");
            }
            sw2.Close();
            Console.WriteLine("cmi calculated！");
            #endregion
            */

            
            List<string> miCData = ReadData(fileName + "_mi.txt");
            List<string> cmiCData = ReadData(fileName + "_cmi.txt");
            for (int i = 0; i < miCData.Count; i++)
            {
                string s = Regex.Replace(miCData[i], @"\s+", " ");
                string[] ss = s.Split(' ');
                miXi m = new miXi();
                m.name = ss[0];
                m.miValue = Convert.ToDouble(ss[1]);
                miC.Add(m);
            }
            for (int i = 0; i < cmiCData.Count; i++)
            {
                string s = Regex.Replace(cmiCData[i], @"\s+", " ");
                string[] ss = s.Split(' ');
                cmiXY c = new cmiXY();
                c.xName = ss[0];
                c.yName = ss[1];
                c.value = Convert.ToDouble(ss[2]);
                cmiC.Add(c);
            }
            Console.WriteLine("mi and cmi imported");
             

           /*
            //Algorithm (x)
            List<int> ChosedNum = new List<int>();
            string aNumber = "01";//算法序号
            int kNumber = 6;//提取的特征数
            HSSFWorkbook hssfworkbook = new HSSFWorkbook();//创建工作本
            ISheet sheet1 = hssfworkbook.CreateSheet("Sheet1");//创建表
            for (int i = 0; i < kNumber; i++)
            {
                sheet1.CreateRow(i);
            }
            for (int p = 0; p <1; p++)
            {
                double pNumber = 1 * Convert.ToDouble(p);//系数
                ChosedNum= Algorithm1(kNumber, pNumber);//算法
                StreamWriter sw = new StreamWriter(fileName + "_features_" + aNumber + "_" + kNumber.ToString() + "_" + pNumber.ToString() + ".txt", false, Encoding.UTF8);
                for (int i = 0; i < ChosedNum.Count; i++)
                {
                    sheet1.GetRow(i).CreateCell(p).SetCellValue(ChosedNum[i]);//表操作
                    //Console.WriteLine(ChosedNum[i].ToString());
                    sw.Write(ChosedNum[i].ToString() + "\r\n");
                }
                sw.Close();
                Console.WriteLine("Algorithm done");
            }
            //通过filestream写入
            FileStream file = new FileStream(fileName + "_features_" + aNumber + "_" + kNumber.ToString() + ".xls", FileMode.Create);
            hssfworkbook.Write(file);
            file.Close();
            Console.WriteLine("save done");
            */
            
            List<int> ChosedNum;
            List<string> AttributeNumber;
            string add = fileName+"_features_01_6_0";
            ChosedNum = new List<int>();
            AttributeNumber = new List<string>();
            AttributeNumber = ReadData(add + ".txt");
            for (int i = 0; i < AttributeNumber.Count; i++)
            {
                ChosedNum.Add(Convert.ToInt32(AttributeNumber[i]));
            }
            Console.WriteLine("BeginToExport");
            ChosedToExcel(ChosedNum, add);
             
            /*
            List<int> ChosedNum;
            List<string> AttributeNumber;
            for (int n = 10; n < 30; n++)
            {
                n = n * 1;
                string add = fileName+"_features_01_6_"+n.ToString();
                ChosedNum = new List<int>();
                AttributeNumber = new List<string>();
                AttributeNumber = ReadData(add + ".txt");
                for (int i = 0; i < AttributeNumber.Count; i++)
                {
                    ChosedNum.Add(Convert.ToInt32(AttributeNumber[i]));
                }
                Console.WriteLine("BeginToExport");
                ChosedToExcel(ChosedNum, add);             
            }
             */

            Console.ReadLine();
        }

        static List<int> Algorithm0(int kNumber, double pNumber)
        {
            List<int> chosedNum = new List<int>();
            int k = kNumber;//特征数
            double p = pNumber;//系数
            for (int i = 0; i < k; i++)
            {
                if (chosedNum.Count == 0)
                {
                    List<double> miList = new List<double>();
                    for (int j = 0; j < attCount; j++)
                    {
                        double IXiC = getMiC(j.ToString());// I(Xi;C)
                        miList.Add(IXiC);
                    }

                    #region 找最大
                    int miBest = -1;
                    double miBestValue = -100;
                    for (int n = 0; n < attCount; n++)
                    {
                        if (miBestValue > miList[n])
                            continue;
                        else
                        {
                            miBest = n;
                            miBestValue = miList[n];
                        }
                    }
                    // Console.WriteLine(miBest.ToString());
                    chosedNum.Add(miBest);
                    #endregion
                }
                else
                {
                    List<cmiValue> cmiList = new List<cmiValue>();
                    for (int j = 0; j < attCount; j++)
                    {
                        int vector = 1;
                        foreach (int a in chosedNum)
                        {
                            if (j == a)
                                vector = 0;
                        }
                        if (vector == 1)
                        {
                            double IXiC = getMiC(j.ToString());// I(Xi;C)
                            double sum = 0;                                                        //sum(S) I(Xi;C|Xj)+I(Xi;C|Xj)
                            foreach (int a in chosedNum)
                            {
                                sum += getCmiC(j.ToString(), a.ToString()) + getCmiC(a.ToString(), j.ToString());
                            }
                            double Jcmi = IXiC + p * sum;//系数
                            cmiValue cv = new cmiValue();
                            cv.number = j;
                            cv.value = Jcmi;
                            cmiList.Add(cv);
                        }
                    }
                    #region 找最大
                    int cmiBest = -1;
                    double cmiBestValue = -100;
                    for (int n = 0; n < cmiList.Count; n++)
                    {
                        if (cmiBestValue > cmiList[n].value)
                            continue;
                        else
                        {
                            cmiBest = cmiList[n].number;
                            cmiBestValue = cmiList[n].value;
                        }
                    }
                    //Console.WriteLine(cmiBest.ToString());
                    chosedNum.Add(cmiBest);
                    #endregion
                }
            }
            return chosedNum;
        }

        static List<int> Algorithm1(int kNumber, double pNumber)
        {
            List<int> chosedNum = new List<int>();
            int k = kNumber;//特征数
            double p = pNumber;//系数
            List<double> distance = new List<double>();
            for (int i = 0; i < attCount; i++)
            {
                for (int j = 0; j < attCount; j++)
                {
                    double d;
                    if (i == j)
                        d = -100;
                    else
                        //d =(getCmiC(i.ToString(), j.ToString()) + getCmiC(j.ToString(), i.ToString()));
                        d = getMiC(i.ToString()) + getMiC(j.ToString()) + (2 * p / (k - 1)) * (getCmiC(i.ToString(), j.ToString()) + getCmiC(j.ToString(), i.ToString()));
                    distance.Add(d);
                }
            }
            for (int m = 0; m < k / 2; m++)
            {
                if (chosedNum.Count == 0)
                {
                    #region 找最大
                    int dBest = -1;
                    double dBestValue = -100;
                    for (int n = 0; n < distance.Count; n++)
                    {
                        if (dBestValue > distance[n])
                            continue;
                        else
                        {
                            dBest = n;
                            dBestValue = distance[n];
                        }
                    }
                    int x = dBest / attCount;
                    int y = dBest % attCount;
                    // Console.WriteLine(x.ToString() + "\r\n" + y.ToString());
                    chosedNum.Add(x);
                    chosedNum.Add(y);
                    #endregion
                }
                else
                {
                    int dBest = -1;
                    double dBestValue = -100;
                    for (int n = 0; n < distance.Count; n++)
                    {
                        int vector = 1;
                        foreach (int a in chosedNum)
                        {
                            if (n / attCount == a || n % attCount == a)
                            {
                                vector = 0;
                            }
                        }
                        if (vector == 1)
                        {
                            if (dBestValue > distance[n])
                                continue;
                            else
                            {
                                dBest = n;
                                dBestValue = distance[n];
                            }
                        }
                    }
                    int x = dBest / attCount;
                    int y = dBest % attCount;
                    //Console.WriteLine(x.ToString() + "\r\n" + y.ToString());
                    chosedNum.Add(x);
                    chosedNum.Add(y);
                }
            }
            if (k % 2 != 0)
            {
                List<double> miList = new List<double>();
                for (int j = 0; j < attCount; j++)
                {
                    double IXiC = getMiC(j.ToString());// I(Xi;C)
                    miList.Add(IXiC);
                }
                int miBest = -1;
                double miBestValue = -100;
                for (int n = 0; n < attCount; n++)
                {
                    int vector = 1;
                    foreach (int a in chosedNum)
                    {
                        if (n == a)
                        {
                            vector = 0;
                        }
                    }
                    if (vector == 1)
                    {
                        if (miBestValue > miList[n])
                            continue;
                        else
                        {
                            miBest = n;
                            miBestValue = miList[n];
                        }
                    }
                }
                // Console.WriteLine(miBest.ToString());
                chosedNum.Add(miBest);
            }
            return chosedNum;
        }

        static List<int> Algorithm2(int kNumber, double pNumber)
        {
            List<int> chosedNum = new List<int>();
            int k = kNumber;//特征数
            double p = pNumber;//系数
            for (int i = 0; i < k; i++)
            {
                if (chosedNum.Count == 0)
                {
                    List<double> miList = new List<double>();
                    for (int j = 0; j < attCount; j++)
                    {
                        double IXiC = getMiC(j.ToString());// I(Xi;C)
                        miList.Add(IXiC);
                    }

                    #region 找最大
                    int miBest = -1;
                    double miBestValue = -100;
                    for (int n = 0; n < attCount; n++)
                    {
                        if (miBestValue > miList[n])
                            continue;
                        else
                        {
                            miBest = n;
                            miBestValue = miList[n];
                        }
                    }
                    // Console.WriteLine(miBest.ToString());
                    chosedNum.Add(miBest);
                    #endregion
                }
                else
                {
                    List<cmiValue> gList = new List<cmiValue>();
                    for (int j = 0; j < attCount; j++)
                    {
                        int vector = 1;
                        foreach (int a in chosedNum)
                        {
                            if (j == a)
                                vector = 0;
                        }
                        if (vector == 1)
                        {
                            double IXiC = getMiC(j.ToString());// I(Xi;C)
                            double sum = 0;                                                        //sum(S) I(Xi;C|Xj)+I(Xi;C|Xj)
                            foreach (int a in chosedNum)
                            {
                                Distance d = getDistance(j.ToString(), a.ToString());
                                Distance dc = getDistanceC(d);
                                sum += 1.0 / 2.0 * d.value - 1.0 / 4.0 * dc.value;
                            }
                            Console.WriteLine(IXiC.ToString());
                            Console.WriteLine(sum.ToString());
                            double gValue = 1 / 2 * IXiC + p * sum;//系数
                            cmiValue cv = new cmiValue();
                            cv.number = j;
                            cv.value = gValue;
                            gList.Add(cv);
                        }
                    }
                    #region 找最大
                    int gBest = -1;
                    double gBestValue = -100;
                    for (int n = 0; n < gList.Count; n++)
                    {
                        if (gBestValue > gList[n].value)
                            continue;
                        else
                        {
                            gBest = gList[n].number;
                            gBestValue = gList[n].value;
                        }
                    }
                    // Console.WriteLine(gBest.ToString());
                    chosedNum.Add(gBest);
                    #endregion
                }
            }
            return chosedNum;
        }

        static Distance getDistance(string xName, string yName)
        {
            Distance d = new Distance();
            d.xName = xName;
            d.yName = yName;
            Attribute x = new Attribute();
            Attribute y = new Attribute();
            foreach (Attribute a in att)
            {
                if (a.Name == xName)
                    x = a;
                if (a.Name == yName)
                    y = a;
            }
            double Hx = 0;
            double Hy = 0;
            for (int i = 0; i < x.attValues.Count; i++)
            {
                double px = Convert.ToDouble(x.attValues[i].times) / Convert.ToDouble(insCount);
                Hx -= px * Math.Log(px, 2);
            }
            for (int i = 0; i < y.attValues.Count; i++)
            {
                double py = Convert.ToDouble(y.attValues[i].times) / Convert.ToDouble(insCount);
                Hy -= py * Math.Log(py, 2);
            }
            d.value = Hx + Hy - 2 * mutualInformation(xName, yName);
            Console.WriteLine("d:  "+d.value.ToString());
            return d;
        }

        static Distance getDistanceC(Distance d)
        {
            Distance dc = new Distance();
            dc.xName = d.xName;
            dc.yName = d.yName;
            dc.value = d.value - getCmiC(d.xName, d.yName) - getCmiC(d.yName, d.xName);
            Console.WriteLine("dc:  "+dc.value.ToString());
            return dc;
        }

        /// <summary>
        /// 互信息计算
        /// </summary>
        /// <param name="attributeName1"></param>
        /// <param name="attributeName2"></param>
        /// <returns></returns>
        static double mutualInformation(string attributeName1, string attributeName2)//name就是序号
        {
            double mi = 0;
            Attribute a1 = new Attribute();
            Attribute a2 = new Attribute();
            foreach (Attribute a in att)
            {
                if (a.Name == attributeName1)
                    a1 = a;
                if (a.Name == attributeName2)
                    a2 = a;
            }
            double Px, Py, Pxy;
            List<mutualValue> mutualAtt = findPxy(a1, a2, ins);
            for (int k = 0; k < mutualAtt.Count; k++)
            {
                for (int i = 0; i < a1.attValues.Count; i++)
                {
                    if (mutualAtt[k].a1Value == a1.attValues[i].value)
                    {
                        for (int j = 0; j < a2.attValues.Count; j++)
                        {
                            if (mutualAtt[k].a2Value == a2.attValues[j].value)
                            {
                                string x = a1.attValues[i].value;
                                string y = a2.attValues[j].value;
                                Px = Convert.ToDouble(a1.attValues[i].times) / Convert.ToDouble(insCount);
                                Py = Convert.ToDouble(a2.attValues[j].times) / Convert.ToDouble(insCount);
                                Pxy = Convert.ToDouble(mutualAtt[k].times) / Convert.ToDouble(insCount);
                                mi -= Pxy * Math.Log(Pxy / (Px * Py), 2);
                            }
                        }
                    }
                }
            }
            return mi;
        }

        /// <summary>
        /// 条件互信息计算
        /// </summary>
        /// <param name="xName"></param>
        /// <param name="yName"></param>
        /// <param name="zName"></param>
        /// <returns></returns>
        static double conditionalMutualInformation(string xName, string yName, string zName)
        {
            double cmi = 0;
            Attribute z = new Attribute();
            foreach (Attribute a in att)
            {
                if (a.Name == zName)
                    z = a;
            }
            for (int i = 0; i < z.attValues.Count; i++)
            {
                double Pz;
                string zValue = z.attValues[i].value;
                Pz = Convert.ToDouble(z.attValues[i].times) / Convert.ToDouble(insCount);

                List<Attribute> attZ = new List<Attribute>();
                List<Instance> insZ = new List<Instance>();

                #region 构建新的实例和特征list
                for (int j = 0; j < insCount; j++)
                {
                    if (ins[j].Attributes[Convert.ToInt32(zName)] == zValue)
                    {
                        insZ.Add(ins[j]);
                    }
                }

                for (int k = 0; k < attCount; k++)
                {
                    Attribute attribute = new Attribute();
                    attribute.Name = k.ToString();
                    attribute.Values = new List<string>();
                    for (int l = 0; l < insZ.Count; l++)
                    {
                        attribute.Values.Add(insZ[l].Attributes[Convert.ToInt32(attribute.Name)]);
                    }
                    attribute.getAttributeValues();
                    attZ.Add(attribute);
                }

                Attribute typeAttribute = new Attribute();
                typeAttribute.Name = attCount.ToString();
                List<string> sType = new List<string>();
                for (int j = 0; j < insZ.Count; j++)
                {
                    sType.Add(insZ[j].Attributes[Convert.ToInt32(typeAttribute.Name)]);
                }
                typeAttribute.Values = sType;
                typeAttribute.getAttributeValues();
                attZ.Add(typeAttribute);
                #endregion

                Attribute x = new Attribute();
                Attribute y = new Attribute();
                foreach (Attribute a in attZ)
                {
                    if (a.Name == xName)
                        x = a;
                    if (a.Name == yName)
                        y = a;
                }

                List<mutualValue> mutualAttZ = findPxy(x, y, insZ);

                double mi = 0;
                for (int k = 0; k < mutualAttZ.Count; k++)
                {
                    for (int m = 0; m < x.attValues.Count; m++)
                    {
                        if (mutualAttZ[k].a1Value == x.attValues[m].value)
                        {
                            for (int j = 0; j < y.attValues.Count; j++)
                            {
                                if (mutualAttZ[k].a2Value == y.attValues[j].value)
                                {
                                    double Px, Py, Pxy;
                                    string xs = x.attValues[m].value;
                                    string ys = y.attValues[j].value;
                                    Px = Convert.ToDouble(x.attValues[m].times) / Convert.ToDouble(insCount);
                                    Py = Convert.ToDouble(y.attValues[j].times) / Convert.ToDouble(insCount);
                                    Pxy = Convert.ToDouble(mutualAttZ[k].times) / Convert.ToDouble(insCount);
                                    mi -= Pxy * Math.Log(Pxy / (Px * Py), 2);
                                }
                            }
                        }
                    }
                }
                cmi += Pz * mi;
            }
            return cmi;
        }

        /// <summary>
        /// 计算同时出现的次数
        /// </summary>
        /// <param name="a1"></param>
        /// <param name="a2"></param>
        /// <param name="instance"></param>
        /// <returns></returns>
        static List<mutualValue> findPxy(Attribute a1, Attribute a2, List<Instance> instance)
        {
            List<mutualValue> mutualList = new List<mutualValue>();
            string value1, value2;
            for (int n = 0; n < instance.Count; n++)
            {
                value1 = instance[n].Attributes[Convert.ToInt32(a1.Name)].ToString();
                value2 = instance[n].Attributes[Convert.ToInt32(a2.Name)].ToString();


                if (mutualList.Count==0||mutualList==null)
                {
                    mutualValue mv;
                    mv.a1Value = value1;
                    mv.a2Value = value2;
                    mv.times = 1;
                    mutualList.Add(mv);
                }
                else
                {
                    int vector = 1;//为1时表示遇到新的成员
                    for (int i = 0; i < mutualList.Count; i++)
                    {
                        if (value1 != mutualList[i].a1Value || value2 != mutualList[i].a2Value)
                            continue;
                        else
                        {
                            vector = 0;
                            mutualValue mv = mutualList[i];
                            mv.times++;
                            mutualList[i] = mv;
                        }
                    }
                    if (vector == 1)
                    {
                        mutualValue mv;
                        mv.a1Value = value1;
                        mv.a2Value = value2;
                        mv.times = 1;
                        mutualList.Add(mv);
                    }
                }
            }
            return mutualList;
        }

        static double getMiC(string name)
        {
            foreach (miXi mixi in miC)
            {
                if (mixi.name != name)
                    continue;
                else
                {
                    return mixi.miValue;
                }
            }
            return 0;
        }

        static double getCmiC(string xName, string yName)
        {
            foreach (cmiXY cmi in cmiC)
            {
                if (cmi.xName != xName || cmi.yName != yName)
                    continue;
                else
                {
                    return cmi.value;
                }
            }
            return 0;
        }

        static void ChosedToExcel(List<int> ChosedNum, string add)
        {
            HSSFWorkbook hssfworkbook = new HSSFWorkbook();//创建工作本
            ISheet sheet1 = hssfworkbook.CreateSheet("Sheet1");//创建表
            //sheet1.SetColumnWidth(0, 100 * 256);//设置表宽
            for (int i = 0; i <= ins.Count; i++)
            {
                sheet1.CreateRow(i);
            }

            for (int i = 0; i < ChosedNum.Count; i++)
            {
                sheet1.GetRow(0).CreateCell(i).SetCellValue(ChosedNum[i]);
                for (int j = 0; j < ins.Count; j++)
                {
                    sheet1.GetRow(j + 1).CreateCell(i).SetCellValue(Convert.ToDouble(att[ChosedNum[i]].Values[j]));
                }
            }
            sheet1.GetRow(0).CreateCell(ChosedNum.Count).SetCellValue("type");
            for (int i = 0; i < ins.Count; i++)
            {
                sheet1.GetRow(i + 1).CreateCell(ChosedNum.Count).SetCellValue(att[att.Count - 1].Values[i].ToString());
            }
            //通过filestream写入
            FileStream file = new FileStream(add + ".xls", FileMode.Create);
            hssfworkbook.Write(file);
            file.Close();

            Console.WriteLine("ExportDone");
        }

        /// <summary>
        /// 从xlsx文件中提取dataset
        /// </summary>
        /// <param name="filenameurl"></param>
        /// <returns>
        /// 需要安装 http://download.microsoft.com/download/7/0/3/703ffbcb-dc0c-4e19-b0da-1463960fdcdb/AccessDatabaseEngine.exe 
        /// 第一行为列名
        /// </returns>
        static DataSet getDatasetFromXlsx(string filenameurl)
        {
            string strConn = "Provider=Microsoft.Ace.OleDb.12.0;" + "data source=" + filenameurl + ";Extended Properties='Excel 12.0; HDR=YES; IMEX=1'";
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

        static DataSet getDatasetFromXls(string filenameurl)
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

        static List<string> ReadData(string name)
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
    }
}
