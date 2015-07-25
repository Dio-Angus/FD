using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 特征提取
{
    class Attribute
    {
        /// <summary>
        /// 特征的名称或序号
        /// </summary>
        private string name;
        /// <summary>
        /// 特征的内容（特征所在那一列）
        /// </summary>
        private List<string> values=null;
        /// <summary>
        /// 特征的可能取值
        /// </summary>
        private List<attributeValue> attributeValues=null;

        public string Name
        {
            get { return name; }
            set { name = value; }
        }
        public List<string> Values
        {
            get { return values; }
            set { values = value; }
        }

        public List<attributeValue> attValues
        {
            get { return attributeValues; }
        }

        public struct attributeValue
        {
            public string value;
            public int times;
        }

        public void getAttributeValues()
        {
            if (values == null)
                return;
            foreach (string value in values)//生成AttributeValues
            {                
                if (attributeValues == null)
                {
                    attributeValue av;
                    av.value = value;
                    av.times = 1;
                    attributeValues = new List<attributeValue>();
                    attributeValues.Add(av);
                }
                else
                {
                    int vector = 1;
                    for (int i = 0; i < attributeValues.Count; i++)
                    {
                        if (value != attributeValues[i].value)
                            continue;
                        else
                        {
                            vector = 0;
                            attributeValue av = attributeValues[i];
                            av.times++;
                            attributeValues[i]=av;
                        }
                    }
                    if (vector == 1)
                    {
                        attributeValue av;
                        av.value = value;
                        av.times = 1;
                        attributeValues.Add(av);
                    }
                }
            }

        }
    }
}
