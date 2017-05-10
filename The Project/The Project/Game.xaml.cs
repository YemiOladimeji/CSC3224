using System;
using System.Collections.Generic;
using Microsoft.Kinect;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.ComponentModel;

namespace The_Project
{
    /// <summary>
    /// Interaction logic for Game.xaml
    /// </summary>
    public partial class Game : Window
    {
        private KinectSensor sensor = null;
        private Body[] bodies = null;

        private BodyFrameReader bfR = null;
        private ColorFrameReader cFR = null;
        private List<GestureDetector> gestureDetectorList = null;

        public Game()
        {
            InitializeComponent();
            this.sensor = KinectSensor.GetDefault();
            this.sensor.Open();

            this.bfR = this.sensor.BodyFrameSource.OpenReader();
            this.cFR = this.sensor.ColorFrameSource.OpenReader();

            this.cFR.FrameArrived += this.Reader_ColorFrameArrived;
            this.bfR.FrameArrived += this.Reader_BodyFrameArrived;

            this.gestureDetectorList = new List<GestureDetector>();

            int maxBodies = this.sensor.BodyFrameSource.BodyCount;
            for (int i = 0; i < maxBodies; ++i)
            {
                GestureResultView result = new GestureResultView(i, false, false, 0.0f, 0);
                GestureDetector detector = new GestureDetector(this.sensor, result);
                this.gestureDetectorList.Add(detector);

                ContentControl contentControl = new ContentControl();
                contentControl.Content = this.gestureDetectorList[i].GestureResultView;
                this.contentCanvas.Children.Add(contentControl);          
            }
        }

        private void Reader_ColorFrameArrived(object sender, ColorFrameArrivedEventArgs e)
        {
            using (ColorFrame colorFrame = e.FrameReference.AcquireFrame())
            {
                if (colorFrame != null)
                {
                    cam.Source = ToBitmap(colorFrame);
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
    
        //Function to take in colour frames from the Kinect and display them 
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

        //Function to execute shutdown tasks.
        private void Game_Closing(object sender, CancelEventArgs e)
        {
            if (this.bfR != null)
            {
                //BodyFrameReader is IDisposable.
                this.bfR.FrameArrived -= this.Reader_BodyFrameArrived;
                this.bfR.Dispose();
                this.bfR = null;
            }

            if (this.gestureDetectorList != null)
            {
                //The GestureDetector contains disposable members(VisualGestureBuilderFrameSource and VisualGestureBuilderFrameReader).
                foreach (GestureDetector detector in this.gestureDetectorList)
                {
                    detector.Dispose();
                }

                this.gestureDetectorList.Clear();
                this.gestureDetectorList = null;
            }

            if (this.sensor != null)
            {
                this.sensor.Close();
                this.sensor = null;
            }
        }
    }
}
