using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Drawing;
using System.Runtime.InteropServices;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace Interface
{
    class Bridge
    {
        #region Import
        
        [DllImport("core.dll")]
        static extern IntPtr Init();

        [DllImport("core.dll")]
        static extern void Free(IntPtr corePtr);

        [DllImport("core.dll")]
        static extern void SetParam(IntPtr corePtr, int id, double value);

        [DllImport("core.dll")]
        static extern void Simulate(IntPtr corePtr);

        [DllImport("core.dll")]
        static extern ulong GetOutputLength(IntPtr corePtr, int id);

        [DllImport("core.dll")]
        static extern double GetOutputX(IntPtr corePtr, int id, ulong index);

        [DllImport("core.dll")]
        static extern double GetOutputY(IntPtr corePtr, int id, ulong index);

        IntPtr corePtr;

        #endregion

        #region Params and outputs

        public class Entry
        {
            public string name;
            public int id;
            public Control control = null;
        }
        public class EntryParam : Entry
        {
            public double defValue;
        }
        public class EntryOutput : Entry
        {
            public Color color;
        }

        List<EntryParam> paramList;
        List<EntryOutput> outputList;
        
        void InitParamList()
        {
            paramList = new List<EntryParam>();

            int i = 0;
            paramList.Add(new EntryParam { name = "T", id = i++, defValue = 1 });// 2.76 });
            paramList.Add(new EntryParam { name = "dt", id = i++, defValue = 0.001  });
            paramList.Add(new EntryParam { name = "x1(0)", id = i++, defValue = 1 });
            paramList.Add(new EntryParam { name = "x2(0)", id = i++, defValue = 1 });
            paramList.Add(new EntryParam { name = "x3(0)", id = i++, defValue = 0 });
            paramList.Add(new EntryParam { name = "x4(0)", id = i++, defValue = 0 });
            paramList.Add(new EntryParam { name = "x5(0)", id = i++, defValue = 0 });
            paramList.Add(new EntryParam { name = "x6(0)", id = i++, defValue = 0 });
            paramList.Add(new EntryParam { name = "x7(0)", id = i++, defValue = 0 });
            paramList.Add(new EntryParam { name = "x8(0)", id = i++, defValue = 0 });
            paramList.Add(new EntryParam { name = "psi1(0)", id = i++, defValue = 0 });// 2.807 });
            paramList.Add(new EntryParam { name = "psi2(0)", id = i++, defValue = 0 });// 0.358 });
            paramList.Add(new EntryParam { name = "psi3(0)", id = i++, defValue = 0 });// 4.349 });
            paramList.Add(new EntryParam { name = "psi4(0)", id = i++, defValue = 0 });// 0.333 });
            paramList.Add(new EntryParam { name = "psi5(0)", id = i++, defValue = 0 });// 1.287 });
            paramList.Add(new EntryParam { name = "psi6(0)", id = i++, defValue = 0 });// -0.838 });
            paramList.Add(new EntryParam { name = "psi7(0)", id = i++, defValue = 0 });// 3.273 });
            paramList.Add(new EntryParam { name = "psi8(0)", id = i++, defValue = 0 });// -0.183 });
            paramList.Add(new EntryParam { name = "Mx", id = i++, defValue = 1 });
            paramList.Add(new EntryParam { name = "My", id = i++, defValue = 1 });
            paramList.Add(new EntryParam { name = "m", id = i++, defValue = 0.741 });
            paramList.Add(new EntryParam { name = "l", id = i++, defValue = 0.3 });
            paramList.Add(new EntryParam { name = "bX", id = i++, defValue = 1 });
            paramList.Add(new EntryParam { name = "bY", id = i++, defValue = 1 });
            paramList.Add(new EntryParam { name = "g", id = i++, defValue = 9.81 });
            paramList.Add(new EntryParam { name = "rho", id = i++, defValue = 100000 });
            paramList.Add(new EntryParam { name = "measId", id = i++, defValue = 1 });
        }
        void InitOutputList()
        {
            outputList = new List<EntryOutput>();

            int i = 0;
            outputList.Add(new EntryOutput { name = "x1", id = i++, color = Color.Green });
            outputList.Add(new EntryOutput { name = "x2", id = i++, color = Color.Red });
            outputList.Add(new EntryOutput { name = "x3", id = i++, color = Color.Purple });
            outputList.Add(new EntryOutput { name = "x4", id = i++, color = Color.Gray });
            outputList.Add(new EntryOutput { name = "x5", id = i++, color = Color.Black });
            outputList.Add(new EntryOutput { name = "x6", id = i++, color = Color.Gold });
            outputList.Add(new EntryOutput { name = "x7", id = i++, color = Color.Brown });
            outputList.Add(new EntryOutput { name = "x8", id = i++, color = Color.Pink });
            outputList.Add(new EntryOutput { name = "psi1", id = i++, color = Color.DarkGreen });
            outputList.Add(new EntryOutput { name = "psi2", id = i++, color = Color.DarkRed });
            outputList.Add(new EntryOutput { name = "psi3", id = i++, color = Color.DarkViolet });
            outputList.Add(new EntryOutput { name = "psi4", id = i++, color = Color.DarkGray });
            outputList.Add(new EntryOutput { name = "psi5", id = i++, color = Color.DarkBlue });
            outputList.Add(new EntryOutput { name = "psi6", id = i++, color = Color.DarkOrange });
            outputList.Add(new EntryOutput { name = "psi7", id = i++, color = Color.DarkSeaGreen });
            outputList.Add(new EntryOutput { name = "psi8", id = i++, color = Color.DarkTurquoise });
            outputList.Add(new EntryOutput { name = "u1", id = i++, color = Color.Blue });
            outputList.Add(new EntryOutput { name = "u2", id = i++, color = Color.Orange });
            outputList.Add(new EntryOutput { name = "meas xM", id = i++, color = Color.Silver });
            outputList.Add(new EntryOutput { name = "meas yM", id = i++, color = Color.DarkMagenta });
            outputList.Add(new EntryOutput { name = "meas betaX", id = i++, color = Color.DarkOliveGreen });
            outputList.Add(new EntryOutput { name = "meas betaY", id = i++, color = Color.DarkKhaki });
        }

        #endregion

        #region Constructor and destructor

        public Bridge()
        {
            corePtr = Init();

            InitParamList();
            InitOutputList();
        }
        ~Bridge()
        {
            Free(corePtr);
        }

        #endregion

        #region Setup controls

        void InsertParamControls(TableLayoutPanel table)
        {
            foreach (EntryParam entry in paramList)
            {
                Label label = new Label();
                label.Text = entry.name;
                label.AutoSize = false;
                label.Dock = DockStyle.Fill;
                label.TextAlign = System.Drawing.ContentAlignment.MiddleRight;
                table.Controls.Add(label);

                NumericUpDown numeric = new NumericUpDown();
                numeric.Dock = DockStyle.Fill;
                numeric.Anchor = AnchorStyles.Left | AnchorStyles.Right;
                numeric.DecimalPlaces = 5;
                numeric.Minimum = -10000000;
                numeric.Maximum = 10000000;
                numeric.Value = (decimal)entry.defValue;
                table.Controls.Add(numeric);
                entry.control = numeric;
            }
        }

        void InsertOutputControls(TableLayoutPanel table)
        {
            foreach (EntryOutput entry in outputList)
            {
                CheckBox checkbox = new CheckBox();
                checkbox.Text = entry.name;
                checkbox.Dock = DockStyle.Fill;
                checkbox.CheckedChanged += Checkbox_CheckedChanged;
                table.Controls.Add(checkbox);
                table.SetColumnSpan(checkbox, 2);
                entry.control = checkbox;
            }
        }

        public void SetUpTable(TableLayoutPanel table)
        {
            //table.CellBorderStyle = TableLayoutPanelCellBorderStyle.Single;
            table.RowCount = paramList.Count + outputList.Count + 1;
            table.Height = table.RowCount * 32;

            InsertParamControls(table);
            InsertOutputControls(table);
            
            foreach (RowStyle row in table.RowStyles)
            {
                row.SizeType = SizeType.Absolute;
                row.Height = 32;
            }
            table.RowStyles[table.RowStyles.Count - 1].SizeType = SizeType.AutoSize;
        }

        #endregion

        #region EventHandlers

        private void Checkbox_CheckedChanged(object sender, EventArgs e)
        {
            DrawOutput();
        }
        public void Simulate()
        {
            int i = 0;
            foreach (EntryParam entry in paramList)
                SetParam(corePtr, i++, (double)((entry.control as NumericUpDown).Value));

            Simulate(corePtr);

            DrawOutput();
        }

        #endregion

        #region Chart handling

        Chart chart;
        public void SetChart(Chart chart)
        {
            this.chart = chart;
        }
        void DrawOutput()
        {
            if (chart == null)
                return;

            chart.Series.Clear();

            foreach (EntryOutput entry in outputList)
            {
                if ((entry.control as CheckBox).Checked)
                {
                    ulong size = GetOutputLength(corePtr, entry.id);

                    Series series = chart.Series.Add(entry.name);
                    series.Color = entry.color;
                    series.ChartType = SeriesChartType.Line;

                    for (ulong index = 0; index < size; ++index)
                        series.Points.AddXY(
                            GetOutputX(corePtr, entry.id, index),
                            GetOutputY(corePtr, entry.id, index));
                }
            }
        }

        #endregion
    }
}
