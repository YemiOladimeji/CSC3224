using System;
using System.Collections.Generic;
using Microsoft.Kinect;
using Microsoft.Kinect.VisualGestureBuilder;

namespace CSC3095___Project
{
    class GestureDetector : IDisposable
    {
        //Filepath to the VGB trained gesture database
        private readonly string gestureDatabase = @"W4ve.gbd";

        //Namec corresponding to the discrete gesture in the database we want to track
        private readonly string waveGestureName = "W4ve";

        //Gesture frame source
        private VisualGestureBuilderFrameSource vgbFrameSource = null;

        //Gesture frame reader
        private VisualGestureBuilderFrameReader vgbFrameReader = null;

        public GestureResultView GestureResultView { get; private set; }

        public GestureDetector(KinectSensor sensor, GestureResultView gestureResultView)
        {
            if (sensor == null)
            {
                throw new ArgumentNullException("sensor");
            }

            if (gestureResultView == null)
            {
                throw new ArgumentNullException("gestureResultView");
            }

            this.GestureResultView = gestureResultView;

            //Create the VGB source
            this.vgbFrameSource = new VisualGestureBuilderFrameSource(sensor, 0);
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
                    if (gesture.Name.Equals(this.waveGestureName))
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

        public void Dispose()
        {
            this.Dispose(true);
            GC.SuppressFinalize(this);
            throw new NotImplementedException();
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
                            if (gesture.Name.Equals(this.waveGestureName) && gesture.GestureType == GestureType.Discrete)
                            {
                                DiscreteGestureResult result = null;
                                discreteResults.TryGetValue(gesture, out result);

                                if (result != null)
                                {
                                    this.GestureResultView.UpdateGestureResult(true, result.Detected, result.Confidence);
                                }
                            }
                        }
                    }
                }
            }
        }

        private void Source_TrackingIdLost(object sender, TrackingIdLostEventArgs e)
        {
            // update the GestureResultView object to show the 'Not Tracked' image in the UI
            this.GestureResultView.UpdateGestureResult(false, false, 0.0f);
        }
    }
}
