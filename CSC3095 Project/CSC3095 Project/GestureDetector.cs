using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;

namespace CSC3095_Project
{
    public class GestureDetector : IDisposable
    {
        //Variable accessing the VGB-built database where gestures are stored
        private readonly string gestureDatabase = @"W4ve.gbd";

        //Name of the waving gesture in the database
        private readonly string waveName = "W4ve";

        //Source of the gesture frames which will be tied to a tracked body's ID
        private VisualGestureBuilderFrameSource vgbFrameSource = null;

        //The gesture frame reader will handle all incoming gesture events from the sensor
        private VisualGestureBuilderFrameReader vgbFrameReader = null;

        public GestureResultView GestureResultView { get; private set; }

        public GestureDetector(KinectSensor kN, GestureResultView gRV)
        {
            if (kN == null)
            {
                throw new ArgumentNullException("kN");
            }
            if (gRV == null)
            {
                throw new ArgumentNullException("gRV");
            }

            this.GestureResultView = gRV;

            this.vgbFrameSource = new VisualGestureBuilderFrameSource(kN, 0);
            this.vgbFrameSource.TrackingIdLost += this.Source_TrackingIdLost;

            this.vgbFrameReader = this.vgbFrameSource.OpenReader();
            if (this.vgbFrameReader != null)
            {
                this.vgbFrameReader.IsPaused = true;
                this.vgbFrameReader.FrameArrived += this.Reader_GestureFrameArrived;
            }

            using (VisualGestureBuilderDatabase dB = new VisualGestureBuilderDatabase(this.gestureDatabase))
            {
                foreach (Gesture gesture in dB.AvailableGestures)
                {
                    if (gesture.Name.Equals(this.waveName))
                    {
                        this.vgbFrameSource.AddGesture(gesture);
                    }
                }
            }
        }

        public ulong TrackingId
        {
            get
            {
                return this.vgbFrameSource.TrackingId;
            }

            set
            {
                if (this.vgbFrameSource.TrackingId != value)
                {
                    this.vgbFrameSource.TrackingId = value;
                }
            }
        }

        public bool IsPaused
        {
            get
            {
                return this.vgbFrameReader.IsPaused;
            }

            set
            {
                if (this.vgbFrameReader.IsPaused != value)
                {
                    this.vgbFrameReader.IsPaused = value;
                }
            }
        }

        private void Source_TrackingIdLost(object sender, TrackingIdLostEventArgs e)
        {
            this.GestureResultView.UpdateGestureResult(false, false, 0.0f);
        }


        protected virtual void Dispose(bool disposing)
        {
            if (disposing)
            {
                if (this.vgbFrameReader != null)
                {
                    this.vgbFrameReader.FrameArrived -= this.Reader_GestureFrameArrived;
                    this.vgbFrameReader.Dispose();
                    this.vgbFrameReader = null;
                }

                if (this.vgbFrameSource != null)
                {
                    this.vgbFrameSource.TrackingIdLost -= this.Source_TrackingIdLost;
                    this.vgbFrameSource.Dispose();
                    this.vgbFrameSource = null;
                }
            }
        }


        private void Reader_GestureFrameArrived(object sender, VisualGestureBuilderFrameArrivedEventArgs e)
        {
            VisualGestureBuilderFrameReference frameReference = e.FrameReference;
            using (VisualGestureBuilderFrame frame = frameReference.AcquireFrame())
            {
                if (frame != null)
                {
                    //Get the gesture results from the last frame
                    IReadOnlyDictionary<Gesture, DiscreteGestureResult> discreteResults = frame.DiscreteGestureResults;

                    if (discreteResults != null)
                    {
                        foreach (Gesture gesture in this.vgbFrameSource.Gestures)
                        {
                            if (gesture.Name.Equals(this.waveName) && gesture.GestureType == GestureType.Discrete)
                            {
                                DiscreteGestureResult result = null;
                                discreteResults.TryGetValue(gesture, out result);

                                if (result != null && result.Confidence > 0.8) //Limit the amount of results which are reported back, by setting a minimum confidence level
                                {
                                    if (result.Confidence == 1)
                                    {
                                        this.GestureResultView.GestureCount++;
                                    }
                                    this.GestureResultView.UpdateGestureResult(true, result.Detected, result.Confidence); //Report back the updated gesture result                                 
                                }
                            }
                        }
                    }
                }
            }
        }

        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
        }
    }
}
