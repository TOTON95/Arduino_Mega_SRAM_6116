//Coded by Alexis Guijarro

﻿using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.IO.Ports;

namespace ARDUINO_RAM_7SEG_LCD
{
    /// <summary>
    /// Lógica de interacción para MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public string[] ports = SerialPort.GetPortNames();
        public SerialPort arduino = new SerialPort();
        string buff= "";

        public MainWindow()
        {
            InitializeComponent();
            suma.IsEnabled = false;
            resta.IsEnabled = false;
            division.IsEnabled = false;
            multiplicacion.IsEnabled = false;
            txt_1.IsEnabled = false;
            txt_2.IsEnabled = false;
            txt_3.IsEnabled = false;
            txt_4.IsEnabled = false;
            txt_5.IsEnabled = false;
            enviar.IsEnabled = false;

        }
        public void SerialInit(string portselected)
        {
            arduino.PortName = portselected;
            arduino.BaudRate = 19200;
           
            try
            {
                arduino.Open();
                label2.Content = "Conectado a Arduino en el puerto " + portselected;
                if (!label2.IsVisible)
                {
                    Action act = () => { label2.Visibility = Visibility.Visible; };
                    label2.Dispatcher.Invoke(act);
                }
                ellipse1.Visibility = Visibility.Visible;
                enviar.IsEnabled = true;

            }

            catch (InvalidOperationException) { }
            catch (ArgumentOutOfRangeException) { }
            catch (ArgumentException) { }
            catch (System.IO.IOException) { }
            catch (UnauthorizedAccessException)
            {
                MessageBox.Show("Puerto en Uso por Otra Aplicación", "ERROR", MessageBoxButton.OK, MessageBoxImage.Error);
            }
        }
        private void button1_Click(object sender, RoutedEventArgs e)
        {
            if (comboBox1.SelectedItem != null)
            {
                string selected = comboBox1.SelectedItem.ToString();
                if (arduino.IsOpen == false)
                {
                    SerialInit(selected);
                }
                else
                {
                    try
                    {
                        arduino.Close();
                    }
                    catch (InvalidOperationException) { }
                    ellipse1.Visibility = Visibility.Hidden;
                    SerialInit(selected);
                }
            }
        }
        private void button2_Click(object sender, RoutedEventArgs e)
        {
            ports = SerialPort.GetPortNames();
            comboBox1.ItemsSource = ports;
        }
        private void Window_Closing(object sender, System.ComponentModel.CancelEventArgs e)
        {
            if (arduino.IsOpen)
            {
                try
                {
                    arduino.DiscardInBuffer();
                    arduino.DiscardOutBuffer();
                    arduino.Close();
                    arduino.Dispose();
                }
                catch (InvalidOperationException) { }
            }
        }

        private void rd_operacion_Checked(object sender, RoutedEventArgs e)
        {
            suma.IsEnabled = true;
            resta.IsEnabled = true;
            division.IsEnabled = true;
            multiplicacion.IsEnabled = true;
            txt_4.IsEnabled = true;
            txt_5.IsEnabled = true;
        }

        private void rd_operacion_Unchecked(object sender, RoutedEventArgs e)
        {
            suma.IsEnabled = false;
            resta.IsEnabled = false;
            division.IsEnabled = false;
            multiplicacion.IsEnabled = false;
            txt_4.IsEnabled = false;
            txt_5.IsEnabled = false;
        }

        private void rd_lectura_Checked(object sender, RoutedEventArgs e)
        {
            txt_1.IsEnabled = true;
        }

        private void rd_escritura_Checked(object sender, RoutedEventArgs e)
        {
            txt_2.IsEnabled = true;
            txt_3.IsEnabled = true;
        }

        private void rd_lectura_Unchecked(object sender, RoutedEventArgs e)
        {
            txt_1.IsEnabled = false;
        }

        private void rd_escritura_Unchecked(object sender, RoutedEventArgs e)
        {
            txt_2.IsEnabled = false;
            txt_3.IsEnabled = false;
        }

