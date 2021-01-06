using Microsoft.Win32;
using Panuon.UI.Silver;
using System;
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

namespace Editor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class EditorMain : WindowX
    {
        public EditorMain()
        {
            InitializeComponent();
        }

        private void OnOpenItemClick(object sender, RoutedEventArgs e)
        {
            var dialog = new OpenFileDialog();
            dialog.Filter = ".jpg|*.jpg|.png|*.png|.jpeg|*.jpeg";
            if (dialog.ShowDialog(this) == false) 
                return;
            var fileName = dialog.FileName;
        }
    }
}
