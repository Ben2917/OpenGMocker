using Microsoft.VisualStudio.PlatformUI;
using System.Globalization;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Controls;

namespace OpenGMockerExtension
{
    public partial class RunOpenGMockerDialogWindow : DialogWindow
    {
        private bool inputFileSelected = false;
        private bool outputFileSelected = false;
        public RunOpenGMockerDialogWindow()
        {
            InitializeComponent();
            MinWidth = Width;
            MinHeight = Height;
            MaxWidth = Width;
            MaxHeight = Height;
        }

        private void SelectInputFileButtonClick(object sender, RoutedEventArgs e)
        {
            var inputFileDialog = new OpenFileDialog();
            if (inputFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                InputFileTextBox.Text = inputFileDialog.FileName;
                inputFileSelected = true;
            }
        }

        private void SelectOutputFileButtonClick(object sender, RoutedEventArgs e) 
        {
            var outputFileDialog = new SaveFileDialog();
            if (outputFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                OutputFileTextBox.Text = outputFileDialog.FileName;
                outputFileSelected = true;
            }
        }

        private void RunButtonClick(object sender, RoutedEventArgs e) 
        {
            if (!inputFileSelected)
            {
                System.Windows.Forms.MessageBox.Show("Please select an interface file to generate a mock from");
                return;
            }

            if (!outputFileSelected)
            {
                System.Windows.Forms.MessageBox.Show("Please select an output file to save the generated mock to");
                return;
            }

            System.Diagnostics.Process process = new System.Diagnostics.Process();
            System.Diagnostics.ProcessStartInfo startInfo = new System.Diagnostics.ProcessStartInfo();
            // startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
            startInfo.FileName = "OpenGMocker.exe";
            startInfo.Arguments = InputFileTextBox.Text + " " + OutputFileTextBox.Text;
            process.StartInfo = startInfo;
            process.Start();

            Close();
        }

        private void CancelButtonClick(object sender, RoutedEventArgs e) 
        {
            Close();
        }
    }
}
