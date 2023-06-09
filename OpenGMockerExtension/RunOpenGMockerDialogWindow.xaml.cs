using Microsoft.VisualStudio.PlatformUI;
using System.Globalization;
using System.Windows;
using System.Windows.Forms;
using System.Windows.Controls;

namespace OpenGMockerExtension
{
    public partial class RunOpenGMockerDialogWindow : DialogWindow
    {
        private const int OK                   = 0;
        private const int INVALID_ARGS         = 1;
        private const int FILE_MOCKER_ERR      = 2;
        private const int CLASS_MOCKER_ERR     = 3;
        private const int FUNCTION_MOCKER_ERR  = 4;
        private const int UNKNOWN_ERR          = 5;

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
            }
        }

        private void SelectOutputFileButtonClick(object sender, RoutedEventArgs e) 
        {
            var outputFileDialog = new SaveFileDialog();
            if (outputFileDialog.ShowDialog() == System.Windows.Forms.DialogResult.OK)
            {
                OutputFileTextBox.Text = outputFileDialog.FileName;
            }
        }

        private void RunButtonClick(object sender, RoutedEventArgs e) 
        {
            var confirmationResult = System.Windows.Forms.MessageBox.Show(
                "Generating mock \"" + 
                OutputFileTextBox.Text + 
                "\" from \"" + 
                InputFileTextBox.Text + 
                "\". Proceed?");

            if (confirmationResult == System.Windows.Forms.DialogResult.OK)
            {
                var process = new System.Diagnostics.Process();
                var startInfo = new System.Diagnostics.ProcessStartInfo();
                startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
                startInfo.FileName = "OpenGMocker.exe";
                startInfo.Arguments = InputFileTextBox.Text + " " + OutputFileTextBox.Text;
                process.StartInfo = startInfo;
                process.Start();
                process.WaitForExit();
                switch (process.ExitCode)
                {
                    case OK:
                        System.Windows.Forms.MessageBox.Show("Mock generated successfully.");
                        break;
                    case INVALID_ARGS:
                        System.Windows.Forms.MessageBox.Show("Mock generation failed. Invalid arguments.");
                        break;
                    case FILE_MOCKER_ERR:
                        System.Windows.Forms.MessageBox.Show("Mock generation failed. File mocker error.");
                        break;
                    case CLASS_MOCKER_ERR:
                        System.Windows.Forms.MessageBox.Show("Mock generation failed. Class mocker error.");
                        break;
                    case FUNCTION_MOCKER_ERR:
                        System.Windows.Forms.MessageBox.Show("Mock generation failed. Function mocker error.");
                        break;
                    case UNKNOWN_ERR:
                        System.Windows.Forms.MessageBox.Show("Mock generation failed. Unknown error.");
                        break;
                }

                Close();
            }
        }

        private void CancelButtonClick(object sender, RoutedEventArgs e) 
        {
            Close();
        }
    }
}
