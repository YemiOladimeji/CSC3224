using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.ComponentModel;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;

namespace CSC3095___Project
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window, INotifyPropertyChanged
    {

        private KinectSensor sensor = null;

        private Body[] bodies = null;

        private string statusText = null;

        private BodyFrameReader bfR = null;

        private List<GestureDetector> gestureDetectorList = null;

        public MainWindow()
        {
            this.sensor = KinectSensor.GetDefault();

            this.sensor.Open();

            this.StatusText = "Waiting for Gesture...";

            this.bfR = this.sensor.BodyFrameSource.OpenReader();

            this.bfR.FrameArrived += this.Reader_BodyFrameArrived;

            this.gestureDetectorList = new List<GestureDetector>();

            this.InitializeComponent();

            int maxBodies = this.sensor.BodyFrameSource.BodyCount;
            for (int i = 0; i < maxBodies; ++i)
            {
                GestureResultView result = new GestureResultView(i, false, false, 0.0f);
                GestureDetector detector = new GestureDetector(this.sensor, result);
                this.gestureDetectorList.Add(detector);
            }
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public string StatusText
        {
            get
            {
                return this.statusText;
            }

            set
            {
                if (this.statusText != value)
                {
                    this.statusText = value;
                    if (this.PropertyChanged != null)
                    {
                        this.PropertyChanged(this, new PropertyChangedEventArgs("Status Text"));
                    }
                }
            }
        }

        private void MainWindow_Closing(object sender, CancelEventArgs e)
        {
            if (this.bfR != null)
            {
                this.bfR.FrameArrived -= Reader_BodyFrameArrived;
                this.bfR.Dispose();
                this.bfR = null;
            }

            if (this.gestureDetectorList != null)
            {
                foreach (GestureDetector detector in this.gestureDetectorList)
                {
                    detector.Dispose();
                }

                this.gestureDetectorList.Clear();
                this.gestureDetectorList = null;
            }

            if (this.sensor != null)
            {
                this.sensor.IsAvailableChanged -= this.Sensor_IsAvailableChanged;
                this.sensor.Close();
                this.sensor = null;
            }
        }

        private void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            this.StatusText = "No Sensor Detected...";
        }

        private void Reader_BodyFrameArrived(object sender, BodyFrameArrivedEventArgs e)
        {
            bool dataRecieved = false;

            using (BodyFrame bodyFrame = e.FrameReference.AcquireFrame())
            {
                if (bodyFrame != null)
                {
                    if (this.bodies == null)
                    {
                        this.bodies = new Body[bodyFrame.BodyCount];
                    }

                    bodyFrame.GetAndRefreshBodyData(this.bodies);
                    dataRecieved = true;
                }
            }

            if (dataRecieved)
            {
                if (this.bodies != null)
                {
                    int maxBodies = this.sensor.BodyFrameSource.BodyCount;
                    for (int i = 0; i< maxBodies; ++i)
                    {
                        Body body = this.bodies[i];
                        ulong trackingID = body.TrackingId;

                        if (trackingID != this.gestureDetectorList[i].TrackingId)
                        {
                            this.gestureDetectorList[i].TrackingId = trackingID;
                            this.gestureDetectorList[i].IsPaused = trackingID == 0;
                        }
                    }
                }
            }
        }


    }
}
