using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 网络爬虫
{
    class algorithm
    {
        static List<int> Algorithm1()
        {
            List<int> chosedNum = new List<int>();
            int k = 50;//特征数
            double p=0.5;//系数
            List<double> distance = new List<double>();
            for (int i = 0; i < attCount; i++)
            {
                for (int j = 0; j < attCount; j++)
                {
                    double d = getMiC(i.ToString()) + getMiC(j.ToString()) + (2 * p / (k - 1)) * (getCmiC(i.ToString(), j.ToString()) + getCmiC(j.ToString(), i.ToString()));
                    distance.Add(d);
                }
            }
            if (chosedNum.Count == 0)
            {
                #region 找最大
                int dBest = -1;
                double dBestValue = -100;
                for (int n = 0; n < distance.Count; n++)
                {
                    if (miBestValue > miList[n])
                        continue;
                    else
                    {
                        miBest = n;
                        miBestValue = miList[n];
                    }
                }
                int x = miBest / attCount;
                int y = miBest % attCount;
                Console.WriteLine(x.ToString() + "" + y.ToString());
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
                            if (n/attCount == a || n%attCount == a)
                            {
                                vector= 0;
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
                        int x = miBest / attCount;
                        int y = miBest % attCount;
                        Console.WriteLine(x.ToString() + "" + y.ToString());
                        chosedNum.Add(x);
                        chosedNum.Add(y);
                }
            }
            return chosedNum;
        }

        static List<int> Algorithm1()
        {
            List<int> chosedNum = new List<int>();
            int k = 50;//特征数
            double p = 0.5;
        }


    }
}
