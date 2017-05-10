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
    public partial class MainWindow : Window, INotifyPropertyChanged, IDisposable
    {   
        //Variables for setting up the Kinect to recognise frame data from multiple sources
        private KinectSensor kinect = null;
        private MultiSourceFrameReader reader = null;
        private string text = null;

        //Variables for reading in body data
        private Body[] bodies = null;
        private int bodyIndex = 0;
        private bool bodyTracked = false;

        //Variables for gesture recognition
        private GestureDetector gestureDetector = null;
        private GestureResultView gestureResultView = null;
        private List<GestureDetector> gestureDetectorList = null;

        public MainWindow()
        {
            this.InitializeComponent();
            this.initialiseKinect();
            this.openReaders();
            this.setDetectorList();
            
        }

        public event PropertyChangedEventHandler PropertyChanged;

        public string StatusText
        {
            get
            {
                return this.text;
            }

            private set
            {
                if (this.text != value)
                {
                    this.text = value;
                    this.NotifyPropertyChanged();
                }
            }
        }

        void initialiseKinect()
        {
            this.kinect = KinectSensor.GetDefault();

            if (this.kinect != null)
            {
                this.kinect.Open();
            }
        }

        void setDetectorList()
        {
            this.gestureDetectorList = new List<GestureDetector>();
            GestureResultView result = new GestureResultView(false, false, 0.0f);
            GestureDetector detector = new GestureDetector(this.kinect, result);
            result.PropertyChanged += GestureResult_PropertyChanged;
            this.gestureDetectorList.Add(detector);
        }

        void openReaders()
        {
            this.reader = this.kinect.OpenMultiSourceFrameReader(FrameSourceTypes.Color | FrameSourceTypes.Body);
            this.reader.MultiSourceFrameArrived += Reader_MultiSourceFrameArrived;
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
                    camera.Source = ToBitmap(frame);
                }
            }

            //Body stream
            using (var frame = reference.BodyFrameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    if (this.bodies == null)
                    {
                        this.bodies = new Body[frame.BodyFrameSource.BodyCount];
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

        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }

        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (this.gestureDetector != null)
                {
                    this.gestureDetector.Dispose();
                    this.gestureDetector = null;
                }
            }
        }

        void GestureResult_PropertyChanged(object sender, PropertyChangedEventArgs e)
        {
            
        }

    }
}
