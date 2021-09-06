using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace question3
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            double salary;
            int level;
            double bonus;
            double.TryParse(textBox1.Text, out salary);
            int.TryParse(comboBox1.Text, out level);
            string temp;
            if (level == 1)
                bonus = 0.1 * salary;
            else if (level > 1 || level < 5)
                bonus = 0.09 * salary;
            else if (level > 4 || level < 8)
                bonus = 0.07 * salary;
            else
                bonus = 0.05 * salary;
            temp = " The bonus computed - " + bonus.ToString();
            label4.Text = temp; 
        }

        private void label2_Click(object sender, EventArgs e)
        {

        }
    }
}
