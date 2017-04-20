using Microsoft.Kinect;
using Microsoft.Kinect.Wpf.Controls;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Runtime.CompilerServices;
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

namespace CSC3095_Project
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : NavigationWindow, INotifyPropertyChanged
    {

        private KinectSensor sensor = null;
        private Body[] bodies = null;
        private string statusText = null;

        private BodyFrameReader bfR = null;
        private ColorFrameReader cFR = null;
        private List<GestureDetector> gestureDetectorList = null;

        public MainWindow()
        {
            this.sensor = KinectSensor.GetDefault();
            this.sensor.Open();
            this.StatusText = "Waiting for Gesture...";
            this.bfR = this.sensor.BodyFrameSource.OpenReader();
            this.cFR = this.sensor.ColorFrameSource.OpenReader();
            this.bfR.FrameArrived += this.Reader_BodyFrameArrived;
            this.cFR.FrameArrived += this.Reader_ColorFrameArrived;
            this.gestureDetectorList = new List<GestureDetector>();
            this.InitializeComponent();

            //this.DataContext = this;

            int maxBodies = this.sensor.BodyFrameSource.BodyCount;
            for (int i = 0; i < maxBodies; ++i)
            {
                GestureResultView result = new GestureResultView(i, false, false, 0.0f, 0);
                GestureDetector detector = new GestureDetector(this.sensor, result);
                this.gestureDetectorList.Add(detector);

                ContentControl contentControl = new ContentControl();
                contentControl.Content = this.gestureDetectorList[i].GestureResultView;
                Grid.SetColumn(contentControl, 0);
                Grid.SetRow(contentControl, 0);
                //this.contentGrid.Children.Add(contentControl);          
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
                    this.PropertyChanged?.Invoke(this, new PropertyChangedEventArgs("Status Text"));
                }
            }
        }

        private void Sensor_IsAvailableChanged(object sender, IsAvailableChangedEventArgs e)
        {
            this.StatusText = "No Sensor Detected...";
        }

        private void Reader_ColorFrameArrived(object sender, ColorFrameArrivedEventArgs e)
        {
            using (ColorFrame colorFrame = e.FrameReference.AcquireFrame())
            {
                if (colorFrame != null)
                {
                    //camera.Source = ToBitmap(colorFrame);
                }
            }
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
                    for (int i = 0; i < maxBodies; ++i)
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

        //Taking the colour frames from the Kinect and turning them into bitmaps 
        private ImageSource ToBitmap(ColorFrame frame)
        {
            int width = frame.FrameDescription.Width;
            int height = frame.FrameDescription.Height;
            var format = PixelFormats.Bgr32;

            byte[] pixels = new byte[width * height * ((PixelFormats.Bgr32.BitsPerPixel + 7) / 8)];

            if (frame.RawColorImageFormat == ColorImageFormat.Bgra)
            {
                frame.CopyRawFrameDataToArray(pixels);
            }
            else
            {
                frame.CopyConvertedFrameDataToArray(pixels, ColorImageFormat.Bgra);
            }

            int stride = width * format.BitsPerPixel / 8;

            return BitmapSource.Create(width, height, 96, 96, format, null, pixels, stride);
        }

        private void NotifyPropertyChanged([CallerMemberName] string propertyName = "")
        {
            this.PropertyChanged(this, new PropertyChangedEventArgs(propertyName));
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

    }
}
