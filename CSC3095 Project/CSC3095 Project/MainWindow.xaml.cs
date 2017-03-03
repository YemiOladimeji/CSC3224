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
        private KinectSensor kinect;
        private MultiSourceFrameReader reader;
        private Gesture waveGesture;
        private VisualGestureBuilderFrameSource gestureSource;
        private VisualGestureBuilderFrameReader gestureReader;

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
            kinect = KinectSensor.GetDefault();
            //cM = kinect.CoordinateMapper;

            if (kinect != null)
            {
                kinect.Open();
            }
        }

        void loadGesture()
        {
            VisualGestureBuilderDatabase db = new VisualGestureBuilderDatabase(@"W4ve.gbd");
            this.waveGesture = db.AvailableGestures.Where(g => g.Name == "W4ve").Single();
        }

        void openReaders()
        {
            reader = kinect.OpenMultiSourceFrameReader(FrameSourceTypes.Color);
            reader.MultiSourceFrameArrived += Reader_MultiSourceFrameArrived;
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
            var reference = e.FrameReference.AcquireFrame();

            //Colour stream
            using (var frame = reference.ColorFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    Camera.Source = ToBitmap(frame);
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
