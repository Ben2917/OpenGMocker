using Microsoft.VisualStudio.PlatformUI;
using System.Globalization;
using System.Windows;
using System.Windows.Controls;

namespace OpenGMockerExtension
{
    public partial class RunOpenGMockerDialogWindow : DialogWindow
    {
        public RunOpenGMockerDialogWindow()
        {
            InitializeComponent();
            this.MinWidth = this.Width;
            this.MinHeight = this.Height;
            this.MaxWidth = this.Width;
            this.MaxHeight = this.Height;
        }

        private void SelectInputFileButtonClick(object sender, RoutedEventArgs e)
        { 

        }

        private void SelectOutputFileButtonClick(object sender, RoutedEventArgs e) 
        {

        }

        private void RunButtonClick(object sender, RoutedEventArgs e) 
        { 

        }

        private void CancelButtonClick(object sender, RoutedEventArgs e) 
        {
            this.Close();
        }
    }
}
