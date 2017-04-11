using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using Microsoft.WindowsAPICodePack.Dialogs;
using Windows.ApplicationModel;
using AppxJava.JdkApp.Resources;

namespace AppxJava.JdkApp
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            
            EnsureCorrectAppRuntime();
            Application.Run(new MainForm());
        }

        static void EnsureCorrectAppRuntime()
        {
            // TODO: Change this value when preparing to deploy to the Windows Store.
            const string expectedPFN = "AppxJava.Jdk_6888pk7g27h36";
            string actualPFN = null;

            try
            {
                // If this method throws an exception, then we are not running in a Store package.
                actualPFN = Package.Current.Id.FamilyName;
            }
            catch
            {
                TaskDialog td = new TaskDialog();
                td.Cancelable = true;
                td.Caption = DRMStrings.AppTitle;
                td.InstructionText = DRMStrings.NoPFNErrorInstruction;
                td.Text = DRMStrings.PFNErrorText;
                td.StandardButtons = TaskDialogStandardButtons.Close;
                td.Icon = TaskDialogStandardIcon.Error;

                td.Show();
                Environment.Exit(-1);
            }

            if (actualPFN != expectedPFN)
            {
                TaskDialog td = new TaskDialog();
                td.Cancelable = true;
                td.Caption = DRMStrings.AppTitle;
                td.InstructionText = DRMStrings.WrongPFNErrorInstruction;
                td.Text = DRMStrings.PFNErrorText;
                td.StandardButtons = TaskDialogStandardButtons.Close;
                td.Icon = TaskDialogStandardIcon.Error;

                td.Show();
                Environment.Exit(-1);
            }
        }
    }
}
