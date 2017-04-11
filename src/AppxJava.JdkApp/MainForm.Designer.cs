namespace AppxJava.JdkApp
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.Windows.Forms.Label label1;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.tableLayoutPanel1 = new System.Windows.Forms.TableLayoutPanel();
            this.mAboutLink = new Microsoft.WindowsAPICodePack.Controls.WindowsForms.CommandLink();
            this.mRunJdkToolButton = new Microsoft.WindowsAPICodePack.Controls.WindowsForms.CommandLink();
            this.mLaunchJavaButton = new Microsoft.WindowsAPICodePack.Controls.WindowsForms.CommandLink();
            label1 = new System.Windows.Forms.Label();
            this.tableLayoutPanel1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label1
            // 
            resources.ApplyResources(label1, "label1");
            this.tableLayoutPanel1.SetColumnSpan(label1, 3);
            label1.ForeColor = System.Drawing.SystemColors.GrayText;
            label1.Name = "label1";
            // 
            // tableLayoutPanel1
            // 
            resources.ApplyResources(this.tableLayoutPanel1, "tableLayoutPanel1");
            this.tableLayoutPanel1.Controls.Add(label1, 0, 0);
            this.tableLayoutPanel1.Controls.Add(this.mAboutLink, 1, 3);
            this.tableLayoutPanel1.Controls.Add(this.mRunJdkToolButton, 1, 1);
            this.tableLayoutPanel1.Controls.Add(this.mLaunchJavaButton, 1, 2);
            this.tableLayoutPanel1.Name = "tableLayoutPanel1";
            // 
            // mAboutLink
            // 
            resources.ApplyResources(this.mAboutLink, "mAboutLink");
            this.mAboutLink.Name = "mAboutLink";
            this.mAboutLink.NoteText = "View version, copyright, and license information.";
            this.mAboutLink.UseVisualStyleBackColor = true;
            // 
            // mRunJdkToolButton
            // 
            resources.ApplyResources(this.mRunJdkToolButton, "mRunJdkToolButton");
            this.mRunJdkToolButton.Name = "mRunJdkToolButton";
            this.mRunJdkToolButton.NoteText = "Run the Java compiler, JAR archiver, and other developer\'s tools.";
            this.mRunJdkToolButton.UseVisualStyleBackColor = true;
            // 
            // mLaunchJavaButton
            // 
            resources.ApplyResources(this.mLaunchJavaButton, "mLaunchJavaButton");
            this.mLaunchJavaButton.Name = "mLaunchJavaButton";
            this.mLaunchJavaButton.NoteText = "Run a JAR file or a loose class. Specify the classpath, command-line arguments, a" +
    "nd other options.";
            this.mLaunchJavaButton.UseVisualStyleBackColor = true;
            // 
            // MainForm
            // 
            resources.ApplyResources(this, "$this");
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.SystemColors.Window;
            this.Controls.Add(this.tableLayoutPanel1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "MainForm";
            this.tableLayoutPanel1.ResumeLayout(false);
            this.tableLayoutPanel1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TableLayoutPanel tableLayoutPanel1;
        private Microsoft.WindowsAPICodePack.Controls.WindowsForms.CommandLink mRunJdkToolButton;
        private Microsoft.WindowsAPICodePack.Controls.WindowsForms.CommandLink mAboutLink;
        private Microsoft.WindowsAPICodePack.Controls.WindowsForms.CommandLink mLaunchJavaButton;
    }
}

