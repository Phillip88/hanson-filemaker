/* -------------------------------------------------------------------------------------------------
This file is part of the Nbbf Copy Protection Library (Nbbf)
 
Nbbf is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
 
Nbbf is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU Lesser Public License for more details.
 
You should have received a copy of the GNU Lesser Public License
along with Nbbf.  If not, see <http://www.gnu.org/licenses/>.
------------------------------------------------------------------------------------------------- */
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Text;
using System.Windows.Forms;
using Test.Properties;
using NbbfCLib;
using NbbfVLib;

namespace Test
{
    public partial class Main : Form
    {
        //------------------------------------------------------------------------------------------
        // A long in C++ is 4 bytes, while in C# it is 8 bytes.  Since the DLL export record
        // contains the number of bytes required for parameters passed, if we don't match up this
        // number exactly the function will not be found by the Interop assembly.
        //
        // Note that the NbbfM DLL and PDB are copied into this directory by the build process for
        // that project as a post build step.
        //------------------------------------------------------------------------------------------
        [DllImport("NbbfM.dll")]
        static extern bool InstallDirect(
            [MarshalAs(UnmanagedType.LPStr)] string lpstrKey,
            int lID1, 
            int lID2);

        //------------------------------------------------------------------------------------------
        // The following are constants that reference the string table.
        //------------------------------------------------------------------------------------------
        private const string STR_VALIDATESUCCESS = "strValidateSuccess";
        private const string STR_VALIDATEFAILURE = "strValidateFailure";
        private const string STR_INSTALLSUCCESS = "strInstallSuccess";
        private const string STR_INSTALLFAILURE = "strInstallFailure";

        //------------------------------------------------------------------------------------------
        // The following are miscellaneous constants.
        //------------------------------------------------------------------------------------------
        private const int CAPS_VALUE = 255;
        private const int LEN_KEYPART = 5;
        private const int MSECS_STATUS = 2000;
        private const int MSECS_STATUSUNUSED = 1;

        public Main()
        {
            InitializeComponent();

            UpdateGUI();
        }

        private void cmdCreate_Click(object sender, EventArgs e)
        {
            //--------------------------------------------------------------------------------------
            // Create a new registration key and update the GUI to display it.
            //--------------------------------------------------------------------------------------
            int iManu;
            int iProd;
            Create objCreate;
            string strKey;

            iManu = int.Parse(txtManufacturer.Text);
            iProd = int.Parse(txtProduct.Text);

            objCreate = new Create();
            strKey = objCreate.Create(iManu, iProd, CAPS_VALUE);
            objCreate = null;

            //--------------------------------------------------------------------------------------
            // Each of the textboxes have their "key part index" set in their Tag property.  We
            // need to convert the Tag (of type System.Object) to a string and use that as an
            // argument to the int.Parse method.  The result is converted to the starting index
            // within the complete key that should be stored in the textbox.
            //--------------------------------------------------------------------------------------
            txtKey1.Text = strKey.Substring(int.Parse(txtKey1.Tag.ToString()) * LEN_KEYPART, LEN_KEYPART);
            txtKey2.Text = strKey.Substring(int.Parse(txtKey2.Tag.ToString()) * LEN_KEYPART, LEN_KEYPART);
            txtKey3.Text = strKey.Substring(int.Parse(txtKey3.Tag.ToString()) * LEN_KEYPART, LEN_KEYPART);
            txtKey4.Text = strKey.Substring(int.Parse(txtKey4.Tag.ToString()) * LEN_KEYPART, LEN_KEYPART);
            txtKey5.Text = strKey.Substring(int.Parse(txtKey5.Tag.ToString()) * LEN_KEYPART, LEN_KEYPART);
        }

        private void cmdInstall_Click(object sender, EventArgs e)
        {
            //--------------------------------------------------------------------------------------
            // Install the key and display the result in the status bar.
            //--------------------------------------------------------------------------------------
            int iManu;
            int iProd;
            string strKey;

            iManu = int.Parse(txtManufacturer.Text);
            iProd = int.Parse(txtProduct.Text);

            strKey = txtKey1.Text + txtKey2.Text + txtKey3.Text + txtKey4.Text + txtKey5.Text;

            if (InstallDirect(strKey, iManu, iProd))
                SetStatusText(STR_INSTALLSUCCESS);
            else
                SetStatusText(STR_INSTALLFAILURE);
        }