        private void txt_1_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            tb.Text = string.Empty;
            tb.GotFocus -= txt_1_GotFocus;
        }

        private void txt_1_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            if (tb.Text == string.Empty)
            {
                tb.Text = "15";
                tb.GotFocus += txt_1_GotFocus;
            }
            else
            {
                try
                {
                    Convert.ToInt32(tb.Text);
                }
                catch(FormatException)
                {
                    tb.Text = "15";
                    MessageBox.Show("Sólo se pueden introducir números", "Advertencia", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void txt_2_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            tb.Text = string.Empty;
            tb.GotFocus -= txt_2_GotFocus;
        }

        private void txt_2_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            if (tb.Text == string.Empty)
            {
                tb.Text = "15";
                tb.GotFocus += txt_2_GotFocus;
            }
            else
            {
                try
                {
                    Convert.ToInt32(tb.Text);
                }
                catch (FormatException)
                {
                    tb.Text = "15";
                    MessageBox.Show("Sólo se pueden introducir números", "Advertencia", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void txt_3_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            tb.Text = string.Empty;
            tb.GotFocus -= txt_3_GotFocus;
        }

        private void txt_3_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            if (tb.Text == string.Empty)
            {
                tb.Text = "9";
                tb.GotFocus += txt_3_GotFocus;
            }
            else
            {
                try
                {
                    Convert.ToInt32(tb.Text);
                }
                catch (FormatException)
                {
                    tb.Text = "9";
                    MessageBox.Show("Sólo se pueden introducir números","Advertencia",MessageBoxButton.OK,MessageBoxImage.Error);
                }
            }
        }

        private void txt_4_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            tb.Text = string.Empty;
            tb.GotFocus -= txt_4_GotFocus;
        }

        private void txt_4_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            if (tb.Text == string.Empty)
            {
                tb.Text = "15";
                tb.GotFocus += txt_4_GotFocus;
            }
            else
            {
                try
                {
                    Convert.ToInt32(tb.Text);
                }
                catch (FormatException)
                {
                    tb.Text = "15";
                    MessageBox.Show("Sólo se pueden introducir números", "Advertencia", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void txt_5_GotFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            tb.Text = string.Empty;
            tb.GotFocus -= txt_5_GotFocus;
        }

        private void txt_5_LostFocus(object sender, RoutedEventArgs e)
        {
            TextBox tb = (TextBox)sender;
            if (tb.Text == string.Empty)
            {
                tb.Text = "15";
                tb.GotFocus += txt_5_GotFocus;
            }
            else
            {
                try
                {
                    Convert.ToInt32(tb.Text);
                }
                catch (FormatException)
                {
                    tb.Text = "15";
                    MessageBox.Show("Sólo se pueden introducir números", "Advertencia", MessageBoxButton.OK, MessageBoxImage.Error);
                }
            }
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            if (rd_lectura.IsChecked == true)
            {
                buff += 'R';
                buff += 'A';
                buff += txt_1.Text;
                buff += '*';
            }
            if (rd_escritura.IsChecked == true)
            {
                buff += 'W';
                buff += 'A';
                buff += txt_2.Text;
                buff += 'B';
                buff += txt_3.Text;
                buff += '*';
            }
            if (rd_operacion.IsChecked == true)
            {
                buff += 'O';
                buff += 'A';
                buff += txt_4.Text;
                if (suma.IsChecked == true)
                {
                    buff += '+';
                }
                if (resta.IsChecked == true)
                {
                    buff += '-';
                }
                if (division.IsChecked == true)
                {
                    buff += '/';
                }
                if (multiplicacion.IsChecked == true)
                {
                    buff += 'X';
                }
                buff += 'B';
                buff += txt_5.Text;
                buff += '*';
            }
            if(arduino.IsOpen)
            {
                arduino.WriteLine(buff);
                buff = "";
            }
            
        }
    }
}
