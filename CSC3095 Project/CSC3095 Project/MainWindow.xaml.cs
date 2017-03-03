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
        //private CoordinateMapper cM = null; //Coordinate mapper to map one type of point to another
        private BodyFrameReader bFR = null;
        private IList<Body> bodies = null; //Array for the bodies
        //private List<Tuple<JointType, JointType>> bones; //Definition of bones
        private Gesture waveGesture;
        private VisualGestureBuilderFrameSource gestureSource;
        private VisualGestureBuilderFrameReader gestureReader;

        public MainWindow()
        {
            InitializeComponent();
            initialiseKinect();
            openReaders();
            loadGesture();
            openBodyReader();
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
            reader = kinect.OpenMultiSourceFrameReader(FrameSourceTypes.Color | FrameSourceTypes.Body);
            reader.MultiSourceFrameArrived += Reader_MultiSourceFrameArrived;
        }
        
        void openBodyReader()
        {
            if (this.bodies == null)
            {
                this.bodies = new Body[this.kinect.BodyFrameSource.BodyCount];
            }
            this.bFR = this.kinect.BodyFrameSource.OpenReader();
            this.bFR.FrameArrived += OnBodyFrameArrived;
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
            this.bFR.Dispose();
            this.bFR = null;
        }

        void OnTrackingIdLost(object sender, TrackingIdLostEventArgs e)
        {
            this.gestureReader.IsPaused = true;
            this.detectBlock.Text = "There's no-one here...";
        }

        void OnBodyFrameArrived(object sender, BodyFrameArrivedEventArgs e)
        {
            using (var frame = e.FrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    frame.GetAndRefreshBodyData(this.bodies);

                    var trackedBody = this.bodies.Where(b => b.IsTracked).FirstOrDefault();

                    if (trackedBody != null)
                    {
                        if (this.gestureReader.IsPaused)
                        {
                            this.gestureSource.TrackingId = trackedBody.TrackingId;
                            this.gestureReader.IsPaused = false;
                        }
                    } else
                    {
                        this.OnTrackingIdLost(null,null);
                    }

                }
            }
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

            //Body stream
            /*using (var frame = reference.BodyFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    bodies = new Body[frame.BodyFrameSource.BodyCount];

                    frame.GetAndRefreshBodyData(bodies);

                    foreach (var body in bodies)
                    {
                        if (body != null)
                        {
                            if (body.IsTracked)
                            {
                                Joint handRight = body.Joints[JointType.HandRight];
                                Joint thumbRight = body.Joints[JointType.ThumbRight];
                                Joint handLeft = body.Joints[JointType.HandLeft];
                                Joint thumbLeft = body.Joints[JointType.ThumbLeft];

                                canvas.DrawPoint(handRight);
                                canvas.DrawPoint(handLeft);
                                canvas.DrawPoint(thumbRight);
                                canvas.DrawPoint(thumbLeft);

                                // Find the hand states
                                string rightHandState = "-";
                                string leftHandState = "-";

                                switch (body.HandRightState)
                                {
                                    case HandState.Open:
                                        rightHandState = "Open";
                                        break;
                                    case HandState.Closed:
                                        rightHandState = "Closed";
                                        break;
                                    case HandState.Lasso:
                                        rightHandState = "Lasso";
                                        break;
                                    case HandState.Unknown:
                                        rightHandState = "Unknown...";
                                        break;
                                    case HandState.NotTracked:
                                        rightHandState = "Not tracked";
                                        break;
                                    default:
                                        break;
                                }

                                switch (body.HandLeftState)
                                {
                                    case HandState.Open:
                                        leftHandState = "Open";
                                        break;
                                    case HandState.Closed:
                                        leftHandState = "Closed";
                                        break;
                                    case HandState.Lasso:
                                        leftHandState = "Lasso";
                                        break;
                                    case HandState.Unknown:
                                        leftHandState = "Unknown...";
                                        break;
                                    case HandState.NotTracked:
                                        leftHandState = "Not tracked";
                                        break;
                                    default:
                                        break;
                                }
                                txtBlock.Text = rightHandState;
                                txtBlock.Text = leftHandState;
                                handCheck(handLeft, handRight);
                            }
                        }
                    }
                }
            }*/
        }

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