        private void cmdValidate_Click(object sender, EventArgs e)
        {
            //--------------------------------------------------------------------------------------
            // Check to see that a valid key has been installed for the manufacturer and product
            // IDs specified.  If, for some reason, the key cannot be properly decoded a
            // COMException will be thrown.  We're catching all exceptions, however, and treating
            // them as a failure to validate.
            //--------------------------------------------------------------------------------------
            int iManu;
            int iProd;
            Validate objValidate;
            int iElapsed;
            bool bReturn;

            iManu = int.Parse(txtManufacturer.Text);
            iProd = int.Parse(txtProduct.Text);

            try
            {
                objValidate = new Validate();
                bReturn = objValidate.Validate(iManu, iProd, CAPS_VALUE);
                iElapsed = objValidate.Elapsed(iManu, iProd);
                objValidate = null;
            }
            catch (Exception objXcpt)
            {
                bReturn = false;
            }

            if (bReturn)
                SetStatusText(STR_VALIDATESUCCESS);
            else
                SetStatusText(STR_VALIDATEFAILURE);
        }

        //------------------------------------------------------------------------------------------
        // The various _TextChanged events are captured simply to update the availability of the
        // command buttons.
        //------------------------------------------------------------------------------------------
        private void txtManufacturer_TextChanged(object sender, EventArgs e)
        {
            UpdateGUI();
        }

        private void txtProduct_TextChanged(object sender, EventArgs e)
        {
            UpdateGUI();
        }

        private void txtKey1_TextChanged(object sender, EventArgs e)
        {
            UpdateGUI();
        }

        private void txtKey2_TextChanged(object sender, EventArgs e)
        {
            UpdateGUI();
        }

        private void txtKey3_TextChanged(object sender, EventArgs e)
        {
            UpdateGUI();
        }

        private void txtKey4_TextChanged(object sender, EventArgs e)
        {
            UpdateGUI();
        }

        private void txtKey5_TextChanged(object sender, EventArgs e)
        {
            UpdateGUI();
        }

        private void tmrStatus_Tick(object sender, EventArgs e)
        {
            //--------------------------------------------------------------------------------------
            // When the timer fires the tick event, it is time to clear the status text.  Disable
            // the timer to avoid having unnecessary firings of this event.
            //--------------------------------------------------------------------------------------
            tssStatus.Text = string.Empty;
            tmrStatus.Enabled = false;
            tmrStatus.Interval = MSECS_STATUSUNUSED;
        }

        private void UpdateGUI()
        {
            //--------------------------------------------------------------------------------------
            // Update the availability of the command buttons based on the contents of the 
            // textboxes.
            //--------------------------------------------------------------------------------------
            bool bCreateValidate;
            bool bInstall;
            int iValue;

            bCreateValidate = true;
            bInstall = true;

            if (!int.TryParse(txtManufacturer.Text, out iValue))
                bCreateValidate = false;

            if (!int.TryParse(txtProduct.Text, out iValue))
                bCreateValidate = false;

            if (txtKey1.Text.Length != LEN_KEYPART)
                bInstall = false;

            if (txtKey2.Text.Length != LEN_KEYPART)
                bInstall = false;

            if (txtKey3.Text.Length != LEN_KEYPART)
                bInstall = false;

            if (txtKey4.Text.Length != LEN_KEYPART)
                bInstall = false;

            if (txtKey5.Text.Length != LEN_KEYPART)
                bInstall = false;

            cmdCreate.Enabled = bCreateValidate;
            cmdValidate.Enabled = bCreateValidate;
            cmdInstall.Enabled = bCreateValidate && bInstall;
        }

        private void SetStatusText(string strResource)
        {
            //--------------------------------------------------------------------------------------
            // Set the status text from the string resource table.  Then set the timer interval and 
            // enable the timer.  When the Tick event is fired, the text will be cleared.
            //--------------------------------------------------------------------------------------
            tssStatus.Text = Resources.ResourceManager.GetString(strResource);
            tmrStatus.Interval = MSECS_STATUS;
            tmrStatus.Enabled = true;
        }
    }
}
