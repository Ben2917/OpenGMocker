using System.Diagnostics.CodeAnalysis;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Forms;

namespace OpenGMockerExtension
{
    /// <summary>
    /// Interaction logic for OpenGMockerToolControl.
    /// </summary>
    public partial class OpenGMockerToolControl : System.Windows.Controls.UserControl
    {
        private const int OK = 0;
        private const int INVALID_ARGS = 1;
        private const int FILE_MOCKER_ERR = 2;
        private const int CLASS_MOCKER_ERR = 3;
        private const int FUNCTION_MOCKER_ERR = 4;
        private const int INVALID_ARG_ERR = 5;

        private const int UNKNOWN_ERR = 100;


        /// <summary>
        /// Initializes a new instance of the <see cref="OpenGMockerToolControl"/> class.
        /// </summary>
        public OpenGMockerToolControl()
        {
            this.InitializeComponent();
        }

        private void SelectInputFileButtonClick(object sender, RoutedEventArgs e)
        {
            // TODO: Replace input file dialog with drop down box of files currently open in the editor
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
        private string WrapInQuotes(string input)
        {
            return "\"" + input + "\"";
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
                string path = System.Reflection.Assembly.GetExecutingAssembly().Location;
                string exePath = path.Replace("OpenGMockerExtension.dll", "OpenGMocker.exe");

                var process = new System.Diagnostics.Process();
                var startInfo = new System.Diagnostics.ProcessStartInfo();
                startInfo.WindowStyle = System.Diagnostics.ProcessWindowStyle.Hidden;
                startInfo.FileName = exePath;
                startInfo.Arguments = WrapInQuotes(InputFileTextBox.Text) + " " + WrapInQuotes(OutputFileTextBox.Text);
                process.StartInfo = startInfo;
                process.Start();
                process.WaitForExit();

                // TODO: Replace message boxes with output box in the command window on the UI
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
            }
        }
    }
}