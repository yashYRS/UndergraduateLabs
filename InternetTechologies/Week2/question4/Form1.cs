using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace question4
{
    public partial class Form1 : Form
    {
        string carName, model, colorName, price ;
        public Form1()
        {
            InitializeComponent();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox1.SelectedItem != null)
                carName = comboBox1.SelectedItem.ToString();
            else
                carName = ""; 
        }

        private void button2_Click(object sender, EventArgs e)
        {
            listBox1.ClearSelected() ;
            comboBox2.ResetText();
            comboBox1.ResetText();
            textBox1.Text = "PRICE : ";
            label4.Text = " "; 
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (listBox1.SelectedItem != null)
                model = listBox1.SelectedItem.ToString();
            else
                model = ""; 
        }

        private void comboBox2_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (comboBox2.SelectedItem != null)
                colorName = comboBox2.SelectedItem.ToString();
            else
                colorName = "";

        }

        private void label1_Click(object sender, EventArgs e)
        {

        }

        private void label2_Click(object sender, EventArgs e)
        {

        }

        private void label3_Click(object sender, EventArgs e)
        {

        }

        private void label4_Click(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            label4.Text = "Car -" +  carName + " Color -" + colorName + " Model Name - " + model + " Price - " + textBox1.Text + "\n THANK YOU FOR PURCHASING"; 
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
        }
    }
}
