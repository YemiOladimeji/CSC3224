using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;
using Microsoft.Kinect.Wpf.Controls;
using System;
using System.Collections.Generic;
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
    public partial class MainWindow : Window
    {
        private KinectSensor kinect = null;
        private MultiSourceFrameReader reader;
        private Gesture waveGesture;
        private VisualGestureBuilderFrameSource gestureSource;
        private VisualGestureBuilderFrameReader gestureReader;

        //Variables for reading in body data
       // private BodyFrameReader bodyFrameReader = null;
        private Body[] bodies = null;
        private int bodyIndex;
        private bool bodyTracked = false;

        public MainWindow()
        {
            InitializeComponent();
            initialiseKinect();
            openReaders();
            loadGesture();
            openGestureReader();
        }

        void initialiseKinect()
        {
            this.kinect = KinectSensor.GetDefault();

            if (this.kinect != null)
            {
                this.kinect.Open();
            }
        }

        void openReaders()
        {
            this.reader = this.kinect.OpenMultiSourceFrameReader(FrameSourceTypes.Color | FrameSourceTypes.Body);
            this.reader.MultiSourceFrameArrived += Reader_MultiSourceFrameArrived;
            //this.bodyFrameReader = this.kinect.BodyFrameSource.OpenReader();
        }

        void loadGesture()
        {
            VisualGestureBuilderDatabase db = new VisualGestureBuilderDatabase(@"W4ve.gbd");
            this.waveGesture = db.AvailableGestures.Where(g => g.Name == "W4ve").Single();
        }

        void openGestureReader()
        {
            this.gestureSource = new VisualGestureBuilderFrameSource(this.kinect, 0);
            this.gestureSource.AddGesture(this.waveGesture);
            this.gestureSource.TrackingIdLost += OnTrackingIdLost;

            this.gestureReader = this.gestureSource.OpenReader();
            this.gestureReader.IsPaused = true;
            this.gestureReader.FrameArrived += OnGestureFrameArrived;
        }

        void OnCloseReaders(object sender, RoutedEventArgs e)
        {
            if (this.gestureReader != null)
            {
                this.gestureReader.FrameArrived -= this.OnGestureFrameArrived;
                this.gestureReader.Dispose();
                this.gestureReader = null; 
            }
            if (this.gestureSource != null)
            {
                this.gestureSource.TrackingIdLost -= this.OnTrackingIdLost;
                this.gestureSource.Dispose();
            }
        }

        void OnTrackingIdLost(object sender, TrackingIdLostEventArgs e)
        {
            this.gestureReader.IsPaused = true;
            this.detectBlock.Text = "There's no-one here...";
        }

        void OnGestureFrameArrived(object sender, VisualGestureBuilderFrameArrivedEventArgs e)
        {
            using (var frame = e.FrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    var continuousResults = frame.ContinuousGestureResults;
                    if ((continuousResults != null) && (continuousResults.ContainsKey(this.waveGesture)))
                    {
                        var result = continuousResults[this.waveGesture];

                        this.detectBlock.Text = "You are waving!";
                    }
                }
            }
        }

        void Reader_MultiSourceFrameArrived(object sender, MultiSourceFrameArrivedEventArgs e)
        {
            bool dataReceived = false;
            var reference = e.FrameReference.AcquireFrame();

            //Colour stream
            using (var frame = reference.ColorFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    Camera.Source = ToBitmap(frame);
                }
            }

            //Body stream
            using (var frame = reference.BodyFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    if (this.bodies == null)
                    {
                        this.bodies = new Body[frame.BodyCount];
                    }
                    frame.GetAndRefreshBodyData(this.bodies);
                    dataReceived = true;
                }
            }

            if (dataReceived)
            {
                Body body = null;
                if (this.bodyTracked)
                {
                    if (this.bodies[this.bodyIndex].IsTracked)
                    {
                        body = this.bodies[this.bodyIndex];
                    } else
                    {
                        bodyTracked = false;
                    }
                }
                if (!bodyTracked)
                {
                    for (int i = 0; i < bodies.Length; ++i)
                    {
                        if (this.bodies[i].IsTracked)
                        {
                            this.bodyIndex = i;
                            this.bodyTracked = true;
                            break;
                        }
                    }
                }
                if (body != null && this.bodyTracked && body.IsTracked)
                {
                    this.detectBlock.Text = "I have noticed you!";
                } else
                {
                    this.detectBlock.Text = "I can't see you...";
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
    }
}
