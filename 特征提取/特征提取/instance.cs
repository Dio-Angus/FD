using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace 特征提取
{
    class Instance
    {
        private string number;
        private string type;//1,-1
        private List<string> attributes;
        public string Number
        {
            get { return number; }
            set { number = value; }
        }
        public string Type
        {
            get { return type; }
            set { type = value; }
        }
        public List<string> Attributes
        {
            get { return attributes; }
            set { attributes = value; }
        }


    }
}
