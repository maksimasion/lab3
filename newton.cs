using System;
using System.IO;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Newton
{
    class Newton
    {
        public double dy(List<double> Y, List<double> X)
        {
            if (Y.Count > 2)
            {
                List<double> Yleft = new List<double>(Y);
                List<double> Xleft = new List<double>(X);
                Xleft.RemoveAt(0);
                Yleft.RemoveAt(0);
                List<double> Yright = new List<double>(Y);
                List<double> Xright = new List<double>(X);
                Xright.RemoveAt(Y.Count - 1);
                Yright.RemoveAt(Y.Count - 1);
                return (dy(Yleft, Xleft) - dy(Yright, Xright)) / (X[X.Count - 1] - X[0]);
            }
            else if (Y.Count == 2)
            {
                return (Y[1] - Y[0]) / (X[1] - X[0]);
            }
            else
            {
                throw new Exception("Not available parameter");
            }
        }

        public double GetValue(double[] X, double[] Y, double x)
        {
            double res = Y[0];
            double buf;
            List<double> Xlist;
            List<double> Ylist;
            for (int i = 1; i < Y.Length; i++)
            {
                Xlist = new List<double>();
                Ylist = new List<double>();
                buf = 1;
                for(int j = 0; j <= i; j++)
                {
                    Xlist.Add(X[j]);
                    Ylist.Add(Y[j]);
                    if (j<i)
                        buf *= x - X[0];
                }
                res += dy(Ylist, Xlist)*buf;
            }
            return res;
        }

        public double Factorial(int arg)
        {
            double res = 1;
            for(int i = 2; i <= arg; i++)
            {
                res *= i;
            }
            return res;
        }

        public double dy_h(List<double> Y, List<double> X, int number, int index)
        {
            if (number > 1)
            {
                return (dy_h(Y,X,number-1,index+1) - dy_h(Y, X, number - 1, index));
            }
            else if (number == 1)
            {
                return (Y[index+1] - Y[index]);
            }
            else
            {
                throw new Exception("Not available parameter");
            }
        }

        public double GetValue(double[] X, double[] Y, double x, double h)
        {
            double res = Y[0];
            double buf;
            List<double> Xlist = new List<double>(X);
            List<double> Ylist = new List<double>(Y);
            double q = (x - X[0]) / h;
            buf = 1;
            for (int i = 1; i < Y.Length; i++)
            {
                buf *= (q-i+1) / i;
                res += dy_h(Ylist, Xlist,i,0) * buf;
            }
            return res;
        }
    }
    class Program 
    {
        static void Main(string[] args)
        {
            System.Threading.Thread.CurrentThread.CurrentCulture = new System.Globalization.CultureInfo("en-US");
            string[] arStr = File.ReadAllLines("args.txt");
            StreamWriter In = new StreamWriter("data_real.txt");
            double[] X = new double[arStr.Length];
            for(int i = 0; i<arStr.Length; i++) 
            {
                X[i] = i;
            }
            double[] Y = new double[X.Length];
            for(int i = 0; i<X.Length; i++) 
            {
                Y[i] = double.Parse(arStr[i], System.Globalization.CultureInfo.InvariantCulture);
                In.WriteLine($"{i} {Y[i]}");
            }
            In.Close();
            Newton interpolation = new Newton();
            StreamWriter f = new StreamWriter("data_inter.txt");
            for(double i = 0; i<=X.Length-1; i=i+0.1) {
            double y = interpolation.GetValue(X, Y, i, 1);
            f.WriteLine($"{i} {y}");
            Console.WriteLine($"Interpolation by Newton for X = {i}, Y = {y}");
            }
            f.Close();
        }
    }
}